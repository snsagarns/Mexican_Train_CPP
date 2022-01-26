/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#include "Tiles.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

/* *********************************************************************
Function Name: Tiles
Purpose: Default Constructor
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Tiles::Tiles() {}

/* *********************************************************************
Function Name: Tiles
Purpose:
        Parameterized constructor to create a tile object, intialize is_reverse and set is_double
Parameters:
        first_side,  an integer passed by value that holds the first side of the tile
        second_side, an integer passed by value that holds the second side of the tile
Return Value: None
Algorithm:
        Constructs a tile object by initializing first side and second side of the tile.
        Initialize the variable to check if the tile's side should be reversed to false
        Checks if the tile's first side and second side are equal and if they are, sets the is_double to true
        If the two sides of tiles aren't same, sets the is_double to false.
Assistance Received: None
********************************************************************* */
Tiles::Tiles(int first_side, int second_side)
{
    this->is_reverse = false;
    this->first_side = first_side;
    this->second_side = second_side;

    if (this->first_side == this->second_side)
    {
        is_double = true;
    }
    else
    {
        is_double = false;
    }
}

/* *********************************************************************
Function Name: setSides
Purpose:
        To set the first and second side of the tile;
Parameters:
        first_side,  an integer passed by value that is to be set as the first side of the tile
        second_side, an integer passed by value that is to be set as the second side of the tile
Return Value: None
Algorithm:
        Receives the first and second side and sets them accordingly
Assistance Received: None
********************************************************************* */
void Tiles::setSides(int first_side, int second_side)
{
    this->first_side = first_side;
    this->second_side = second_side;
}

/* *********************************************************************
Function Name: getSumOfSides
Purpose:
        To get the sum of two sides of tile which will be later helpful to select good tiles among matching tiles
Parameters: None
Return Value: None
Algorithm:
        find the sum of first side and second side of the tile and return them
Assistance Received: None
********************************************************************* */
int Tiles::getSumOfSides()
{
    return this->first_side + this->second_side;
}

/* *********************************************************************
Function Name: getDoubleDigitSides
Purpose:
        To get the double digit value for tile manipulation. For instance 7-3 gives 73
Parameters: None
Return Value: return the double digit value from two sides of the tile
Algorithm:
        multiplies the first side by 10 and adds the second side to it
Assistance Received: None
********************************************************************* */
int Tiles::getDoubleDigitSides()
{
    int double_digit = this->first_side * 10 + this->second_side;
    return double_digit;
}

/* *********************************************************************
Function Name: reverseTile
Purpose:
        To set the boolean reverse_tile variable when needed.
Parameters: None
Return Value: None
Algorithm:
        Set the is_reverse to true to reverse the side of tile.
Assistance Received: None
********************************************************************* */
void Tiles::reverseTile()
{
    this->is_reverse = true;
}

/* *********************************************************************
Function Name: printTiles
Purpose:
        To formatthe tile and print it
Parameters: None
Return Value: None
Algorithm:
        checks if the tile's sides need to be reversed. If yes, then print the second side of the tile first
        followed by the first side. If not, then print the first side followed by second side
Assistance Received: None
********************************************************************* */
void Tiles::printTiles()
{

    if (!is_reverse)
        cout << "|" << this->first_side << "-" << this->second_side << "| ";
    else
        cout << "|" << this->second_side << "-" << this->first_side << "| ";
}
