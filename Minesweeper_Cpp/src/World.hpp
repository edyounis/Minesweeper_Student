//
// FILE:        World.hpp
//
// Created by Jian Li  on 2/19/18.
//
// DESCRIPTION: This file contains the World class, which is responsible
//              for everything game related.
//

#ifndef MINE_SWEEPER_CPP_SHELL_BOARD_HPP
#define MINE_SWEEPER_CPP_SHELL_BOARD_HPP

#include <cstdio>       // rand
#include <iostream>     // iostream
#include <iomanip>      // setw
#include <string>       // string
#include <fstream>      // file
#include "Agent.hpp"
#include "ManualAI.hpp"
#include "RandomAI.hpp"
#include "MyAI.hpp"

class World{

public:
    World(bool debug, string aiType, string filename);      // Constructor
    ~World  (  );                                           // Destructor
    int run (  );                                           // Engine function

private:
    // Tile structure
    struct Tile{
        bool mine       = false; // has Bomb or nor
        bool uncovered  = false; // uncovered or nor
        bool flag       = false; // flag marker
        int  number     = 0;     // records number of bombs around
    };

    // Operation Variables
    bool 	debug;			    // If true, displays board info after every move

    // Agent Variables
    Agent* 	agent;			    // The agent
    int 	score;			    // The agent's score
    int     flagLeft;           // flag remaining
    int	    agentX;			    // The column where the agent is located ( x-coord = col-coord )
    int	    agentY;			    // The row where the agent is located ( y-coord = row-coord )
    int     coveredTiles;       // For faster score calculation and
    int     correctFlags;       // checking game-terminating conditions.
    Agent::Action	lastAction;	// The last action the agent made

    // Board Variables
    int	    colDimension;	    // The number of columns the game board has
    int	    rowDimension;	    // The number of rows the game board has
    Tile**	board;			    // The game board
    int     totalMines;         // Number of mines the game board has

    // World Variables
    const int WIN_BONUS = 100;
    const int LOSS_PENALTY = -100;
    const int FLAG_BONUS = 2;
    const int FLAG_PENALTY = -2;

    // World Management functions
    void 	        addFeatures	    (   );                  // add random features to the board
    void	        addFeatures ( std::ifstream &file );	// add specified features according the file to the board
    Agent::Action   genFirstAxis    (   );                  // generate first move axis
    void 	        addMine 		(   );                  // add mine to game board
    void            addMineCount    (   );                  // adding mine counter according to neighbour
    void            addNeighbour    ( int c, int r );       // helper function for addMineCount
    void            uncoverAll      (   );                  //
    bool            doMove          ( Agent::Action action );//
    bool            isInBounds      ( int c, int r );       // check bound

    // World printing functions
    void	        printWorldInfo	(   );
    void            printBoardInfo  (   );
    void            printTileInfo   ( int c, int r );
    void	        printAgentInfo  (   );
    void	        printActionInfo	(   );

    // Helper Functions
    int	            randomInt	( int limit );              // Randomly generate a int in the range [0, limit)

};

#endif //MINE_SWEEPER_CPP_SHELL_BOARD_HPP
