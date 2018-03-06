//
// Created by Jian  on 3/5/18.
//

#ifndef MINE_SWEEPER_CPP_SHELL_MYAI_HPP
#define MINE_SWEEPER_CPP_SHELL_MYAI_HPP

#include<iostream> // temporary use
#include "Agent.hpp"

class MyAI : public Agent
{
public:
    MyAI ( void );

    Action getAction ( bool mine, int neighbourMine, int flagLeft, int uncoverLeft ) override;

    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================


    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
};

#endif //MINE_SWEEPER_CPP_SHELL_MYAI_HPP
