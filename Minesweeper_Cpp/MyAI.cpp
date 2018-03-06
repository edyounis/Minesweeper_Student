//
// Created by Jian  on 3/5/18.
//

#include "MyAI.hpp"

MyAI::MyAI(void) : Agent ( ) {}


Agent::Action MyAI::getAction(bool mine, int neighbourMine, int flagLeft, int uncoverLeft) {
    std::cout << "Debugging: My AI initialize...." << std::endl;
    Agent::Action action = {LEAVE, -1, -1};
    return action;
}
