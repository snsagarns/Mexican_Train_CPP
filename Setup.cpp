/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/
#include "Setup.hpp"
#include "Tiles.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

/* *********************************************************************
Function Name: Setup
Purpose: Default Constructor, initialize the insert_engine to false
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Setup::Setup()
{
    insert_engine = false;
}

/* *********************************************************************
Function Name: placeEngine
Purpose:
        To insert the engine tile to both Mexican and Computer-Human Train
Parameters: Tile object e
Return Value: None
Local Variables: None
Algorithm:
        1. Both Mexican and Computer-Human Train is empty until now, so insert engine to both of them.
Assistance Received: None
********************************************************************* */
void Setup::placeEngine(Tiles e)
{
    trainTiles.push_back(e);
    mexicanTrain.push_back(e);
}

/* *********************************************************************
Function Name: insertLeft
Purpose:
        To insert the tile to the Computer Train
Parameters: Tile object t
Return Value: None
Local Variables: None
Algorithm:
        1. Insert tile to the Computer Train
Assistance Received: None
********************************************************************* */
void Setup::insertLeft(Tiles t)
{
    trainTiles.push_front(t);
}

/* *********************************************************************
Function Name: insertRight
Purpose:
        To insert the tile to the Human Train
Parameters: Tile object t
Return Value: None
Local Variables: None
Algorithm:
        1. Insert tile to the Human Train
Assistance Received: None
********************************************************************* */
void Setup::insertRight(Tiles t)
{
    trainTiles.push_back(t);
}

/* *********************************************************************
Function Name: getLeft
Purpose:
        To get the leftmost tile from the Computer train
Parameters: None
Return Value: Leftmost Tile from the Computer Train
Local Variables: None
Algorithm:
        1. Since Computer-Human train is deque, return the tile at index 0, it will give leftmost tile of the computer train
Assistance Received: None
********************************************************************* */
Tiles Setup::getLeft()
{
    return trainTiles[0];
}

/* *********************************************************************
Function Name: getRight
Purpose:
        To get the righttmost tile from the Human Train
Parameters: None
Return Value: Rightmost Tile from the Human Train
Local Variables: None
Algorithm:
        1. Since Computer-Human train is deque, return the tile at last index, it will give rightmost tile of the human train
Assistance Received: None
********************************************************************* */
Tiles Setup::getRight()
{
    return trainTiles[trainTiles.size() - 1];
}

/* *********************************************************************
Function Name: getFromMexicanTrain
Purpose:
        To get the righttmost tile from the Mexican Train
Parameters: None
Return Value: Rightmost Tile from the Mexican Train
Local Variables: None
Algorithm:
        1. Since Mexica train is vector, return the tile at last index, it will give rightmost tile of Mexican Train
Assistance Received: None
********************************************************************* */
Tiles Setup::getFromMexicanTrain()
{
    return mexicanTrain[mexicanTrain.size() - 1];
}

/* *********************************************************************
Function Name: insertInMexicanTrain
Purpose:
        To insert provided tile to the right of the Mexican Train
Parameters: None
Return Value: None
Local Variables: None
Algorithm:
        1. Insert to the right of the Mexican train setup by pushing back the tile
Assistance Received: None
********************************************************************* */
void Setup::insertInMexicanTrain(Tiles t)
{
    mexicanTrain.push_back(t);
}

/* *********************************************************************
Function Name: printMexicanTrain
Purpose:
        To print the Mexican Train setup to the screen
Parameters: None
Return Value: None
Local Variables:
        line_a, line_b, line_c, three separate ostringstream lines to match the required output setup
Algorithm:
        1. declare three ostringstream objects line to write a string
        2. iterate through the Mexican Train Setup, check if the tiles are double tile and load accordingly on separate lines for desired output
        3. if the tiles are reversed, then first print the second side then the first side
        4. adjust the setwidth accordingly. It may vary based on the console screen.
        5. Exit the loop and print them to the screen
Assistance Received: None
********************************************************************* */
void Setup::printMexicanTrain()
{
    // ostringstream to store the first line, second line and third line.
    std::ostringstream line_a, line_b, line_c;

    cout << "\nMexican Train" << endl;

    // adjusting setwidth so that Mexican Train prints little further to the right than the computer human train
    int count = 50 + trainTiles.size() * 4;
    cout << setw(50);

    // print Mexican train only after it has been started
    if (mexicanTrain.size() > 1)
    {
        cout << internal;
        // loop through the Mexican train and adjust the output accordingly
        for (auto &t : mexicanTrain)
        {
            if (t.getFirsttSide() == t.getSecondSide())
            {
                line_a << std::setw(1) << t.getFirsttSide();
                line_b << std::setw(1) << "|";
                line_c << std::setw(1) << t.getSecondSide();
            }
            else if (!t.checkReverse())
            {
                line_a << std::setw(6) << " ";
                line_b << "|" << t.getFirsttSide() << "-" << t.getSecondSide() << "| ";
                line_c << std::setw(6) << " ";
            }
            else
            {
                line_a << std::setw(6) << " ";
                line_b << "|" << t.getSecondSide() << "-" << t.getFirsttSide() << "| ";
                line_c << std::setw(6) << " ";
            }
        }

        // print the Mexican Train
        std::cout << setw(75) << line_a.str() << '\n'
                  << setw(75) << line_b.str() << '\n'
                  << setw(75) << line_c.str() << '\n';
    }
}

/* *********************************************************************
Function Name: printTrain
Purpose:
        To print the Computer-Human Train to the screen
Parameters: a, an integer value to adjust the marker on Computer and Human train accordingly
Return Value: None
Local Variables:
        line_a, line_b, line_c, three separate ostringstream lines to match the required output setup
Algorithm:
        1. declare three ostringstream objects line to write a string
        2. iterate through the Computer-Human Train Setup, check if the tiles are double tile and load accordingly on separate lines for desired output
        3. if the tiles are reversed, then first print the second side then the first side
        4. adjust the setwidth accordingly. It may vary based on the console screen.
        5. After exiting the loop, check the rececived value from the parameter
        6. (1) means there is a marker in Computer Train, (2) means there is a marker in Human Train, (3) means there is a marker in both train s
Assistance Received: None
********************************************************************* */
void Setup::printTrain(int a)
{
    // ostringstream to store the first line, second line and third line.
    std::ostringstream line_a, line_b, line_c;

    cout << "\nComputer Train | Human Train" << endl;
    cout << left;
    cout << setw(50);

    // loop through the Computer-Human train and adjust the output accordingly
    for (auto &t : trainTiles)
    {
        if (t.getFirsttSide() == t.getSecondSide())
        {
            line_a << std::setw(1) << t.getFirsttSide();
            line_b << std::setw(1) << "|";
            line_c << std::setw(1) << t.getSecondSide();
        }
        else if (!t.checkReverse())
        {
            line_a << std::setw(6) << " ";
            line_b << "|" << t.getFirsttSide() << "-" << t.getSecondSide() << "| ";
            line_c << std::setw(6) << " ";
        }
        else
        {
            line_a << std::setw(6) << " ";
            line_b << "|" << t.getSecondSide() << "-" << t.getFirsttSide() << "| ";
            line_c << std::setw(6) << " ";
        }
    }

    // denoting marker in the computer train printing "M" to the left of the screen above the leftmost tile of the computer train
    if (a == 1)
    {
        cout << "M" << endl;
        std::cout << line_a.str() << '\n'
                  << line_b.str() << '\n'
                  << line_c.str() << '\n';
    }

    // denoting marker in the human train printing "M" to the right of the screen to the righmost tile of the human train
    else if (a == 2)
    {
        std::cout << line_a.str() << " " << '\n'
                  << line_b.str() << "M" << '\n'
                  << line_c.str() << " " << '\n';
    }

    // denoting marker in both computer and human train
    else if (a == 3)
    {
        cout << "M" << endl;
        std::cout << line_a.str() << " " << '\n'
                  << line_b.str() << "M" << '\n'
                  << line_c.str() << " " << '\n';
    }

    // marker doesn't exist on any train
    else
    {
        std::cout << line_a.str() << '\n'
                  << line_b.str() << '\n'
                  << line_c.str() << '\n';
    }
}
