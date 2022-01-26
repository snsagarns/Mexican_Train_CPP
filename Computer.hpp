/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#ifndef Computer_hpp
#define Computer_hpp
#include <iostream>
#include <stdio.h>
#include "Player.hpp"

class Computer : public Player
{
public:
    // select sides functions for computer player
    int selectTiles(int side);

private:
};

#endif /* Computer_hpp */
