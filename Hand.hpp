/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#ifndef Hand_hpp
#define Hand_hpp

#include "Tiles.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

class Hand
{
public:
    // default constructor
    Hand();

    // another constructor with Tiles vector for tiles at hand
    Hand(vector<Tiles> my_tiles);

    // Accessors
    // inline function to get tiles in hand vector
    inline vector<Tiles> getHandTiles()
    {
        return tilesIn_hand;
    }

    // Utility Functions
    // inline function to get the size of tiles in hand
    inline int getHandSize()
    {
        return tilesIn_hand.size();
    }

    // inline function to add tiles
    inline void addTiles(Tiles tile)
    {
        tilesIn_hand.push_back(tile);
    }

    // get Tiles by index
    Tiles &getTile(int index);

    // remove a tile from the provided index
    void removeTile(int index);

    // find tile with one pip value of tile
    int findSideInTile(int side);

    // find tiles with two pip value of tile
    int findSidesInTile(int side_one, int side_two);

    // print the tiles in hand
    void printHandTiles();

private:
    // vector to store the tiles in hand
    vector<Tiles> tilesIn_hand;
};

#endif /* Hand_hpp */
