/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#include "Hand.hpp"
#include <vector>
#include <iostream>
using namespace std;

// utility for tile codes, named integral constants
enum tileCode
{
    double_tile = -2,
    not_found = -1
};

/* *********************************************************************
Function Name: Hand
Purpose: Default Constructor
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Hand::Hand() {}

/* *********************************************************************
Function Name: Hand
Purpose:
        Parameterized constructor to set the hand tiles vector with the tiles provided
Parameters: my_tiles vector of Tiles
Return Value: None
Local Variables: None
Algorithm:
        1. Set the hand tiles vector with the tiles that have been provided
Assistance Received: None
********************************************************************* */
Hand::Hand(vector<Tiles> my_tiles)
{
    tilesIn_hand = my_tiles;
}

/* *********************************************************************
Function Name: removeTile
Purpose:
        Remove the hand tile from the provided indexs
Parameters: index, index of tile to be removed
Return Value: None
Local Variables: None
Algorithm:
        1. Use vector erase functionality to remove the tiles from the given indexs
Assistance Received: None
********************************************************************* */
void Hand::removeTile(int index)
{
    tilesIn_hand.erase(tilesIn_hand.begin() + index);
}

/* *********************************************************************
Function Name: getTile
Purpose:
        To extract the tile from provied index
Parameters: index, index of tile to be extracted
Return Value: t, tile from the given index
Local Variables: t, tile object
Algorithm:
        1. Return the tile located at the given index. Throw exception error if an invalid index is provided
           checking for out of bound indices/values
Assistance Received: None
********************************************************************* */
Tiles &Hand::getTile(int index)
{
    // tile object
    Tiles t;
    try
    {
        t = tilesIn_hand.at(index);
        return t;
    }
    catch (const std::out_of_range &e)
    {
        cout << "Out of Range error. Provide good index" << endl;
    }
    return t;
}

/* *********************************************************************
Function Name: findSideInTile
Purpose:
        check if the player's hand has a tile with given side and get index if it has
Parameters: side
Return Value: tile_code, returns the index of tile with a given side if found, if not found return not_found, i.e, -1
Local Variables:
        tile_code: store the tile index if found, index: counter variable to find the index of a tile
        value: stores the double digit value for a tile
Algorithm:
        1. Iterate through the hand tiles and use utility function getDoubleDigitSides to find a dual digit for each tiles in hand
        2. Manipulate and extract two sides using division and modulus operator
        3. Check if the two sides extracted are equal. If they are, double tile for given side exists. Store it in the tile_code
        4. If they aren't double tile, find the tile with given side and store the index of that tile in tile code
        5. Return the tile_code. If not found tile_code will be -1
Assistance Received: None
********************************************************************* */
int Hand::findSideInTile(int side)
{
    // store the index of a required tile, counter variable
    int index = 0;

    // stores the appropriate tile code
    int tile_code = not_found;

    for (auto &t : tilesIn_hand)
    {
        int value = t.getDoubleDigitSides();

        if ((value / 10) == side || (value % 10) == side)
        {
            tile_code = index;
            break;
        }
        else if ((value / 10) == side && (value % 10) == side)
        {
            tile_code = double_tile;
        }

        index++;
    }
    return tile_code;
}

/* *********************************************************************
Function Name: findSidesInTile
Purpose:
        check if the player's hand has a tile with given sides and get index if it has
Parameters: side
Return Value: tile_code, returns the index of tile with a given side if found, if not found return not_found, i.e, -1
Local Variables:
        tile_code: store the tile index if found, index: counter variable to find the index of a tile
        value: stores the double digit value for a tile
Algorithm:
        1. Iterate through the hand tiles and use utility function getDoubleDigitSides to find a dual digit for each tiles in hand
        2. Manipulate and extract two sides using division and modulus operator. One with divison will be first side and one with modulus will be second side
        3. Check if the extracted value equals to the two sides that are required
        4. Find the tile with given sides and store the index of that tile in tile code
        5. Return the tile_code. If not found tile_code will be -1
Assistance Received: None
********************************************************************* */
int Hand::findSidesInTile(int side_one, int side_two)
{
    int index = 0;
    int tile_code = not_found;

    for (auto &t : tilesIn_hand)
    {
        int value = t.getDoubleDigitSides();

        if ((value / 10) == side_one && (value % 10) == side_two)
        {
            tile_code = index;
            return tile_code;
        }
        index++;
    }
    return not_found;
}

/* *********************************************************************
Function Name: printHandTiles
Purpose:
        To print all the tiles that are in player's hand
Parameters: None
Return Value: None
Local Variables: None
Algorithm:
        1. iterate over the player's hand tiles and call printTile utility function from the Tile class
Assistance Received: None
********************************************************************* */
void Hand::printHandTiles()
{
    for (auto &i : tilesIn_hand)
    {
        i.printTiles();
    }
}
