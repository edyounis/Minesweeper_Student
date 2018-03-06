//
// FILE:        World.cpp
//
// Created by Jian Li  on 2/19/18.
//
// DESCRIPTION: This file contains the World class, which is responsible
//              for everything game related.
//

#include "World.hpp"

using namespace std;

// ===============================================================
// =				Constructor and Destructor
// ===============================================================

World::World( bool _debug, bool _randomAI, bool _manualAI, string filename )
{

    // Operation Flags
    debug        = _debug;
    manualAI     = _manualAI;

    // World Initialization
    // if ture: file provided
    // if false: file not provided, board with default size and random feature
    if ( filename != "" )
    {
        //cout<< "open file" << endl;  debug use
        // open file
        ifstream file;
        file.open(filename);

        // read file
        file >> colDimension >> rowDimension;
        if (file.fail())
            throw exception();
        board = new Tile*[colDimension];
        for ( int index = 0; index < colDimension; ++index )
            board[index] = new Tile[rowDimension];

        // set feature according to the file
        addFeatures ( file );
        file.close();
    }
    else
    {
        mineNums        = 10;
        colDimension    = 9; // temporary use
        rowDimension    = 9;
        board = new Tile*[colDimension];
        for ( int index = 0; index < colDimension; ++index )
            board[index] = new Tile[rowDimension];

        // Adding mines, adding mine counter according to neighbour, uncover first file
        addFeatures();
    }

    // Agent Initialization
    score           = 0;
    countCover      = rowDimension * colDimension;
    flagLeft       =  10;  // temporary use
    // Generate random first move axis: in bound, has no mine, no neighbour has mine
    // return agent for first move coordinates info
    lastAction   = genFirstAxis();
    agentX       = lastAction.x;
    agentY       = lastAction.y;

    if ( _randomAI )
        agent = new RandomAI();
    if ( _manualAI )
        agent = new ManualAI();
    else
        agent = new MyAI();

}

World::~World() {
    for ( int index = 0; index < colDimension; ++index )
        delete [] board[index];

    delete [] board;
}

// ===============================================================
// =					Engine Function
// ===============================================================

int World::run()
{
    while ( score >= -1000 )
    {
        if ( debug || manualAI )
        {
            printWorldInfo();

            if ( !manualAI )
            {
                // Pause the game, only if manualAI isn't on
                // because manualAI pauses for us
                cout << "Press ENTER to continue..." << endl;
                cin.ignore( 999, '\n');
            }
        }

        // Get the move
        lastAction = agent->getAction(board[agentX][agentY].mine, board[agentX][agentY].neighbour, flagLeft, countCover);
        agentX       = lastAction.x;
        agentY       = lastAction.y;

        // Make the move
        switch ( lastAction.action )
        {
            case Agent::LEAVE:
                if (countCover == mineNums)
                    score += 1000; // temporary use
                uncoverAll();

                return score;
            case Agent::UNCOVER:
                board[agentX][agentY].uncovered = true; // warning for uncovered tile to be uncovered again?
                if (board[agentX][agentY].mine)     // invalid tile
                {
                    score -= 1000;
                    uncoverAll();
                    return score;
                }
                else
                {
                    ++score;
                }
                --countCover;
                break;
            case Agent::FLAG:
                if (flagLeft) // warning for out of use
                {
                    board[agentX][agentY].flag = true;
                    --flagLeft;
                    if (board[agentX][agentY].mine)
                        ++score;
                    else
                        --score;
                    break;
                }

            case Agent::UNFLAG:
                board[agentX][agentY].flag = false;
                ++flagLeft;
                if (board[agentX][agentY].mine)
                    --score;
                else
                    ++score;
                break;
        }
    }
    return score;
}


// ===============================================================
// =				World Generation Functions
// ===============================================================
void World::addFeatures(    )
{

    // Generate mine: mineNums times, in bound, no mine before -> [mc][mr]mine = true
    addMine();

    // Generate number of mines around
    addMineCount();
}

void World::addFeatures( std::ifstream &file )
{

    int r = rowDimension;
    bool mine = 0;

    // generate mine according to input file
    while (r > 0 &&!file.eof() )
    {
        --r;

        for ( size_t c = 0; c < colDimension; ++c )
        {
            file >> mine;

            if (file.fail())
                throw exception();
            if (mine)
            {
                board[c][r].mine = mine;
                ++mineNums;
            }
        }
    }

    // Generate number of mines around
    addMineCount();
    // printBoardInfo();  debug use
}

void World::addMine(    )
{

    for (int m = 0; m < mineNums; ++m){
        size_t mc = randomInt( colDimension );
        size_t mr = randomInt( rowDimension );
        while ( !isInBounds( mc, mr ) || board[mc][mr].mine ) {
            mc = randomInt( colDimension );
            mr = randomInt( rowDimension );
        }
        board[mc][mr].mine = true;
    }
}

void World::addMineCount(   )
{
    for ( int c = 0; c < colDimension; ++c ){
        for ( int r = 0; r < rowDimension; ++r ){
            if (!board[c][r].mine)
                addNeighbour( c, r );
        }
    }
}

void World::addNeighbour( size_t c, size_t r)
{
    // helper function for addMineCount
    // iterate 8 neighbours around a tile, and increment neighbour if there is mine

    int dir[8][2] = { {-1, 1}, {-1, 0}, {-1 , -1},
                      {0, 1},          {0, -1},
                      {1, 1}, {1, 0}, {1, -1} };

    for (int *i : dir) {
        size_t nc = c + i[0];
        size_t nr = r + i[1];
        if ( isInBounds( nc, nr ) && board[nc][nr].mine ){
            board[c][r].neighbour++;
        }
    }
}

Agent::Action World::genFirstAxis(  )
{

    size_t fc = randomInt( colDimension );
    size_t fr = randomInt( rowDimension );
    //while ( !isInBounds( fc, fr ) || board[fc][fr].mine || board[fc][fr].neighbour) //potentially wrong for no non_zero neighbour
    while ( !isInBounds( fc, fr ) || board[fc][fr].mine)
    {
        fc = randomInt( colDimension );
        fr = randomInt( rowDimension );
    }
    board[fc][fr].uncovered = true;

    Agent::Action firstMove = {Agent::UNCOVER, (int) fc , (int )fr};
    return firstMove;
}

void World::uncoverAll() {
    for ( int c = 0; c < colDimension; ++c )
    {
        for ( int r = 0; r < rowDimension; ++r )
            board[c][r].uncovered = true;
    }
}


bool World::isInBounds ( size_t c, size_t r )
{
    return ( c < colDimension && r < rowDimension );
}

// ===============================================================
// =				World Printing Functions
// ===============================================================

void World::printWorldInfo(     )
{
    printBoardInfo();
    printAgentInfo();
}

void World::printBoardInfo(     )
{

    for ( int r = rowDimension-1; r >= 0; --r )
    {
        for ( size_t c = 0; c < colDimension; ++c )
            printTileInfo ( c, r );
        cout << endl << endl;
    }
}

void World::printTileInfo( size_t c, size_t r )
{

    string tileString;

    if ( board[c][r].uncovered )
        if ( board[c][r].mine )
            tileString.append("*");
        else
        {
            tileString.append(to_string(board[c][r].neighbour));

        }
    else if ( board[c][r].flag )
            tileString.append("#");  // temporary use
    else
        tileString.append(".");

    cout << setw(8) << tileString;
}

void World::printAgentInfo(void)
{
    cout << "Score: "       << score    << endl;
    cout << "The agent has " << flagLeft << " flag remaining" << endl;
    cout << "The agent has " << countCover << " tile to uncover" << endl;

    printActionInfo ();
}

void World::printActionInfo()
{
    switch ( lastAction.action )
    {
        case Agent::UNCOVER:
            cout << "Last Action: Uncover";
            break;
        case Agent::FLAG:
            cout << "Last Action: Flag";
            break;
        case Agent::UNFLAG:
            cout << "Last Action: Unflag";
            break;
        case Agent::LEAVE:
            cout << "Last Action: Leave" << endl;
            break;

        default:
            cout << "Last Action: Invalid" << endl;
    }

    if (lastAction.action != Agent::LEAVE)
        cout << " on tile " << agentX << " " << agentY << endl;
}

// ===============================================================
// =					Helper Functions
// ===============================================================

size_t World::randomInt ( size_t limit )
{
    return rand() % limit;
}






