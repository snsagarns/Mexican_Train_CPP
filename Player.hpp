/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <iostream>
#include "Hand.hpp"

using namespace std;

class Player
{
public:
    // Player Class Constructor
    Player();

    // Accessors
    Hand getHand()
    {
        return hand;
    }

    // Utility functions
    // virtual function to select the tiles for given side
    virtual int selectTiles(int needed_side);

    // validates sides and return the index for required side
    int validateSides(int side1, int side2);

    // sets hand tiles for players
    void setHand(Hand h);

    // prints the hand tiles of players
    void printHand();

    // sums of all tiles present in hand
    int getSumofHands();

    // calculates the score of player
    int calculateScore();

    // finds the best fit tile to play for given side
    int findGoodTile(int side);

    // deletes tile from the hand for given indexs
    void deleteTilesFromHand(int index);

    // adds the tiles to player's hand
    void addTilesToHand(Tiles t);

    // utility function to lowercase the string for input validation
    string lowercase(string &a_temp);

    // boolean function to check if player's hand is exhausted
    bool isHandEmpty();

    // helps with the index of tile for human
    void provideHelp(int needed_side);

    // provides the demanded tile located at given index
    Tiles getDemandedTile(int index);

private:
    // players hand
    Hand hand;
    
    // drawm
    bool drawn;
};

#endif /* Player_hpp */
