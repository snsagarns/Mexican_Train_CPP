/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#ifndef Deck_hpp
#define Deck_hpp

// Standard Include Files
#include <stdio.h>
#include <iostream>
#include <vector>

#include "Tiles.hpp"

using namespace std;

class Deck
{
public:
    // Deck class constructor
    Deck();

    //Accessors
    vector<Tiles> getDeck() { return this->deck; }

    // setter for the deck
    void setDeck(vector<Tiles> t)
    {
        deck = t;
    }

    // Utility Functions
    void shuffleDeck();
    void printDeck();
    int getSizeDeck();

    Tiles getEngineFromDeck(int round);
    Tiles getFromBoneyard();
    vector<Tiles> distributeToPlayer();

private:
    // vector containing all the shuffled tiles
    vector<Tiles> deck;
};

#endif /* Deck_hpp */
