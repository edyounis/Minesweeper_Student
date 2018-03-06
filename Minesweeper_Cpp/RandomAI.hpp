//
// Created by Jian  on 3/5/18.
//

#ifndef MINE_SWEEPER_CPP_SHELL_RANDOMAI_HPP
#define MINE_SWEEPER_CPP_SHELL_RANDOMAI_HPP

#include <cstdlib>
#include "Agent.hpp"

class RandomAI : public Agent
{
public:

    Action getAction(bool mine, int neighbourMine, int flagLeft, int uncoverLeft) override
    {
        return actions [ rand() % 4 ];  //??
    }

private:

    const Action actions[4] =
            {
                    UNCOVER,
                    FLAG,
                    UNFLAG,
                    LEAVE,
            };
};
#endif //MINE_SWEEPER_CPP_SHELL_RANDOMAI_HPP
