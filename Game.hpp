/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <iostream>
#include "Round.hpp"

class Game
{
public:
    // constructor
    Game();

    // for playing a game
    void playGame();

    // load file for the serialization
    bool loadFile();

    // print the game details on the screen
    void printGameDetails();

    // ask user if they want to play another round
    void askForAnotherRound();
    

private:
    // game score
    int game_score;

    // human score for the round
    int human_score;

    // computer score for the round
    int computer_score;

    // round number
    int round_number;

    // playing round
    int playing_round;

    // winner
    string winner;

    // utility vectors and deque
    vector<Tiles> human_hand;
    vector<Tiles> computer_hand;
    vector<Tiles> boneyard;
    deque<Tiles> setup_train;
    vector<Tiles> mexican_setup;

    int play_turn;

    bool loadedFromFile = false;

    // check marker
    bool left_mark = false;

    // checks marker
    bool right_mark = false;
};

#endif /* Game_hpp */
