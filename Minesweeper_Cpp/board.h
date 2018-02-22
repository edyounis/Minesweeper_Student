//
// FILE:        Board.h
//
// Created by Jian Li  on 2/19/18.
//
// DESCRIPTION: This file contains the Board class, which is responsible
//              for everything game related.
//

#ifndef MINE_SWEEPER_CPP_SHELL_BOARD_H
#define MINE_SWEEPER_CPP_SHELL_BOARD_H

#include <cstdio>
#include<iostream>
#include <iomanip>
#include <string>

class Board{

public:

    // Constructor
    Board();

    // Destructor
    ~Board();

    // Engine function
    void run ();



private:
    // Tile structure
    struct Tile{
        bool mine       = false; // has Bomb or nor
        bool uncovered  = true; // uncovered or nor
        bool flag       = false; // flag marker
        int  neighbour  = 0;  // records number of bombs around
    };

    // Board Variables
    size_t	colDimension;	// The number of columns the game board has
    size_t	rowDimension;	// The number of rows the game board has
    Tile**	board;			// The game board
    int mineNums;           // Number of mines the game board has

    // Board Management functions
    void 	addFeatures	    (   );  // add needed features to the board
    void 	addMine 		(   );  // add mine to game board
    void    addMineCount    (   );  // number of mines around every single tile
    void    addNeighbour     ( size_t c, size_t r ); // number of mines around a single tile
    void    genFirstAxis    (   );  // generate first move axis
    bool    isInBounds      ( size_t c, size_t r );  // check bound

    // Board printing functions
    void    printBoardInfo  (   );  // print a board
    void    printTileInfo ( size_t c, size_t r ); // print a tile

    // Helper Functions
    size_t	randomInt	( size_t limit );		// Randomly generate a int in the range [0, limit)

};

#endif //MINE_SWEEPER_CPP_SHELL_BOARD_H
