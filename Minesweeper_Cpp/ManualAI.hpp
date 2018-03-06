//
// Created by Jian  on 3/4/18.
//

#ifndef MINE_SWEEPER_CPP_SHELL_MANUALAL_HPP
#define MINE_SWEEPER_CPP_SHELL_MANUALAL_HPP

#include "Agent.hpp"
#include<iostream>

class ManualAI : public Agent
{
public:
    Action getAction(bool mine, int neighbourMine, int flagLeft, int uncoverLeft) override
    {
        // Print Command Menu
        std::cout << "Press 'L' to 'Leave'  'U' to 'Uncover'" << std::endl;
        std::cout << "Press 'F' to 'Flag'   'N' to 'Unflag'" << std::endl;

        Action_type new_action = Action_type ::LEAVE;
        char input_action;
        int input_x = -1; // x = col
        int input_y = -1; // y = row

        // get action from input
        std::cout << "Please press a action: ";
        while (true)
        {
            std::cin >> input_action;
            std::cin.ignore(9999, '\n');


            if (input_action == 'L')
                break;
            else if (input_action == 'U')
            {
                new_action = UNCOVER;
                --uncoverLeft;
                break;
            }

            else if (input_action == 'F')
            {
                new_action = FLAG;
                --flagLeft;
                break;
            }

            else if (input_action == 'N')
            {
                new_action = UNFLAG;
                ++flagLeft;
                break;
            }

            else
                std::cout << "Invalid action specified, please enter again: ";
        }

        // get coordinates from input
        if (new_action != LEAVE)
        {
            std::cout << "Please enter coordinates (x y): ";
            while (!(std::cin >> input_x) || input_x < 0 || !(std::cin >> input_y) || input_y < 0)
            {
                std::cout << "Invalid coordinates specified, please enter again: ";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
            }
        }

        Action action = {new_action, input_x, input_y};
        return action;
    };
};


#endif //MINE_SWEEPER_CPP_SHELL_MANUALAL_HPP
