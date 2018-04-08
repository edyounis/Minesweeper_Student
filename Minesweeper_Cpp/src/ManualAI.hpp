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

    ManualAI ( int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY ){
        rowDimension = _rowDimension;
        colDimension = _colDimension;
        totalMines   = _totalMines;
    };

    Action getAction( int number ) override
    {
        // Print Command Menu
        std::cout << "---------------- Available Actions ----------------" << std::endl;
        std::cout << "L: leave game   U: uncover tile   F: flag   N: unflag" << std::endl;

        Action_type new_action = Action_type ::LEAVE;
        char input_action;
        int input_x = -1; // x = col
        int input_y = -1; // y = row

        // get action from input
        std::cout << "Enter a action:  ";
        while (true)
        {
            std::cin >> input_action;
            std::cin.ignore(9999, '\n');


            if (input_action == 'L')
                break;
            else if (input_action == 'U')
            {
                new_action = UNCOVER;
                break;
            }

            else if (input_action == 'F')
            {
                new_action = FLAG;
                break;
            }

            else if (input_action == 'N')
            {
                new_action = UNFLAG;
                break;
            }

            else
                std::cout << "Invalid action specified, please enter again: ";
        }

        // get coordinates from input
        if (new_action != LEAVE)
        {
            std::cout << "Enter X: ";
            while (!(std::cin >> input_x) || input_x < 0 || input_x > rowDimension)
            {
                std::cout << "Invalid coordinates specified, please enter again: ";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
            }
            std::cout << "Enter Y: ";
            while (!(std::cin >> input_y) || input_y < 0 || input_y > colDimension)
            {
                std::cout << "Invalid coordinates specified, please enter again: ";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
            }
        }

        return {new_action, input_x, input_y};
    };
};


#endif //MINE_SWEEPER_CPP_SHELL_MANUALAL_HPP
