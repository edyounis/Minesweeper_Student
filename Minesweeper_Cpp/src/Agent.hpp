//
// Created by amos  on 2/26/18.
//

#ifndef MINE_SWEEPER_CPP_SHELL_AGENT_HPP
#define MINE_SWEEPER_CPP_SHELL_AGENT_HPP

class Agent {

public:
int    rowDimension;
int    colDimension;
int    totalMines;
int    agentX;
int    agentY;
public:

// Actuators
enum Action_type
{
    LEAVE,
    UNCOVER,
    FLAG,
    UNFLAG,
};

struct Action{
    Action_type     action;
    int             x;
    int             y;

};

virtual Action getAction
        (
            int number
        ) = 0;
};
#endif //MINE_SWEEPER_CPP_SHELL_AGENT_HPP
