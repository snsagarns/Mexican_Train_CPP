/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#include "Computer.hpp"
#include "Player.hpp"

/* *********************************************************************
Function Name: selectTiles
Purpose:
        To separate the user call for select Tiles from computer call and automate computer's play
        User should be asked for input, but computer will play automatically
Parameters: side, side needed to play
Return Value:
            returns the index of the tile if possible to play, if not possible, returns -1
Local Variables: move, tile and command_code
Algorithm:
        1. Initialize move to -1 and check if there is any good fit tile for the side needed to be played
        2. If there's none, return -1;
        3. Otherwise extract the good fit tile's index and validate the tile and return it's index position
Assistance Received: None
********************************************************************* */
int Computer::selectTiles(int side)
{
    int move = -1;

    int command_code = findGoodTile(side);

    if (command_code == -1)
    {
        return -1;
    }
    else
    {
        Tiles t = getDemandedTile(command_code);
        move = validateSides(t.getFirsttSide(), t.getSecondSide());
        return move;
    }
}
