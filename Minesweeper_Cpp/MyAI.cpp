// ======================================================================
// FILE:        MyAI.cpp
//
// AUTHOR:      Jian Li
//
// DESCRIPTION: This file contains your agent class, which you will
//              implement. You are responsible for implementing the
//              'getAction' function and any helper methods you feel you
//              need.
//
// NOTES:       - If you are having trouble understanding how the shell
//                works, look at the other parts of the code, as well as
//                the documentation.
//
//              - You are only allowed to make changes to this portion of
//                the code. Any changes to other portions of the code will
//                be lost when the tournament runs your code.
// ======================================================================

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
    known     = {{agentX, agentY}};
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

    //// uncovered Debugging:
//    cout<<"uncovered:\n";
//    for (auto i: uncovered)
//        cout<<get<0>(i)<<get<1>(i)<<endl;
    ////danger Debugging:
//    cout<<"danger:\n";
//    for (auto i: danger)
//        cout<<i.first.first<<i.first.second<<"number: "<<i.second<<endl;
    //// next_uncover Debugging:
//    cout<<"next_uncover: "<<endl;
//    for (auto i: next_uncover)
//        cout<<get<0>(i)<<get<1>(i)<<endl;
    //// next_flag Debugging:
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
        }

        if(!next_flag.empty())                                                   // Flag tiles
        {
            auto tile = *next_flag.begin();
            genAction(tile.first, tile.second, FLAG, next_flag, marked);
        }
        else if (!next_uncover.empty())                                         // Uncover tiles
        {
            auto tile = *next_uncover.begin();
            genAction(tile.first, tile.second, UNCOVER, next_uncover, known);
        }
        else                                                                    // Pattern generate
        {
//            for (auto i: danger)
//            {
//                cout<<i.first.first<<i.first.second<<"number: "<<i.second<<endl;
//                if (i.second==0)
//                    danger.erase(i.first);
//            }
            auto next_it = danger.cbegin();
            for (auto it = danger.cbegin(); it != danger.cend(); it = next_it)
            {
                next_it = it; ++next_it;
                if ((*it).second==0)
                {
                    danger.erase(it);
                }
            }

            pattern();
            if (!next_uncover.empty())                                                  // Uncover tiles
            {
                auto tile = *next_uncover.begin();
                genAction(tile.first, tile.second, UNCOVER, next_uncover, known);

            }
            else if(!next_flag.empty())                                                   // Flag tiles
            {
                auto tile = *next_flag.begin();
                genAction(tile.first, tile.second, FLAG, next_flag, marked);
            }
            else
            {
                pair<int, int> buff = guess();
                if (buff.first != -1)
                {
                    next_uncover.emplace(buff);
                    auto tile = *next_uncover.begin();
                    genAction(tile.first, tile.second, UNCOVER, next_uncover, known);
                }
            }
        }
    }

    if (next_uncover.empty() && next_flag.empty())                              // No action: no more flag and uncover
        action.action = LEAVE;
    else
        clearNext(action.action);                                               // remove implemented tiles
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
        if (isInBounds(newX, newY))
            result.emplace(newX, newY);

    }
    return result;
}

void MyAI::genNext(int x, int y, set<pair<int, int>> &add, set<pair<int, int>> check) {
    for (const pair<int, int> i: getNeighbour(x, y))
    {
        int newX = i.first;
        int newY = i.second;

        if (isInBounds(newX, newY) && !count(check.begin(),check.end(),make_pair(newX, newY)))
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
}

void MyAI::clearNext(Agent::Action_type act) {
    if (act == FLAG)
        next_flag.erase(next_flag.begin());
    else if (act == UNCOVER)
        next_uncover.erase(next_uncover.begin());
}

void MyAI::pattern() {
    for (auto p: danger)
    {
        if (p.second == 1)      // find 1
        {
            set<pair<int, int>> edg;
            genNext(p.first.first, p.first.second, edg, known);
            if (edg.size() == 2)    // 1 at edg
            {
                set<pair<int, int>> neighbour;
                genNext(p.first.first, p.first.second, neighbour, {});

                for (auto n: neighbour)
                {
                    if ( danger.count(n) && (danger.at(n) == 1 || danger.at(n) == 2)&&    // adjacent of p = 1, vertical
                         ( p.first.first == n.first || p.first.second == n.second) ) // or horizontal
                    {
                        set<pair<int, int>> n_neighbour;
                        genNext(n.first, n.second, n_neighbour, known);
                        if (n_neighbour.size()==3)      // ??unexplored 3 tiles from adjacent of p = 1
                        {
                            auto it = n_neighbour.begin();
                            if  ( (*it).second == (*(++it)).second && (*it).second == (*(it)).second  )
                            {
                                for (auto item: n_neighbour)
                                {
                                    if (item.first != p.first.first && item.first != n.first) // find the third tile
                                    {
                                        if (danger.at(n) == 1)
                                            next_uncover.emplace(item);
                                        else if (danger.at(n) == 2)
                                            next_flag.emplace(item);
                                    }
                                }

                            }
                            else if ( (*it).first == (*(++it)).first && (*it).first == (*(it)).first  )
                            {
                                for (auto item: n_neighbour)
                                {
                                    if (item.second != p.first.second && item.second != n.second) // find the third tile
                                    {
                                        if (danger.at(n) == 1)
                                            next_uncover.emplace(item);
                                        else if (danger.at(n) == 2)
                                            next_flag.emplace(item);
                                    }

                                }
                            }
                        }
                    }
                }
            }

        }
    }
}

pair<int,int> MyAI::guess() {
    map<pair<int, int>, double> weight;
    for (auto p: danger)
    {
        if (p.second)
        {
            set<pair<int, int>> neighbour;
            genNext(p.first.first, p.first.second, neighbour, known);
            double size = neighbour.size();
            for (auto n: neighbour)
            {
                if (weight.count(n))
                {
                    weight.at(n) += (p.second/size);
                }
                else
                {
                    weight.emplace(make_pair(n, (p.second/size)));
                }
            }
        }
    }

    double min = 1000.0;
    pair<int,int> buff = make_pair(-1,-1);
    for (auto i: weight)
    {
        if (i.second < min)
        {
            min = i.second;
            buff = i.first;
        }
    }

    return buff;

}
// ======================================================================
// YOUR CODE ENDS
// ======================================================================
