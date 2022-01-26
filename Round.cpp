/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/
#include "Round.hpp"
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <iostream>
#include <fstream>

/* *********************************************************************
Function Name: Round
Purpose:
        Constructor to initialize data members, and print the engine
Parameters: round_count, round number
Return Value: None
Local Variables: None
Algorithm:
        1. Initialize the data members, extract engine for the round and print Engine tile for reference
Assistance Received: None
********************************************************************* */
Round::Round(int round_count)
{
    turn = 1;
    ht_odt = false;
    mt_odt = false;
    ct_odt = false;

    has_left_marker = false;
    has_right_marker = false;

    cout << "\nEngine for the round:  ";
    getEngine(round_count).printTiles();
    num_round = round_count;
    engine = getEngine(num_round).getFirsttSide();
}

/* *********************************************************************
Function Name: isGameOver
Purpose:
        to check if the condition for ending the round has been met
Parameters: None
Return Value: boolean value
Local Variables: None
Algorithm:
        1. returns true if an either player's hand is exhausted or boneyard is empty
Assistance Received: None
********************************************************************* */
bool Round::isGameOver()
{
    if (isBoneyardEmpty() == true)
        return true;
    if (player1.isHandEmpty() == true)
        return true;
    if (player2.isHandEmpty() == true)
        return true;

    return false;
}

/* *********************************************************************
Function Name: setHandTiles
Purpose:
        To shuffle the deck and distribute tiles to the player's hand and place an engine for the round
Parameters: None
Return Value: boolean value
Local Variables: None
Algorithm:
        1. shuffle the deck, set human player's hand, then set computer player's hand and place engine on the game board
Assistance Received: None
********************************************************************* */
void Round ::setHandTiles()
{
    // shuffiling the deck after the extraction of engine
    deck.shuffleDeck();

    // distributing tiles to the players
    player1.setHand(Hand(deck.distributeToPlayer()));
    player2.setHand(Hand(deck.distributeToPlayer()));

    cout << "\nStarting a game placing an engine: \n";
    // placing engine for the round
    setup.placeEngine(getEngine(num_round));
}

/* *********************************************************************
Function Name: getEngine
Purpose:
        To extract the engine from the deck
Parameters: integer a, passed by value : round number
Return Value: Engine tiles
Local Variables: None
Algorithm:
        1. call the utility function from Deck class to extract the engine
Assistance Received: None
********************************************************************* */
Tiles Round::getEngine(int a)
{
    return deck.getEngineFromDeck(a);
}

/* *********************************************************************
Function Name: printDetails
Purpose:
        To print both player's hand, boneyard and train setup
Parameters: None
Return Value: None
Local Variables: None
Algorithm:
        1. call the Utility function to print game details for the round
Assistance Received: None
********************************************************************* */
void Round::printDetails()
{

    cout << "\n--------------------------------------------WELCOME TO MEXICAN TRAIN GAME------------------------------------------------------" << endl;

    cout << "\nRound: " << num_round << endl;

    cout << "\nHuman Tiles at Hand:  \n";
    player1.printHand();

    cout << "\n\nComputer Tiles at Hand:  \n";
    player2.printHand();

    cout << "\n\nBoneyard: " << endl;
    deck.printDeck();

    cout << "\n---------------------------------------------------------------------------------------------------------------------------------" << endl;

    // 3 is the code to set marker in both player's train
    if (has_left_marker && has_right_marker)
    {
        setup.printTrain(3);
    }
    // 1 is the code to set marker in Computer's train
    else if (has_left_marker)
    {
        setup.printTrain(1);
    }
    // 2 is the code to set marker in Human's train
    else if (has_right_marker)
    {
        setup.printTrain(2);
    }
    // 0 denotes there is no marker in any player's train
    else
    {
        setup.printTrain(0);
    }
    cout << endl;
    setup.printMexicanTrain();
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------" << endl;
}

/* *********************************************************************
Function Name: findTurn
Purpose:
       To make players play on their turn until game ends
Parameters: None
Return Value: 1, if the human's hand is exhausted first, 2 if the computer's hand is exhausted and -1 if the game hasn't ended yets
Local Variables: None
Algorithm:
        1. check if the player's hand is exhausted, if it is return whose turn it was
        2. If the hand is not exhausted, make player play on their turn calling playTurn Function
Assistance Received: None
********************************************************************* */
int Round::findTurn()
{

    if (player1.isHandEmpty())
    {
        return 1;
    }
    if (player2.isHandEmpty())
    {
        return 2;
    }

    if (turn == 1)
    {
        cout << "\nHuman Player's Turn: \n"
             << endl;

        // play and change turn
        playTurn(&player1);
        turn = 2;
    }
    else
    {
        cout << endl
             << "\nComputer Player's Turn: \n"
             << endl;

        // play and change turn
        playTurn(&player2);
        turn = 1;
    }
    return -1;
}

/* *********************************************************************
Function Name: ownSideNeeded
Purpose:
       To find out which pip value is required in own train
Parameters: None
Return Value: returns the integer value of the side needed in own train
Local Variables: side_needed, stores the side needed to be played in own train
Algorithm:
        1. If human is playing, check if the rightmost tile's placed on human train was reversed or not
        2. If it was reversed,  first side of the tile is required side, otherwise, second side is a required side
        3. If a computer is playing check if the leftmost tile's placed on computer train was reversed or not
        4. If it was reversed,  second side of the tile is required side, otherwise, first side is a required side
        5. Return the side needed to be played on own side
Assistance Received: None
********************************************************************* */
int Round::ownSideNeeded()
{
    int side_needed;
    if (turn == 1)
    {
        if (!setup.getRight().checkReverse())
        {
            side_needed = setup.getRight().getSecondSide();
        }
        else
        {
            side_needed = setup.getRight().getFirsttSide();
        }
        return side_needed;
    }
    else
    {
        if (!setup.getLeft().checkReverse())
        {
            side_needed = setup.getLeft().getFirsttSide();
        }
        else
        {
            side_needed = setup.getLeft().getSecondSide();
        }
        return side_needed;
    }
}

/* *********************************************************************
Function Name: opponentSideNeeded
Purpose:
       To find out which pip value is required in opponent train in case it has a marker in future
Parameters: None
Return Value: returns the integer value of the side needed in opponent train
Local Variables: side_needed, stores the side needed to be played in opponent train
Algorithm:
        1. If human is playing, check if the leftmost tile's placed on computer train was reversed or not
        2. If it was reversed,  second side of the tile is required side, otherwise, first side is a required side
        3. If a computer is playing check if the rightmost tile's placed on human train was reversed or not
        4. If it was reversed,  first side of the tile is required side, otherwise, second side is a required side
        5. Return the side needed to be played on own side
Assistance Received: None
********************************************************************* */
int Round::opponentSideNeeded()
{
    int side_needed;
    if (turn == 1)
    {
        if (!setup.getLeft().checkReverse())
        {
            side_needed = setup.getLeft().getFirsttSide();
        }
        else
        {
            side_needed = setup.getLeft().getSecondSide();
        }
        return side_needed;
    }
    else
    {
        if (!setup.getRight().checkReverse())
        {
            side_needed = setup.getRight().getSecondSide();
        }
        else
        {
            side_needed = setup.getRight().getFirsttSide();
        }
        return side_needed;
    }
}

/* *********************************************************************
Function Name: mexicanSideNeeded
Purpose:
       To find out which pip value is required in Mexican Tain
Parameters: None
Return Value: returns the integer value of the side needed in Mexican Train
Local Variables: side_needed, stores the side needed to be played in Mexican Train
Algorithm:
        1. No matter, whcih player is playing, check if the rightmost tile's placed on Mexican train was reversed or not
        4. If it was reversed, first side of the tile is required side, otherwise, second side is a required side
        5. Return the side needed to be played on own side
        5. Return the side needed to be played on own side
Assistance Received: None
********************************************************************* */
int Round::mexicanSideNeeded()
{
    int side_needed;
    if (!setup.getFromMexicanTrain().checkReverse())
    {
        side_needed = setup.getFromMexicanTrain().getSecondSide();
    }
    else
    {
        side_needed = setup.getFromMexicanTrain().getFirsttSide();
    }
    return side_needed;
}

/* *********************************************************************
Function Name: chooseTrain
Purpose:
       To help human player to choose the good train and good tile to play and find the best train to play for the computer train
Parameters: None
Return Value:
        Train Number 1 for Human Train
        Train Number 2 for Computer Train
        Train Number 3 for Mexican Train
        -1 to Prompt the player to draw from a Boneyard
Local Variables:
        side1, side2, side3 to store owm side needed, opponent side needed and mexican train side needed respectively
        pos1, pos2, pos3 to store the index of the best tile possible for human train, computer trainn and mexican train respectively
Algorithm:
        1. Initialize local variables with the side needed on each human, computer and mexican train
        2. If the player does not have eligible tile to play on required train, it will always return -1 to prompt the player to draw a tile
        3. First check if any train is orphan double, if it is, find if the player has required tiles in hand
        4. If eligible tile is present in player's hand, return the train number that's orphan double else return -1;
        5. If human is playing, make sure to store the information, It's helpful later if they ask for help
        6. If none of the train is orphan double, first find if their is marker in own train or not, it's always better to remove marker earlier
        7. If opponent's train has marker, try playing there
        8. If there's marker and player has eligible tile to play, return the train number of own train.
        9. After that, check if the player has double tile that can be placed on any eligible train or not. If yes, return that particular train number
           where double tile can be played.
        10. If double tile cannot be played on any eligible train, check which train has maximum side value, check if the player has tile with that side value
           If the player has, check what's the highest sum possible tile that a player can play and return the index of that train
       11. If the player has none of the tile on any eligible train to play, return -1 to prompt the player to draw one from the boneyard.
Assistance Received: None
********************************************************************* */
int Round::chooseTrain()
{
    int side1 = ownSideNeeded();
    int side2 = opponentSideNeeded();
    int side3 = mexicanSideNeeded();

    // stores the indices of eligible tile
    int pos1, pos2, pos3 = -1;

    // if human train is orphan double, it's only eligible train to play
    if (ht_odt)
    {
        cout << "Human train is now orphan double and only eligible train to play" << endl;
        if (turn == 2)
        {
            if (player2.findGoodTile(opponentSideNeeded()) >= 0)
            {
                return 1;
            }
        }
        if (turn == 1)
        {
            pos1 = player1.findGoodTile(ownSideNeeded());
            if (pos1 >= 0)
            {
                cout << " Computer Suggests Human to Play ";
                player1.getDemandedTile(pos1).printTiles();
                cout << " from index " << pos1 + 1 << " as it's highest pip tile matching with Orphan Human Train" << endl;
                return 1;
            }
            cout << "Computer Suggests you to draw a tile as you don't matching tiles with that of Orphan Train " << endl;
        }
        return -1;
    }

    // if computer train is orphan double, it's only eligible train to play
    if (ct_odt)
    {
        cout << "Computer train is now orphan double and only eligible train to play" << endl;
        if (turn == 2)
        {
            if (player2.findGoodTile(ownSideNeeded()) >= 0)
            {
                return 2;
            }
        }
        if (turn == 1)
        {
            pos2 = player1.findGoodTile(opponentSideNeeded());
            if (pos2 >= 0)
            {
                cout << " Computer Suggests Human to Play ";
                player1.getDemandedTile(pos2).printTiles();
                cout << "from index " << pos2 + 1 << " as it's highest pip tile matching with Orphan Computer Train" << endl;
                return 2;
            }
            cout << "Computer Suggests you to draw a tile as you don't matching tiles with that of Orphan Train " << endl;
        }
        return -1;
    }

    // If Mexican Train is orphan double, it's the only eligible train to play
    if (mt_odt)
    {
        cout << "Mexican train is now orphan double and only eligible train to play" << endl;
        if (turn == 2)
        {
            if (player2.findGoodTile(mexicanSideNeeded()) >= 0)
            {
                return 3;
            }
        }
        if (turn == 1)
        {
            pos3 = player1.findGoodTile(mexicanSideNeeded());
            if (pos3 >= 0)
            {
                cout << " Computer Suggests Human to Play ";
                player1.getDemandedTile(pos3).printTiles();
                cout << " from index " << pos3 + 1 << " as it's highest pip tile matching with Orphan Mexican Train" << endl;
                return 3;
            }
            cout << "Computer Suggests you to draw a tile as you don't matching tiles with that of Orphan Train " << endl;
        }
        return -1;
    }

    // Human's turn
    if (turn == 1)
    {
        // index position for tiles at hand
        pos1 = player1.findGoodTile(side1);
        pos3 = player1.findGoodTile(side3);
        pos2 = player1.findGoodTile(side2);

        // checks if computer train has marker
        if (has_left_marker)
        {
            if (pos2 >= 0)
            {
                if (player1.getDemandedTile(pos2).checkDouble())
                {
                    cout << "Computer Suggests Human to Play ";
                    player1.getDemandedTile(pos2).printTiles();
                    cout << " from index " << pos2 + 1 << " in Computer Train because it has a marker and you have a double tile" << endl;
                    return 2;
                }
            }
        }
        // if both human train and mexican train are eligible to play
        if ((pos1 >= 0) && (pos3 >= 0))
        {
            // check if double can be placed on any train
            if (player1.getDemandedTile(pos1).checkDouble())
            {
                cout << "Computer Suggests Human to Play ";
                player1.getDemandedTile(pos1).printTiles();
                cout << " from index " << pos1 + 1 << " in Human Train because playing double is helpful to create orphan double...." << endl;
                return 1;
            }
            if (player1.getDemandedTile(pos3).checkDouble())
            {
                cout << "Computer Suggests Human to Play ";
                player1.getDemandedTile(pos3).printTiles();
                cout << " from index " << pos3 + 1 << " in Mexican Train because playing double is helpful to create orphan double...." << endl;
                return 3;
            }
        }
        // if own train has marker and eligible tile to play exists in hand
        if (has_right_marker && pos1 >= 0)
        {
            cout << "Computer Suggests Human to Play ";
            player1.getDemandedTile(pos1).printTiles();
            cout << " from index " << pos1 + 1 << " in Human Train because it has a marker and it's better to resolve the marker earlier." << endl;
            return 1;
        }
        // if computer train has marker and all train are possible to play, check where highest sum pip can be played
        if (has_left_marker)
        {
            if ((pos1 >= 0) && (pos2 >= 0) && (pos3 >= 0))
            {
                if ((side1 > side2) && (side1 > side3))
                {
                    cout << "Computer Suggests Human to Play ";
                    player1.getDemandedTile(pos1).printTiles();
                    cout << " from index " << pos1 + 1 << " in Human Train because it is has high sum of pips." << endl;
                    return 1;
                }
                if ((side2 > side1) && (side2 > side3))
                {
                    cout << "Computer Suggests Human to Play ";
                    player1.getDemandedTile(pos2).printTiles();
                    cout << " from index " << pos2 + 1 << " in Computer Train because it has marker and human has matching tile with high sum of pips." << endl;
                    return 2;
                }
                cout << "Computer Suggests Human to Play ";
                player1.getDemandedTile(pos3).printTiles();
                cout << " from index " << pos3 + 1 << " in Mexican Train because human has a matching tile with high sum of pips." << endl;
                return 3;
            }
        }
        if (has_left_marker)
        {
            if ((pos1 >= 0) && (pos2 >= 0))
            {
                if (side1 > side2)
                {
                    cout << "Computer Suggests Human to Play ";
                    player1.getDemandedTile(pos1).printTiles();
                    cout << " from index " << pos1 + 1 << " in Human Train because it is has high sum of pips." << endl;
                    return 1;
                }
                cout << "Computer Suggests Human to Play ";
                player1.getDemandedTile(pos2).printTiles();
                cout << " from index " << pos2 + 1 << " in Computer Train because it has marker and human has matching tile with high sum of pips." << endl;
                return 2;
            }
        }
        if ((pos1 >= 0) && (pos3 >= 0))
        {
            if (side1 > side3)
            {
                cout << "Computer Suggests Human to Play ";
                player1.getDemandedTile(pos1).printTiles();
                cout << " from index " << pos1 + 1 << " in Human Train because it is has high sum of pips." << endl;
                return 1;
            }
            cout << "Computer Suggests Human to Play ";
            player1.getDemandedTile(pos3).printTiles();
            cout << " from index " << pos3 + 1 << " in Mexican Train because it has marker and human has matching tile with high sum of pips." << endl;
            return 3;
        }
        if (has_left_marker)
        {
            if ((pos3 >= 0) && (pos2 >= 0))
            {
                if (side2 > side3)
                {
                    cout << "Computer Suggests Human to Play ";
                    player1.getDemandedTile(pos2).printTiles();
                    cout << " from index " << pos2 + 1 << " in Computer Train because it has marker and human has matching tile with high sum of pips." << endl;
                    return 2;
                }
                cout << "Computer Suggests Human to Play ";
                player1.getDemandedTile(pos3).printTiles();
                cout << " from index " << pos3 + 1 << " in Mexican Train because human has matching tile with high sum of pips." << endl;
                return 3;
            }
        }
        if (pos1 >= 0)
        {
            cout << "Computer Suggests Human to Play ";
            player1.getDemandedTile(pos1).printTiles();
            cout << " from index " << pos1 + 1 << " in Human Train because it is has high sum of pips." << endl;
            return 1;
        }
        if (has_left_marker)
        {
            if (pos2 >= 0)
            {
                cout << "Computer Suggests Human to Play ";
                player1.getDemandedTile(pos2).printTiles();
                cout << " from index " << pos2 + 1 << " in Computer Train because it has marker and human has matching tile with high sum of pips." << endl;
                return 2;
            }
        }
        if (pos3 >= 0)
        {
            cout << "Computer Suggests Human to Play ";
            player1.getDemandedTile(pos3).printTiles();
            cout << " from index " << pos3 + 1 << " in Mexican Train because human has matching tile with high sum of pips." << endl;
            return 3;
        }
        cout << "You don't have any eligible tile to play in any train. Draw one from the boneyard " << endl;
        return -1;
    }

    // Computer Turn
    if (turn == 2)
    {
        pos2 = player2.findGoodTile(side1);
        pos3 = player2.findGoodTile(side3);

        if (has_left_marker && pos2 >= 0)
        {
            return 2;
        }
        if (has_right_marker && pos1 >= 0)
        {
            pos1 = player2.findGoodTile(side2);
            if (player2.getDemandedTile(pos1).checkDouble())
            {
                return 1;
            }
        }

        if ((pos2 >= 0) && (pos3 >= 0))
        {
            if (player2.getDemandedTile(pos2).checkDouble())
            {
                return 2;
            }
            if (player2.getDemandedTile(pos3).checkDouble())
            {
                return 3;
            }
        }

        if ((pos1 >= 0) && (pos2 >= 0) && (pos3 >= 0))
        {
            if ((side1 > side2) && (side1 > side3))
            {
                return 2;
            }
            if (side2 > side3)
            {
                return 1;
            }
            return 3;
        }
        if ((pos1 >= 0) && (pos2 >= 0))
        {
            if (side1 > side2)
            {
                return 2;
            }
            return 1;
        }
        if ((pos2 >= 0) && (pos3 >= 0))
        {
            if (side1 > side3)
            {
                return 2;
            }
            return 3;
        }
        if ((pos1 >= 0) && (pos3 >= 0))
        {
            if (side2 > side3)
            {
                return 2;
            }
            return 3;
        }
        if (pos3 >= 0)
        {
            return 3;
        }
        if (pos1 >= 0)
        {
            return 1;
        }
        if (pos2 >= 0)
        {
            return 2;
        }
        return -1;
    }
    return -1;
}

/* *********************************************************************
Function Name: userChoosenTrain
Purpose:
       To provide human player an option to get the help with train,
        tile, option to save the game and prompt the human player for input for eligible train to play on
Parameters: None
Return Value:
        Train Number 1 for Human Train
        Train Number 2 for Computer Train
        Train Number 3 for Mexican Train
Local Variables:
        tile_index, own_tile_index, mt_tile_index, op_tile_index, vector of valid input
Algorithm:
        1. Check for all the possible train human can play on and push the indices of the train code to the valid input vector
        2. Push the code for Help and Exit on the vector
        3. Prompt the user for an input if asked for help, provide help from chooseTrain() function
        4. If none of the train are eligible to play because human does not have good tile, prompt the human to draw a tile
        5. If user wants to save the game save the game
Assistance Received: None
********************************************************************* */
int Round::userChosenTrain()
{
    // Tile object
    Tiles train_tile;

    // tile indexs
    int tile_index = -1;

    int own_tile_index = player1.findGoodTile(ownSideNeeded());
    int mt_tile_index = player1.findGoodTile(mexicanSideNeeded());
    int op_tile_index = player1.findGoodTile(opponentSideNeeded());

    int input;
    while (true)
    {
        // int vector to store all the possible train and code for help and exit
        vector<int> valid_input = {};
        cout << "\n<<<<<< Which train you want to play on? Eligible trains are: ";

        // Mexican Orphan Double Train
        if (mt_odt)
        {
            cout << " (3) ORPHAN DOUBLE MEXICAN TRAIN " << endl;
            if (mt_tile_index >= 0)
            {
                valid_input.push_back(3);
            }
            else
            {
                return -1;
            }
        }
        // Human Orphan Double Train
        if (ht_odt)
        {
            cout << " (1) ORPHAN DOUBLE HUMAN TRAIN " << endl;
            if (own_tile_index >= 0)
            {
                valid_input.push_back(1);
            }
            else
            {
                return -1;
            }
        }
        // Computer Orphan Double train
        if (ct_odt)
        {
            cout << " (2) ORPHAN DOUBLE COMPUTER TRAIN " << endl;
            if (op_tile_index >= 0)
            {
                valid_input.push_back(2);
            }
            else
            {
                return -1;
            }
        }

        // If orphan double does not exist
        if ((!mt_odt && !ct_odt && !ht_odt))
        {
            if (own_tile_index >= 0)
            {
                cout << " 1(Human Train) ";
                valid_input.push_back(1);
            }
            if (mt_tile_index >= 0)
            {
                cout << " 3(Mexican Train) ";
                valid_input.push_back(3);
            }
            // push train code for opponent train too if it has a marker
            if (has_left_marker)
            {
                if (op_tile_index >= 0)
                {
                    cout << " 2(Computer Train) ";
                    valid_input.push_back(2);
                }
            }
            if ((!has_left_marker) && (own_tile_index < 0) && (mt_tile_index < 0))
            {
                return -1;
            }
            if ((op_tile_index < 0) && (mt_tile_index < 0) && (own_tile_index < 0))
            {
                return -1;
            }
        }
        valid_input.push_back(4);
        valid_input.push_back(5);
        valid_input.push_back(6);

        cout << ">>>>>>> \n <<<<<<<<<<<<<<<< PRESS 4 FOR HELP ON CHOOSING TRAIN AND TILES...  AND 5 IF YOU WANNA EXIT THE GAME >>>>>>>>>>>>>>>>: \n"
             << endl;
        cout << ">>>>>>>>> Press 6 if you want to save the game <<<<<<<<<<" << endl;

        /// ask for an input
        cin >> input;

        // validate the user input
        if (cin.fail())
        {
            cout << "\nERROR -- You did not enter a valid number \n ";

            cin.clear();

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (std::find(valid_input.begin(), valid_input.end(), input) != valid_input.end())
        {

            if (input == 1)
            {
                return 1;
            }
            else if (input == 2)
            {
                return 2;
            }
            else if (input == 3)
            {
                return 3;
            }
            else if (input == 4)
            {
                cout << "####################################################################################################\n";
                chooseTrain();
                cout << "####################################################################################################\n";
                continue;
            }
            else if (input == 5)
            {
                exit(1);
            }
            else if (input == 6)
            {
                saveGame(human_score, computer_score);
            }
            break;
        }
        cout << "Please enter valid input only: " << endl;
        continue;
    }
    return -1;
}

/* *********************************************************************
Function Name: setOrphanDouble
Purpose:
       To set the orphan double train
Parameters: None
Return Value: None
Local Variables: None
Algorithm:
        1. Check for the setup train after player played, if there's double tile it's orphan double
        2. Check for the Mexican Train after player played, if there's double tile, it's orphan double
Assistance Received: None
********************************************************************* */
void Round::setOrphanDouble()
{
    if (setup.getLeft().getFirsttSide() != engine)
    {
        if (setup.getLeft().checkDouble())
        {
            ct_odt = true;
        }
        else
        {
            ct_odt = false;
        }
    }

    if ((setup.getRight().getFirsttSide() != engine) && (setup.getRight().getFirsttSide() != engine))
    {
        if (setup.getRight().checkDouble())
        {
            ht_odt = true;
        }
        else
        {
            ht_odt = false;
        }
    }

    if (setup.getFromMexicanTrain().getFirsttSide() != engine)
    {
        if (setup.getFromMexicanTrain().checkDouble())
        {
            mt_odt = true;
        }
        else
        {
            mt_odt = false;
        }
    }
}

/* *********************************************************************
Function Name: playTurn
Purpose:
       To play on own turn
Parameters: Pointer to an either human or computer player
Return Value: None
Local Variables: None
Algorithm:
        1. Play on own turn. If eligible tile exist for eligible train, play it. If it does not draw one from the boneyard
        2. adjust the marker if a player could not play drawn tiles and add it to the hand
        3. Check if hand tiles can be played on any eligible train, if not draw a tile, if drawn tile can be played, play else, set marker and pass the turn
        4. If double tile played by player, play again! if twice double, check if next tile to be played is in hand
        5. Set OrphanDouble upon necesary
Assistance Received: None
********************************************************************* */
void Round::playTurn(Player *player)
{
    // Human turn
    if (turn == 1)
    {
        // tile object
        Tiles train_tile;
        // tile index
        int tile_index;

        // prompt user to choose train
        int i = userChosenTrain();

        // if none of the train was eligible, prompt the human to draw a tile
        if (i == -1)
        {
            system("read -n 1 -s -p \"Human does not have any matching tile for any eligible train to play. Press any key to draw from a boneyard\"");

            // tompost tile from the boneyard
            Tiles t = deck.getFromBoneyard();

            // add to player's hand
            player->addTilesToHand(t);
            printDetails();

            // see if the drawn tile can be played
            int j = chooseTrain();

            // play if it can be played
            if (j >= 0)
            {
                cout << "Human drew a matching tile ";
                t.printTiles();
                cout << " from the boneyard" << endl;
                cout << "\nHuman Turn:\n";
                turn = 1;
                playTurn(&player1);
            }
            // if it can't be played, set the marker and change the turn
            else
            {
                cout << "Human drew a tile ";
                t.printTiles();
                cout << " from the boneyard" << endl;
                has_right_marker = true;
                printDetails();
                cout << "Human drawn Tiles";
                t.printTiles();
                cout << "cannot be played so passing Human's turn! " << endl;
                turn = 2;
            }
        }
        else
        {
            // Human train
            if (i == 1)
            {
                tile_index = player->selectTiles(ownSideNeeded());
                train_tile = player->getDemandedTile(tile_index);
                if (train_tile.getSecondSide() == ownSideNeeded())
                {
                    train_tile.reverseTile();
                }
                setup.insertRight(train_tile);
                has_right_marker = false;
                player->deleteTilesFromHand(tile_index);
                printDetails();
                if (train_tile.checkDouble())
                {
                    cout << "Human just played double tile";
                    train_tile.printTiles();
                    cout << "on Human side";
                    playTurn(&player1);
                }
                else
                {
                    turn = 2;
                    cout << "Human just played tile";
                    train_tile.printTiles();
                    cout << "on Human side";
                }
            }
            // Computer train
            if (i == 2)
            {
                tile_index = player->selectTiles(opponentSideNeeded());
                train_tile = player->getDemandedTile(tile_index);
                if (train_tile.getFirsttSide() == opponentSideNeeded())
                {
                    train_tile.reverseTile();
                }
                setup.insertLeft(train_tile);
                player->deleteTilesFromHand(tile_index);
                printDetails();
                if (train_tile.checkDouble())
                {
                    cout << "Human just played double tile";
                    train_tile.printTiles();
                    cout << "on Computer side";
                    playTurn(&player1);
                }
                else
                {
                    turn = 2;
                    cout << "Human just played tile";
                    train_tile.printTiles();
                    cout << "on Computer side";
                }
            }
            // Mexican Train
            if (i == 3)
            {
                tile_index = player->selectTiles(mexicanSideNeeded());
                train_tile = player->getDemandedTile(tile_index);
                if (train_tile.getSecondSide() == mexicanSideNeeded())
                {
                    train_tile.reverseTile();
                }
                setup.insertInMexicanTrain(train_tile);
                player->deleteTilesFromHand(tile_index);
                printDetails();
                if (train_tile.checkDouble())
                {
                    cout << "Human just played double tile";
                    train_tile.printTiles();
                    cout << "on Mexican train ";
                    playTurn(&player1);
                }
                else
                {
                    turn = 2;
                    cout << "Human just played tile";
                    train_tile.printTiles();
                    cout << "on Mexican train";
                }
            }
        }
    }
    // Computer Turn
    else
    {
        // tile object
        Tiles train_tile;

        // tile index
        int tile_index;

        // check if any train is eligible to play
        int n = chooseTrain();

        // draw a tile if none of the tiles can be played in any eligible train
        if (n == -1)
        {
            system("read -n 1 -s -p \"Computer does not have any matching tile for any eligible train to play, so drawing tiles from boneyard... Press any key to see what happens next\"");
            Tiles t = deck.getFromBoneyard();

            // add to hand
            player->addTilesToHand(t);
            printDetails();
            cout << "Computer drew a tile ";
            t.printTiles();
            cout << "from the boneyard" << endl;

            //check if the drawn tile can be played
            int j = chooseTrain();
            if (j >= 0)
            {
                cout << "\nComputer Turn:\n";
                cout << "Matching tile drawn from the boneyard. Computer can now play his turn" << endl;
                playTurn(&player2);
            }
            // set marker
            else
            {
                turn = 1;
                has_left_marker = true;
                printDetails();
                cout << "Computer drawn  tile ";
                t.printTiles();
                cout << " could not be played so computer passed it's turn " << endl;
            }
        }
        else
        {
            // Human Train
            if (n == 1)
            {
                tile_index = player->findGoodTile(opponentSideNeeded());

                train_tile = player->getDemandedTile(tile_index);
                if (train_tile.getSecondSide() == opponentSideNeeded())
                {
                    train_tile.reverseTile();
                }
                system("read -n 1 -s -p \"Press any key to continue...\"");
                setup.insertRight(train_tile);
                player->deleteTilesFromHand(tile_index);
                printDetails();
                if (train_tile.checkDouble())
                {
                    cout << "Computer choose to play double tile";
                    train_tile.printTiles();
                    cout << "on Human side because it has a marker and computer has matching double tile";
                    playTurn(&player2);
                }
                else
                {
                    turn = 1;
                    cout << "Computer choose to play tile";
                    train_tile.printTiles();
                    cout << "on Human side because it has marker and computer has matching tile with high pip sum";
                }
            }
            // Computer Train
            else if (n == 2)
            {
                tile_index = player->findGoodTile(ownSideNeeded());
                train_tile = player->getDemandedTile(tile_index);

                if (train_tile.getFirsttSide() == ownSideNeeded())
                {
                    train_tile.reverseTile();
                }
                system("read -n 1 -s -p \"Press any key to continue...\"");
                setup.insertLeft(train_tile);
                has_left_marker = false;
                player->deleteTilesFromHand(tile_index);
                printDetails();
                if (train_tile.checkDouble())
                {
                    cout << "Computer choose to play double tile";
                    train_tile.printTiles();
                    cout << "on its own side because it has a matching double tile" << endl;
                    playTurn(&player2);
                }
                else
                {
                    turn = 1;
                    cout << "Computer played tiles ";
                    train_tile.printTiles();
                    cout << "in it's own train because based on the high sum of pip" << endl;
                }
            }
            // Mexican Train
            else if (n == 3)
            {
                tile_index = player->findGoodTile(mexicanSideNeeded());

                train_tile = player->getDemandedTile(tile_index);
                if (train_tile.getSecondSide() == mexicanSideNeeded())
                {
                    train_tile.reverseTile();
                }
                system("read -n 1 -s -p \"Press any key to continue...\"");
                setup.insertInMexicanTrain(train_tile);
                player->deleteTilesFromHand(tile_index);
                printDetails();
                if (train_tile.checkDouble())
                {
                    cout << "Computer choose to play double tile";
                    train_tile.printTiles();
                    cout << "on Mexican side because computer has matching double tile with that of Mexican train";
                    playTurn(&player2);
                }
                else
                {
                    turn = 1;
                    cout << "Computer played tiles ";
                    train_tile.printTiles();
                    cout << "in Mexican train because it has got matching tile with high sum of pips" << endl;
                }
            }
        }
    }
    // Set Orphan Double if necessary
    setOrphanDouble();
}

/* *********************************************************************
Function Name: getTileFromBoneyard
Purpose:
       To get the topmost tile from the boneyard
Parameters: None
Return Value: Tile object, topmost tile from boneyard
Local Variables: None
Algorithm:
        1. Use utility function to get topmost tile from the boneyard
Assistance Received: None
********************************************************************* */
Tiles Round::getTileFromBoneyard()
{
    return deck.getFromBoneyard();
}

/* *********************************************************************
Function Name: getHumanScore
Purpose:
       To calculate and get Human's score
Parameters: None
Return Value: integer, human's score
Local Variables: None
Algorithm:
        1. Use utility function to calculate human's score
Assistance Received: None
********************************************************************* */
int Round::getHumanScore()
{
    return player1.calculateScore();
}

/* *********************************************************************
Function Name: getComputerScore
Purpose:
       To calculate and get Computer's score
Parameters: None
Return Value: integer, computer's score
Local Variables: None
Algorithm:
        1. Use utility function to calculate computer's score
Assistance Received: None
********************************************************************* */
int Round::getComputerScore()
{
    return player2.calculateScore();
}

/* *********************************************************************
Function Name: isBoneyardEmpty
Purpose:
       To check if the boneyard is empty
Parameters: None
Return Value: Boolean Value true if empty
Algorithm:
        1. Use utility function to check if the boneyard is empty
Assistance Received: None
********************************************************************* */
bool Round::isBoneyardEmpty()
{
    return (deck.getDeck()).empty();
}

/* *********************************************************************
Function Name: saveGame
Purpose:
       to save the game upon the request of the user
Parameters: None
Return Value: None
Algorithm:
        1. Get the name of the save file from the user
        2. Open the file, write all information that needs to be saved, and close the file.
Assistance Received: None
********************************************************************* */
void Round::saveGame(int &score1, int &score2)
{
    string file_name;
    cout << "Please enter the file name where you want to save you game: " << endl;
    cin >> file_name;
    file_name.append(".txt");
    ofstream save_game;
    save_game.open(file_name);
    save_game << "Round: " << num_round << "\n\n";
    save_game << "Computer:\n";
    save_game << "Score: " << score1 << "\n";
    save_game << "Hand: ";
    for (int i = 0; i < player1.getHand().getHandSize(); i++)
    {
        save_game << player1.getHand().getHandTiles()[i].getFirsttSide() << "-" << player1.getHand().getHandTiles()[i].getSecondSide() << " ";
    }
    save_game << "\n";
    save_game << "Train: ";
    int i = 0;
    if (has_left_marker)
    {
        save_game << "M ";
    }

    int second_loop;

    for (int i = 0; i < setup.getTrainTiles().size(); i++)
    {
        if (setup.getTrainTiles()[i].getFirsttSide() == engine && setup.getTrainTiles()[i].getSecondSide() == engine)
        {
            second_loop = i;
            break;
        }
        else
        {
            save_game << getSetup().getTrainTiles()[i].getFirsttSide() << "-" << getSetup().getTrainTiles()[i].getFirsttSide() << " ";
        }
    }

    save_game << engine << "-" << engine;

    save_game << "\n\n";

    save_game << "Human:\n";
    save_game << "Score: " << score2 << "\n";
    save_game << "Hand: ";
    for (int i = 0; i < player2.getHand().getHandSize(); i++)
    {
        save_game << player2.getHand().getHandTiles()[i].getFirsttSide() << "-" << player2.getHand().getHandTiles()[i].getSecondSide() << " ";
    }
    save_game << "\n";
    save_game << "Train: ";

    for (int j = second_loop; j < setup.getTrainTiles().size(); j++)
    {
        save_game << getSetup().getTrainTiles()[j].getFirsttSide() << "-" << getSetup().getTrainTiles()[j].getSecondSide() << " ";
    }
    if (has_right_marker)
    {
        save_game << "M\n\n";
    }

    save_game << "Mexican Train: ";
    for (int j = 0; j < setup.getMexicanTrain().size(); j++)
    {
        save_game << setup.getMexicanTrain()[j].getFirsttSide() << "-" << setup.getMexicanTrain()[j].getSecondSide() << " ";
    }
    save_game << "\n\n";
    save_game << "Boneyard: ";
    for (int j = 0; j < deck.getDeck().size(); j++)
    {
        save_game << deck.getDeck()[j].getFirsttSide() << "-" << deck.getDeck()[j].getSecondSide() << " ";
    }
    save_game << "\n";

    if (turn == 1)
    {
        save_game << "Next Player: Computer"
                  << "\n";
    }
    else
    {
        save_game << "Next Player: Human"
                  << "\n";
    }
    save_game << "\n";
    save_game.close();

    cout << "Your Game has been saved" << endl;
}

