/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#include "Deck.hpp"

#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <time.h>
using namespace std;

/* *********************************************************************
Function Name: Deck
Purpose:
        To construct a Deck Object and intialize it with all possible tiles
Parameters: None
Return Value: None
Algorithm:
        Iterate over and insert all the possible uniqu tiles to a deck vector
Assistance Received: None
********************************************************************* */

Deck::Deck()
{
    for (int i = 0; i <= 9; i++)
    {
        for (int j = i; j <= 9; j++)
        {
            deck.push_back(Tiles(i, j));
        }
    }
}

/* *********************************************************************
Function Name: getEngineFromDeck
Purpose:
        to extract the engine tile based on the round and set the engine accordingly for higher rounds
        delete the engine tile from the deck after extracting it
Parameters: round, round number, passed by value
Local Variables:
                t: tile object made to be returned
                engine_pip: side of the engine
                engine_code: index of the engine
Return Value: t, engine tile object
Algorithm:
        1. If the round is less than 11, subtract the round from 10 to get engine pip
        2. If the round is greater than or equal to 11, subtract (round mod 10) from 10 to get engine pip
        3. Multiply engine pip with 10 and add engine pip to it to get double digit value of engine
        4. Iterate through the deck to find the doubleDigit value of engine
        4. After finding it, store the index on engine_code
        5. Erase the engine from the deck
        5. Create the tile object setting engine pip as both first and second side of it and return the tile object
Assistance Received: None
********************************************************************* */
Tiles Deck::getEngineFromDeck(int round)
{
    // tile object to store the engine tile
    Tiles t;

    // temp to store the engine pip value
    int engine_pip;

    // temp to receive and store the round number
    int temp = round;

    // stores the index of engine in the deck
    int engine_code = -1;

    // loop counter
    int index = 0;

    if (temp < 11)
    {
        temp = 10 - temp;
    }
    else
    {
        temp = 10 - temp % 10;
    }

    // storing double digit of engine pip
    temp = temp * 10 + temp;

    for (auto &t : deck)
    {
        int value = t.getDoubleDigitSides();

        if (value == temp)
        {
            engine_code = index;
        }
        index++;
    }

    // removes the engine tile from the deck
    deck.erase(deck.begin() + engine_code);

    // creates a tile object with engine pip and return it
    engine_pip = temp % 10;
    t.setSides(engine_pip, engine_pip);

    return t;
}

/* *********************************************************************
Function Name: shuffleDeck
Purpose:
        To shuffle a deck of cards
Parameters: None
Return Value: None
Local Variables:
        seed, an unsigned int holding current time
Algorithm:
        1.Shuffle the deck vector
Assistance Received: None
********************************************************************* */
void Deck::shuffleDeck()
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

    auto rng = std::default_random_engine(seed);
    shuffle(deck.begin(), deck.end(), rng);
}

/* *********************************************************************
Function Name: distributeToPlayer
Purpose:
        To provide unique 16 tiles to each player from the deck and delete them later
Parameters: None
Return Value: tile vector storing the unique tiles assigned to the player
Local Variables:
        tile_vec, Tiles vector created to store the tiles assigned to the players
Algorithm:
        1. Assign the first 16 tiles to the player storing them in a vector
        2. Delete those tiles that have been assigned to the player
        3. return the vector that stores the tiles provided to the players
Assistance Received: None
********************************************************************* */
vector<Tiles> Deck::distributeToPlayer()
{

    // get first 16 tiles
    vector<Tiles> tile_vec(deck.begin(), deck.begin() + 16);

    // after distributing delete those tiles
    for (int i = 0; i < 16; i++)
    {
        deck.erase(deck.begin());
    }

    return tile_vec;
}

/* *********************************************************************
Function Name: getFromBoneyard
Purpose:
        To extract the topmost tile from the boneyard
Parameters: None
Return Value: topmost tile from the boneyard
Local Variables:
        temp, tile object  created to store the topmost tile from the boneayard
Algorithm:
        1. store the topmost tile on the tile object
        2. remove the topmost tile from the deck
        3. return the topmost tile
Assistance Received: None
********************************************************************* */
Tiles Deck::getFromBoneyard()
{
    Tiles temp = deck.front();
    deck.erase(deck.begin());
    return temp;
}

/* *********************************************************************
Function Name: printDeck
Purpose:
        To print all the tiles remaining in the boneyard
Parameters: None
Return Value: None
Local Variables:
        change_line to format the output
Algorithm:
        1. call printTile function from Tiles class and change line after printing 11 tiles
Assistance Received: None
********************************************************************* */
void Deck::printDeck()
{
    int change_line = 0;
    for (auto &temp : deck)
    {
        if (change_line % 11 == 0)
        {
            cout << "\n\t";
        }
        temp.printTiles();
        change_line++;
    }
    cout << "\n";
}

/* *********************************************************************
Function Name: getSizeDeck
Purpose:
        To get the size of deck, i.e, number of remaining tiles in the deck
Parameters: None
Return Value: size, size of the deck
Local Variables:
        size, to store the size of the decks
Algorithm:
        1. get the deck and call size() function for the vector and return the size of deck vector
Assistance Received: None
********************************************************************* */
int Deck::getSizeDeck()
{
    int size = getDeck().size();
    return size;
}
