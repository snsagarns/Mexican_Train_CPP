/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#include "Player.hpp"
#include "Hand.hpp"
#include "Tiles.hpp"
#include <string>
#include <iostream>

using namespace std;

/* *********************************************************************
Function Name: Player
Purpose: Default Constructor
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Player::Player(){
    drawn = false;
}

/* *********************************************************************
Function Name: setHand
Purpose:
        To set the player's hand tiles
Parameters:
        Hand object
Return Value: None
Local Variables: None
Algorithm:
        1. Assign the hand object received to player's hand vector
Assistance Received: None
********************************************************************* */
void Player::setHand(Hand h)
{
    hand = h;
}

/* *********************************************************************
Function Name: addTilesToHand
Purpose:
        Utility function to add tiles to the player's hand
Parameters:
        Tile object
Return Value: None
Local Variables: None
Algorithm:
        1. Call the utility function to add tiles to the player's hand
Assistance Received: None
********************************************************************* */
void Player::addTilesToHand(Tiles t)
{
    hand.addTiles(t);
}

/* *********************************************************************
Function Name: deleteTilesFromHand
Purpose:
        Utility function to delete the tiles from the player's hand from given index position
Parameters:
        index
Return Value: None
Local Variables: None
Algorithm:
        1. call the utility function to remove the tile from the hand
Assistance Received: None
********************************************************************* */
void Player::deleteTilesFromHand(int index)
{
    hand.removeTile(index);
}

/* *********************************************************************
Function Name: isHandEmpty()
Purpose:
        Utility function to check if the player's hand is exhausted, i.e, has no more tiles to play
Parameters: None
Return Value: boolean value whether the hand is empty or not (true if it is, false if it's not)
Local Variables: None
Algorithm:
        1. call the utility function to check if there's no more tile in hand
Assistance Received: None
********************************************************************* */
bool Player::isHandEmpty()
{
    return hand.getHandTiles().empty();
}
/* *********************************************************************
Function Name: selectTiles
Purpose:
        To find out the index of tiles in hand required for playing on eligible train
        To see if drawing a tile from the boneyard is necessary or not
Parameters: needed_side, side required to be placed on the eligible train
Return Value: index of tile if found in hand, if not found returns -1
Local Variables:
        move, integer value to return either -1 or the index of the tile to be played
        tile object t, to store the tile for the validation
        index_size, integer value to store the valid size of the hand, helpful for input validation
        flag, boolean utility for input validation
Algorithm:
        1. get the side needed for playing
        2. ask user for input, validate it, and ask user for an index of the tile they wish to play
        3. check if the tile at user entered index matches with the side that's actually needed
        4. checks if the player has any eligible tile on his/her hand for playing,
        5. validate the tile and return index of tile if playable tile is in hand
        6. If playable tile is not in hand, return -1 which will later prompt user to draw one from the boneyard
        
Assistance Received: None
********************************************************************* */
int Player::selectTiles(int needed_side)
{

    // move -1 no playable tile in hand, else store index of playable tile in hand
    int move = -1;

    // tile object
    Tiles t;

    // iterate until true
    for (;;)
    {
        
        string userInput;
        cout << "\n<<<<< Enter an index for a tile you want to play >>>>>" << endl;
        cout << "<<<<< Press 'H' or 'HELP' for Help. Press 'P' or 'PASS' for Pass and Press 'D' or 'Draw' for Draw >>>>" << endl;
        cout << "<<<<< You can press 'E' or 'EXIT' to Exit the Game and 'S' to Save the Game: >>>> : " << endl;

        cin >> userInput;

   
            if ((lowercase(userInput) == "help") || (lowercase(userInput) == "h"))
            {
                provideHelp(needed_side);
                continue;
            }
        

        
        // exit the game with a message See you again!
        if (lowercase(userInput) == "e" || lowercase(userInput) == "exit")
        {
            cout << "See you again!" << endl;
            exit(1);
        }
       

        if ((lowercase(userInput) == "p") || (lowercase(userInput) == "pass") ||
            (lowercase(userInput) == "d") || (lowercase(userInput) == "draw"))
        {
            // checks if the move is valid or not
            int command_code = findGoodTile(needed_side);
            // if only move is not possible
            if (command_code == -1)
            {
                if (!drawn)
                {
                    cout << "\n"
                         << "Tiles are being drawn for you" << endl;
                    return -1;
                }
                else
                {
                    return -2;
                }
            }
            else
            {
                cout << "You can't pass or draw... Move is possible! Press h or HELP if you need  help from a computer!!" << endl;
            }
            continue;
        }

        // boolean flag for input validation
        bool flag = false;

        // valid index size
        int index_size = hand.getHandSize();

        if (userInput.size() <= 2)
        {
            int index;

            for (int i = 0; i < userInput.size(); i++)
            {
                if (isdigit(userInput[i]))
                {
                    flag = true;
                }
                else
                {
                    flag = false;
                }
            }
            if (flag == true)
            {
                index = stoi(userInput);
                index--;
                if (index > index_size || index < 0)
                {
                    cout << "Invalid Index! Please enter a valid index" << endl;
                    cin >> userInput;
                }
                else
                {
                    t = getDemandedTile(index);
                    if ((t.getFirsttSide() == needed_side) || (t.getSecondSide() == needed_side))
                    {
                        move = validateSides(t.getFirsttSide(), t.getSecondSide());
                    }
                }
            }
        }
        //if user entered index has valid tile to play, break
        if (move != -1)
        {
            break;
        }
        else
        {
            cout << "Invalid Tile selection. You must enter the tile with matching pip\n"
                 << endl;
        }
    }
    return move;
}

/* *********************************************************************
Function Name: getDemandedTile
Purpose:
        return the tile at given index
Parameters: index
Return Value: tile object t
Local Variables: tile object t
Algorithm:
       1.  throw an exception if a user provide with an invalid index else return a tile at given index
Assistance Received: None
********************************************************************* */
Tiles Player::getDemandedTile(int index)
{
    Tiles t;
    try
    {
        t = hand.getHandTiles().at(index);
    }
    catch (const std::out_of_range &e)
    {
        cout << "Exception thrown" << endl;
    }
    return t;
}

/* *********************************************************************
Function Name: provideHelp
Purpose:
        to help with the user with index of tile if they have already choosen train
Parameters: needed_side, side required for playing
Return Value: None
Local Variables: command_code, stores the index of tile if playable and asks for drawing a tile if not playable storing -1
Algorithm:
        1. call the utility function findGoodTile and based on the return value, provide appropriate help to the user
Assistance Received: None
********************************************************************* */
void Player::provideHelp(int needed_side)
{
    int command_code = findGoodTile(needed_side);
    if (command_code >= 0)
    {
        cout << "Computer suggests you to play tiles at index: " << command_code + 1 << " because it is either a double tile or has got high matching pip\n";
    }
    else
    {
        cout << "No tiles playable in the train you selected. Draw a tile\n"
             << endl;
    }
}

/* *********************************************************************
Function Name: findGoodTile
Purpose:
        to find the index of the most suitable tile to play in order to maximize chances of winning
Parameters: needed_side, side required for playing
Return Value: None
Local Variables: return_code, stores the index of the most suitable tile to play, if none, stores -1
Algorithm:
        1. check if the player has a double tile that can be played in their hand for the side required
        2. if double tile can be played, return the index of double tile
        3. if double tile cannot be played, iterate through the player's hand to find the tile with required side
        4. even if the tile is found, continue the iteration and update the tile if tile with required side has higher counterpart value
        5. if found, return the index of tile with maximum sum, For instance if needed side = 7 AND 7-1 and 7-9 are two tiles, return 7-9
        6. if neither double nor any tile found for given side, return -1
Assistance Received: None
********************************************************************* */
int Player::findGoodTile(int side)
{

    int count = 0;
    int returnCode = -1;
    int temp = -1;
    for (auto &t : hand.getHandTiles())
    {
        // if double tile found return its index
        if ((t.getFirsttSide() == side) && (t.getSecondSide() == side))
        {

            return hand.findSidesInTile(side, side);
        }
        // if not found, continue the iteration to find tile with side with maximum sum combination with other half
        else
        {
            if ((t.getFirsttSide() == side) || (t.getSecondSide() == side))
            {
                temp = (100 + t.getFirsttSide() * 10 + t.getSecondSide());
                if (temp > returnCode)
                {
                    returnCode = temp;
                }
            }
            count++;
        }
    }
    if (returnCode > 0)
    {
        int digit = returnCode % 100;
        return hand.findSidesInTile(digit / 10, digit % 10);
    }
    return returnCode;
}

/* *********************************************************************
Function Name: validateSides
Purpose:
        To check if the two sides are valid are pip value of valid tile or not
Parameters: side1 and side 2: first and second side
Return Value: None
Local Variables: count, counter to find the index of a tile with given sides
Algorithm:
        1. iterate through the hand tiles of the player and return index of tile if it's valid tile else return -1
Assistance Received: None
********************************************************************* */
int Player ::validateSides(int side1, int side2)
{

    int count = 0;
    for (auto &t : hand.getHandTiles())
    {
        if ((t.getFirsttSide() == side1) && (t.getSecondSide() == side2))
        {
            return count;
        }
        count++;
    }
    return -1;
}

/* *********************************************************************
Function Name: lowercase
Purpose:
       utility function to lowercase every letter of the string
Parameters: a_temp, string passed by reference
Return Value: lowercase string
Local Variables: None
Algorithm:
        1. iterate through the string size and change every character to a lowercase string
Assistance Received: None
********************************************************************* */
string Player::lowercase(string &a_temp)
{
    for (int i = 0; i < a_temp.size(); i++)
    {
        a_temp[i] = tolower(a_temp[i]);
    }
    return a_temp;
}

/* *********************************************************************
Function Name: getSumofHands
Purpose:
       to find the sum of all tiles existing in the player's hand
Return Value: sum, sum of tiles sides
Local Variables: sum, stores the sum
Algorithm:
        1. iterate through the player's hand and add sum of tiles to the sum calling getSumOfSides from Tiles class
Assistance Received: None
********************************************************************* */
int Player::getSumofHands()
{
    int sum = 0;

    for (auto &t : hand.getHandTiles())
    {
        sum = sum + t.getSumOfSides();
    }
    return sum;
}

/* *********************************************************************
Function Name: calculateScore
Purpose:
       to calculate the score of the player
Return Value: sum of all tiles left in the player's hand
Local Variables: None
Algorithm:
        1. return the sum of tiles of player's hand
Assistance Received: None
********************************************************************* */
int Player::calculateScore()
{
    return getSumofHands();
}

/* *********************************************************************
Function Name: printHand
Purpose:
       to print all the tiles in the player's hand
Return Value: None
Local Variables: count, counter variable for iteration, change_line, utility to format the output
Algorithm:
        1. call utility function printTiles and change line after printing 9 tiles in a line
Assistance Received: None
********************************************************************* */
void Player::printHand()
{
    int count = 0;
    int change_line = 0;
    cout << "\t";
    for (auto &t : hand.getHandTiles())
    {
        if (change_line % 9 == 0)
        {
            cout << "\n\t";
        }
        cout << (count + 1) << ".";
        t.printTiles();
        count++;
        change_line++;
    }
}
