//
// Created by Jian  on 3/5/18.
//

#ifndef MINE_SWEEPER_CPP_SHELL_MYAI_HPP
#define MINE_SWEEPER_CPP_SHELL_MYAI_HPP

#include "Agent.hpp"
#include <iostream> // temporary use
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class MyAI : public Agent
{
public:
    MyAI ( int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY );

    Action getAction ( int number ) override;


    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================

    bool firstMove = true;
    bool end  = false;
    Action action  = {LEAVE, -1, -1};
    set<pair<int, int>>     next_uncover;
    set<pair<int, int>>     uncovered;
    set<pair<int, int>>     next_flag;
    set<pair<int, int>>     marked;
    set<pair<int, int>>     known;
    map<pair<int, int>, int> danger;


    bool                    isInBounds    ( int c, int r );
    set<pair<int, int>>     getNeighbour  ( int x, int y );
    void                    genNext       ( int x, int y,
                                            set<pair<int, int>> &add,
                                            set<pair<int, int>> check );
    void                    clearDanger   ( int x, int y );
    void                    genAction     ( int x, int y, Action_type act,
                                            set<pair<int, int>>& next,
                                            set<pair<int, int>>& record );
    void                    clearNext        ( Action_type act );

    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
};

#endif //MINE_SWEEPER_CPP_SHELL_MYAI_HPP
