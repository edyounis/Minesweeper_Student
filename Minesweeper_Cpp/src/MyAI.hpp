//
// Created by Jian  on 3/5/18.
//

#ifndef MINE_SWEEPER_CPP_SHELL_MYAI_HPP
#define MINE_SWEEPER_CPP_SHELL_MYAI_HPP

#include "Agent.hpp"
#include <iostream> // temporary use
#include <vector>
#include <map>
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
    bool genDanger = false;
    vector<pair<int, int>> next_move;
    vector<pair<int, int>> known;
    vector<pair<int, int>> flag;
    map<pair<int, int>, int> danger;
    Action action = {LEAVE, -1, -1};

    bool isInBounds ( int c, int r);
    vector<pair<int, int>>  getNeighbour(int x, int y);
    void                    genNext( int x, int y, vector<pair<int, int>>& next);

    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
};

#endif //MINE_SWEEPER_CPP_SHELL_MYAI_HPP
