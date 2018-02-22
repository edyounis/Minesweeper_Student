//
// FILE:        Board.cpp
//
// Created by Jian Li  on 2/19/18.
//
// DESCRIPTION: This file contains the Board class, which is responsible
//              for everything game related.
//

#include "board.h"

using namespace std;

// ===============================================================
// =				Constructor and Destructor
// ===============================================================

Board::Board() {


    colDimension = 9; // temporary use
    rowDimension = 9;
    mineNums = 10;

    board = new Tile*[colDimension];
    for ( int index = 0; index < colDimension; ++index )
        board[index] = new Tile[rowDimension];

    addFeatures();
}

Board::~Board() {
    for ( int index = 0; index < colDimension; ++index )
        delete [] board[index];

    delete [] board;
}

// ===============================================================
// =					Engine Function
// ===============================================================

void Board::run() {

    printBoardInfo();

    // Get the move

    // Make the move
}


// ===============================================================
// =				Board Generation Functions
// ===============================================================
void Board::addFeatures() {

    // Generate mine: mineNums times, in bound, no mine before -> [mc][mr]mine = true
    addMine();

    // Generate number of mines around
    addMineCount();

    // Generate first move axis: in bound, has no mine, no neighbour has mine
    genFirstAxis();

}

void Board::addMine() {

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

void Board::addMineCount( ) {

    for ( int c = 0; c < colDimension; ++c ){
        for ( int r = 0; r < rowDimension; ++r ){
            if (!board[c][r].mine)
                addNeighbour( c, r );
        }
    }
}

void Board::genFirstAxis(){

    size_t fc = randomInt( colDimension );
    size_t fr = randomInt( rowDimension );
    while ( !isInBounds( fc, fr ) || board[fc][fr].mine || board[fc][fr].neighbour){
        fc = randomInt( colDimension );
        fr = randomInt( rowDimension );
    }

    // cout << board[fc][fr].mine << board[fc][fr].neighbour << endl;
    cout << "first move: " << fc << fr << endl;
}

void Board::addNeighbour( size_t c, size_t r) {

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



bool Board::isInBounds ( size_t c, size_t r )
{
    return ( c < colDimension && r < rowDimension );
}

// ===============================================================
// =				World Printing Functions
// ===============================================================

void Board::printBoardInfo() {

    for ( int r = rowDimension-1; r >= 0; --r )
    {
        for ( size_t c = 0; c < colDimension; ++c )
            printTileInfo ( c, r );
        cout << endl << endl;
    }
}

void Board::printTileInfo(size_t c, size_t r) {

    string tileString;

    if ( board[c][r].uncovered )
        if ( board[c][r].mine )
            tileString.append("*");
        else
            tileString.append(to_string(board[c][r].neighbour));
    else if ( board[c][r].flag )
            tileString.append("#");  // temporary use
    else
        tileString.append(".");

    cout << setw(8) << tileString;
}

// ===============================================================
// =					Helper Functions
// ===============================================================

size_t Board::randomInt ( size_t limit )
{
    return rand() % limit;
}






