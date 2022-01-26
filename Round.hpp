/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#ifndef Round_hpp
#define Round_hpp

#include <stdio.h>
#include "Player.hpp"
#include "Human.hpp"
#include "Computer.hpp"
#include "Deck.hpp"
#include "Hand.hpp"
#include "Tiles.hpp"
#include "Setup.hpp"

class Round
{
public:
    // Round Class constructor, round number as a parameter
    Round(int num_round);

    // checks if the condition has been met to end the round
    bool isGameOver();

    // function for playing the game based on turn
    void playTurn(Player *player);

    // sets hand tiles
    void setHandTiles();

    // prints game details to the screen
    void printDetails();

    // finds the player's turn and calls player to play the game
    int findTurn();

    // finds the side needed to be played on own train
    int ownSideNeeded();

    // finds the side needed to be played on opponent's train
    int opponentSideNeeded();

    // finds the side needed to be played on mexican train
    int mexicanSideNeeded();

    // gets score for the Human player
    int getHumanScore();

    // gets score for the Computer player
    int getComputerScore();

    // gets topmost tile from the boneyard
    Tiles getTileFromBoneyard();

    // asks human player for the eligible train they want to play
    int userChosenTrain();

    // provide help for the human player to choose the train and tile get computer's train
    int chooseTrain();

    // sets orphan double when necessary
    void setOrphanDouble();
    
    // get setup
    Setup getSetup(){
        return setup;
    }
    
    // sets the turn of the player
    void setTurn(int a)
    {
        turn = a;
    }

    // sets Human player's hand
    void setHumanHand(vector<Tiles> v)
    {
        player1.setHand(v);
    }

    // sets Computer player's hand
    void setComputerHand(vector<Tiles> v)
    {
        player2.setHand(v);
    }

    // sets the Computer-Human Train setup
    void setSetup(deque<Tiles> v)
    {
        setup.setPlayersTrain(v);
    }

    // sets the Mexican Train setup
    void setMexicanTrain(vector<Tiles> v)
    {
        setup.setMexicanTrain(v);
    }

    // sets the boneyard deck of remaining tiles s
    void setDeckBoneyard(vector<Tiles> v)
    {
        deck.setDeck(v);
    }

    // sets the deck
    void setDeck(Deck d)
    {
        deck = d;
    }

    // sets the left marker Computer Train marker
    void setLeftMarker(bool a)
    {
        has_left_marker = a;
    }

    // sets the right marker Human Train marker
    void setRighttMarker(bool a)
    {
        has_right_marker = a;
    }

    // sets the Mexican Train as Orphan Double
    void setOrphanDouble_M(bool a)
    {
        mt_odt = a;
    }

    // sets the Computer Train as Orphan Double
    void setOrphanDouble_C(bool a)
    {
        ct_odt = a;
    }

    // sets the Human Train as Orphan Double
    void setOrphanDouble_H(bool a)
    {
        ht_odt = a;
    }

    // checks if the human's hand is exhausted, i.e, if it's empty
    bool isHumanHandEmpty()
    {
        return player1.isHandEmpty();
    }

    // checks if the computer's hand is exhausted, i.e, if it's empty
    bool isComputerHandEmpty()
    {
        return player2.isHandEmpty();
    }

    // sets Human score
    void setHumanScore(int a){
        human_score = a;
    }
    // sets computer score
    void setComputerScore(int a){
        computer_score = a;
    }
    
    // saveGame;
    void saveGame(int &score1, int &score2);
    
    // checks if the boneyard is empty
    bool isBoneyardEmpty();

    //extract the engine for the given round
    Tiles getEngine(int a);

private:
    // engine for the round
    int engine;

    // number of round
    int num_round;

    // turn of the player
    int turn;

    // boolean variable to store the status of computer train's marker
    bool has_left_marker;

    // boolean variable to store the status of human train's marker
    bool has_right_marker;

    // boolean to store whether human train, mexican train or computer train is orphan double or not
    bool ht_odt, mt_odt, ct_odt;
    
    // score
    int human_score;
    int computer_score;
    

    // Human player
    Human player1;

    // Computer player
    Computer player2;

    // Deck
    Deck deck;

    // Train Setup
    Setup setup;
};

#endif /* Round_hpp */
