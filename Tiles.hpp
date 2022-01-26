/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#ifndef Tiles_hpp
#define Tiles_hpp

// Standard Include Files
#include <stdio.h>

using namespace std;

class Tiles
{

public:
    // Tiles Class default constructor
    Tiles();

    // Tiles Class parameterized constructor
    Tiles(int first_side, int second_side);

    // Accessors
    int getFirsttSide() { return this->first_side; }
    int getSecondSide() { return this->second_side; }
    bool checkDouble() { return this->is_double; }
    bool checkReverse() { return this->is_reverse; }

    // Utility functions
    int getSumOfSides();
    int getDoubleDigitSides();
    void reverseTile();
    void setSides(int first_side, int second_side);
    void printTiles();

private:
    // stores the first side of the tile
    int first_side;

    // stores the second side of the tiles
    int second_side;

    // boolean variable to check if the tile's first side and second side are same.
    bool is_double;

    // boolean variable to check if the tile's should be reversed to fit the train
    bool is_reverse;
};

#endif /* Tiles_hpp */
