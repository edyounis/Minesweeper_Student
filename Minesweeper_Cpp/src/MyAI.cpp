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

    // uncovered Debugging:
//    cout<<"uncovered:\n";
//    for (auto i: uncovered)
//        cout<<get<0>(i)<<get<1>(i)<<endl;
    //danger Debugging:
//    cout<<"danger:\n";
//    for (auto i: danger)
//        cout<<i.first.first<<i.first.second<<"number: "<<i.second<<endl;
    // next_uncover Debugging:
//    cout<<"next_uncover: "<<endl;
//    for (auto i: next_uncover)
//        cout<<get<0>(i)<<get<1>(i)<<endl;
    // next_flag Debugging:
//    cout<<"next_flag:\n";
//    for (auto i: next_flag)
//        cout<<i.first<<i.second<<endl;

    if (firstMove)                                                              // First move
    {
        genNext(agentX, agentY, next_uncover, known);
        firstMove = false;
    }
    else if (number == 0)                                                       // Safe tile: Generate uncover tile
    {
        genNext(action.x, action.y, next_uncover, known);
    }
    else if ( number == -1)                                                     // Flag percept
    {
        clearDanger(action.x, action.y);
    }
    else                                                                        // Dangerous tile
    {
        danger.emplace(make_pair(make_pair(action.x, action.y), number));
        set<pair<int, int>> neighbour = getNeighbour(action.x, action.y);       // clear danger
        for (auto i: neighbour)
        {
            if (marked.count(i))
                danger.at(make_pair(action.x, action.y))--;
        }

    }

    if (!next_uncover.empty())                                                  // Uncover tiles
    {
        auto tile = *next_uncover.begin();
        genAction(tile.first, tile.second, UNCOVER, next_uncover, uncovered);

    }
    else
    {
        if (next_flag.empty())
        {
            for (auto p: danger)
            {
                set<pair<int, int>> neighbour;
                genNext(p.first.first, p.first.second, neighbour, known);
                if (p.second)                                                  // Generate flag tiles
                {
                    if (neighbour.size() == p.second)
                    {
                        for (pair<int, int> n: neighbour)
                            next_flag.emplace(n);
                    }
                }
                else                                                            // Generate uncover tiles
                {
                    for (auto i: neighbour)
                        next_uncover.emplace(i.first, i.second);
                }
            }

            if (!next_uncover.empty())
            {
                auto tile = *next_uncover.begin();
                genAction(tile.first, tile.second, UNCOVER, next_uncover, known);
            }

        }

        if(!next_flag.empty())                                                   // Flag tiles
        {
            auto tile = *next_flag.begin();
            genAction(tile.first, tile.second, FLAG, next_flag, marked);
        }
    }

    if (next_uncover.empty() && next_flag.empty())                              // No action: no more flag and uncover
        action.action = LEAVE;
    else
        clearNext(action.action);

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

set<pair<int, int>> MyAI::getNeighbour(int x, int y) {
    set<pair<int, int>> result;
    const set<pair<int, int>> buff  = {  {-1,1},{0,1},{1,1},
                                            {-1,0},      {1,0},
                                            {-1,-1},{0,-1},{1,-1}};
    for (const pair<int, int> i: buff)
    {
        int newX = x + get<0>(i);
        int newY = y + get<1>(i);
        if (isInBounds(newX, newX))
            result.emplace(newX, newY);
    }
    return result;
}

void MyAI::genNext(int x, int y, set<pair<int, int>> &add, set<pair<int, int>> check) {
    for (const pair<int, int> i: getNeighbour(x, y))
    {
        int newX = i.first;
        int newY = i.second;
        if (isInBounds(newX, newY)  && !count(check.begin(),check.end(),make_pair(newX, newY)))
            add.emplace(newX, newY);
    }
}

void MyAI::clearDanger(int x, int y) {
    set<pair<int, int>> neighbour = getNeighbour(x,y);
    for (auto i: danger)
    {
        if (neighbour.count(i.first) && i.second)
            danger.at(i.first)--;
    }
}

void MyAI::genAction(int x, int y, Agent::Action_type act, set<pair<int, int>>& next, set<pair<int, int>>& record) {
    action = {act, x, y};
    record.emplace(x, y);
    known.emplace(x, y);
    //next.erase(next.begin());
}

void MyAI::clearNext(Agent::Action_type act) {
    if (act == FLAG)
        next_flag.erase(next_flag.begin());
    else if (act == UNCOVER)
        next_uncover.erase(next_uncover.begin());

}




// ======================================================================
// YOUR CODE ENDS
// ======================================================================