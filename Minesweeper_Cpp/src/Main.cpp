//
// FILE:        Main.cpp
//
// Created by Jian Li  on 2/19/18.
//
// DESCRIPTION: This file is the entry point for the program.
// Right now, it only in charge of launching board generation
// All tiles are set to uncover for visibility; set to false to display "."
//

#include <iostream>
#include <dirent.h>
#include <cmath>
#include "World.hpp"

using namespace std;

int main( int argc, char *argv[] )
{

    // Set random seed
    srand( time ( NULL ) );

    if ( argc == 1 ){
        World world(false, std::string(), std::string());
        int score = world.run();
        cout << "Your agent scored: " << score << endl;
        return 0;
    }

    // Important Variables
    bool 	debug        = false;
    bool	verbose      = false;
    string  aiType       = "MyAI";
    bool 	folder       = false;
    string	worldFile    = "";
    string	outputFile   = "";
    string 	firstToken 	 = argv[1];

    // read options if there are options
    if ( firstToken[0] == '-' )
    {
        // Parse Options
        for (int index = 1; index < firstToken.size(); ++index)
        {
//            switch (firstToken[index])
//            {
//                case '-':
//                    break;
//
//                case 'f':
//                case 'F':
//                    folder = true;
//                    break;
//
//                case 'v':
//                case 'V':
//                    verbose = true;
//                    break;
//
//                case 'r':
//                case 'R':
//                    randomAI = true;
//                    break;
//
//                case 'm':
//                case 'M':
//                    manualAI = true;
//                    break;
//
//                case 'd':
//                case 'D':
//                    debug = true;
//                    break;
//
//                default:
//                    return 0;
//            }
            // If both AI's on, turn one off and let the user know.
            if ( firstToken[index] == '-' )
                    continue;
            if ( firstToken[index] == 'f' || firstToken[index] =='F' )
                folder = true;
            if ( firstToken[index] == 'v' || firstToken[index] =='V' )
                verbose = true;
            if ( firstToken[index] == 'r' || firstToken[index] == 'R' )
            {
                if ( aiType == "manualAI" )
                    cout << "[WARNING] Manual AI and Random AI both on;"" Manual AI was turned off." << endl;
                aiType = "randomAI";
            }
            if ( firstToken[index] == 'm' || firstToken[index] == 'M' )
            {
                if ( aiType == "randomAI" )
                    cout << "[WARNING] Manual AI and Random AI both on; Manual AI was turned off." << endl;
                else
                    aiType = "manualAI";
            }
            if (firstToken[index] == 'd' || firstToken[index] == 'D')
                debug = true;

        }


        if ( argc >= 3 )
            worldFile = argv[2];
        if ( argc >= 4 )
            outputFile = argv[3];
    }
    else
    {
        if ( argc >= 2 )
            worldFile = argv[1];
        if ( argc >= 3 )
            outputFile = argv[2];
    }

    // no input folder for -f option turning on
    if ( worldFile == "" )
    {
        if ( folder )
            cout << "[WARNING] No folder specified; running on a random world." << endl;
        World world(debug, aiType, std::string());
        int score = world.run();
        cout << "The agent scored: " << score << endl;
        return 0;
    }

    // no input file or invalid file for -f option turning on
    if ( folder )
    {
        DIR *dir;
        if ((dir = opendir(worldFile.c_str())) == NULL)
        {
            cout << "[ERROR] Failed to open directory." << endl;
            return 0;
        }

        struct dirent *ent;

        int numOfScores = 0;
        double sumOfScores = 0;
        double sumOfScoresSquared = 0;

        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name[0] == '.')
                continue;

            if (verbose)
                cout << "Running world: " << ent->d_name << endl;

            string individualWorldFile = worldFile + "/" + ent->d_name;

            int score;
            try {
                World world(debug, aiType, individualWorldFile);
                score = world.run();
            }
            catch (...) {
                numOfScores = 0;
                sumOfScores = 0;
                sumOfScoresSquared = 0;
                break;
            }

            numOfScores += 1;
            sumOfScores += score;
            sumOfScoresSquared += score * score;
        }

        closedir(dir);

        double avg = (float)sumOfScores / (float)numOfScores;
        double std_dev = sqrt ( (sumOfScoresSquared - ((sumOfScores*sumOfScores) / (float)numOfScores) ) / (float)numOfScores );

        cout << "The agent's average score: " << avg << endl;  // temporary use
        cout << "The agent's standard deviation: " << std_dev << endl;

        return 0;
    }

    try
    {
        if ( verbose )
            cout << "Running world: " << worldFile << endl;

        World world(debug, aiType, worldFile);
        int score = world.run();
        cout << "The agent scored: " << score << endl; // temporary use
//        if ( outputFile == "" )
//        {
//            cout << "The agent scored: "  << endl;//?
//        }
//        else
//        {
//            ofstream file;
//            file.open ( outputFile );
//            //file << "SCORE: " << score << endl;
//            file.close();
//        }
    }
    catch ( const std::exception& e )
    {
        cout << "[ERROR] Failure to open file." << endl;
    }
}