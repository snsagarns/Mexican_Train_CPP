/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#ifndef Setup_hpp
#define Setup_hpp

#include <stdio.h>
#include <iostream>
#include <deque>
#include <vector>
#include "Tiles.hpp"

using namespace std;

class Setup
{
public:
    // default constructor
    Setup();

    // Accessors
    // returns the Computer-Human train setup
    inline deque<Tiles> getTrainTiles()
    {
        return trainTiles;
    }

    // returns the Mexican Train Setup
    inline vector<Tiles> getMexicanTrain()
    {
        return mexicanTrain;
    }

    // sets the Computer-Human Train
    void setPlayersTrain(deque<Tiles> train)
    {
        trainTiles = train;
    }
    // sets the Mexican Train
    void setMexicanTrain(vector<Tiles> train)
    {
        mexicanTrain = train;
    }

    // Utility functions

    // Prints the Computer-Human Train
    void printTrain(int a);

    // Prints the Mexican Train
    void printMexicanTrain();

    // Insert Tiles to the Computer Train
    void insertLeft(Tiles t);

    // Insert Tiles to the Human Train
    void insertRight(Tiles t);

    // Places engine on the Game Board
    void placeEngine(Tiles e);

    // Get the Tiles Leftmost Tile from the Computer Train
    Tiles getLeft();

    // Get the right most tile from the Human Train
    Tiles getRight();

    // Get the right most tile from the Mexican Train
    Tiles getFromMexicanTrain();

    // Insert Tiles to the Mexican Train
    void insertInMexicanTrain(Tiles t);

private:
    // vector to store the mexican Train setup
    vector<Tiles> mexicanTrain;

    // deque to store the Computer-Human Train setup
    deque<Tiles> trainTiles;

    // boolean to check if the engine has already been inserted or not
    bool insert_engine;
};

#endif /* Setup_hpp */
