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

    // Constructor
    World   ( bool debug = false, bool randomAI = false, bool manualAI = false, std::string filename = "" );

    // Destructor
    ~World  (  );

    // Engine function
    int run (  );

private:
    // Tile structure
    struct Tile{
        bool mine       = false; // has Bomb or nor
        bool uncovered  = false; // uncovered or nor
        bool flag       = false; // flag marker
        int  neighbour  = 0;     // records number of bombs around
    };

    // Operation Variables
    bool 	debug;			// If true, displays board info after every move
    bool	manualAI;		// If true, alters the behavior of debug for flow purposes

    // Agent Variables
    Agent* 	agent;			// The agent
    int 	score;			// The agent's score
    int     countCover;
    int     flagLeft;
    int	    agentX;			// The column where the agent is located ( x-coord = col-coord )
    int	    agentY;			// The row where the agent is located ( y-coord = row-coord )

    Agent::Action	lastAction;	// The last action the agent made

    // Board Variables
    size_t	colDimension;	// The number of columns the game board has
    size_t	rowDimension;	// The number of rows the game board has
    Tile**	board;			// The game board
    int     mineNums;       // Number of mines the game board has

    // World Management functions
    void 	        addFeatures	    (   );      // add random features to the board
    void	        addFeatures ( std::ifstream &file );	// add specified features according the file to the board
    void 	        addMine 		(   );      // add mine to game board
    void            addMineCount    (   );      // adding mine counter according to neighbour
    void            addNeighbour    ( size_t c, size_t r ); // helper function for addMineCount
    void            uncoverAll      (   );
    Agent::Action   genFirstAxis    (   );      // generate first move axis
    bool            isInBounds      ( size_t c, size_t r );  // check bound

    // World printing functions
    void	        printWorldInfo	(   );
    void            printBoardInfo  (   );
    void            printTileInfo   ( size_t c, size_t r );
    void	        printAgentInfo  (   );
    void	        printActionInfo	(   );

    // Helper Functions
    size_t	        randomInt	( size_t limit ); // Randomly generate a int in the range [0, limit)

};

#endif //MINE_SWEEPER_CPP_SHELL_BOARD_HPP
