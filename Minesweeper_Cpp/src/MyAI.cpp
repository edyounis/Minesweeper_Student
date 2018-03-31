//
// Created by Jian  on 3/5/18.
//

#include "MyAI.hpp"

MyAI::MyAI ( int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY ) : Agent()
{
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================
    rowDimension = _rowDimension;
    colDimension = _colDimension;
    totalMines   = _totalMines;
    agentX       = _agentX;
    agentY       = _agentY;

    uncovered = {{agentX, agentY}};
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
};

Agent::Action MyAI::getAction( int number )
{
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================

//    cout << "Debugging: My AI initialize...." << endl;



    if (firstMove)
    {
        genNext(agentX, agentY , next_move, uncovered);
        firstMove = false;
    }
    else if (number == 0)
    {
        genNext(action.x, action.y, next_move, uncovered);
    }

    for (auto i: next_move)
        cout<<get<0>(i)<<get<1>(i)<<endl;
    cout<<"\n";
    for (auto i: uncovered)
        cout<<get<0>(i)<<get<1>(i)<<endl;

    if (!next_move.empty())
    {
        auto x = *next_move.begin();
        action = {UNCOVER, get<0>(x), get<1>(x)};
        uncovered.emplace_back(action.x, action.y);
        next_move.erase(next_move.begin());
    }else
    {
        action = {LEAVE, -1, -1};
    }

    return action;
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
}

// ======================================================================
// YOUR CODE BEGINS
// ======================================================================

bool MyAI::isInBounds( int c, int r ){
    return ( 0 <= c && c < colDimension && 0 <= r && r < rowDimension );
}

vector<pair<int, int>> MyAI::getNeighbour( int x, int y ){
    vector<pair<int, int>> result;
    const vector<pair<int, int>> buff  = {  {-1,1},{0,1},{1,1},
                                            {-1,0},      {1,0},
                                            {-1,-1},{0,-1},{1,-1}};
    for (const pair<int, int> i: buff)
    {
        int newX = x + get<0>(i);
        int newY = y + get<1>(i);
        if (isInBounds(newX, newX))
            result.emplace_back(newX, newY);
    }
    return result;
}

void MyAI::genNext(int x, int y, vector<pair<int, int>> &next, vector<pair<int, int>> uncovered) {
    for (const pair<int, int> i: getNeighbour(x, y))
    {
        int newX = get<0>(i);
        int newY = get<1>(i);
        //cout<<!next.count({newX, newY})<<endl;
        if (isInBounds(newX, newY) && !count(uncovered.begin(),uncovered.end(),make_pair(newX, newY)) && !count(next.begin(),next.end(),make_pair(newX, newY)))
            next.emplace_back(newX, newY);
    }
}


// ======================================================================
// YOUR CODE ENDS
// ======================================================================