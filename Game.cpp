/*
*****************************************************************
* Name:         Sagar Neupane                                   *
* Project:      1. Mexican Train C++                            *
* Class:        CMPS 366, Organization of Programming Language  *
* Date:         10/22/2021                                      *
*****************************************************************
*/

#include "Game.hpp"
#include "Tiles.hpp"
#include <fstream>
#include <string>
#include <sstream>

// Utility Functions prototype to extract the file
Tiles parseTiles(string userInput);
vector<string> parseVector(string test);
deque<string> parseDeque(string test);

/* *********************************************************************
Function Name: Game
Purpose: Default Constructor to initialize member variables
Parameters: None
Return Value: None
Local Variables:
Algorithm: None
Assistance Received: None
********************************************************************* */
Game::Game()
{
    round_number = 1;
    human_score = 0;
    computer_score = 0;
    playing_round = 1;
    winner = "";
}

/* *********************************************************************
Function Name: playGame
Purpose:
    To play the game with or without loading the file
Parameters: None
Return Value: None
Local Variables: Round object round
Algorithm:
        1. Check if the file was loaded, if it was, adjust round accordingly
        2. Intialize round object with round number, Print Details
        3. Set Hands, Boneyard, Turn, Marker and Orphan Double status accordingly
        4. call for new round
Assistance Received: None
********************************************************************* */
void Game::playGame()
{
    cout << "\n--------------------------------------------🎬🎬🎬🎬WELCOME TO THE MEXICAN TRAIN🎬🎬🎬🎬------------------------------------------------\n";

    // if loading file was successful
    if (loadFile())
    {
        playing_round = round_number;
    }

    // create a round class object
    Round round(playing_round);

    round.setHumanScore(human_score);
    round.setComputerScore(computer_score);
    
    cout << "\nGAME STANDING:\n"
         << endl;
    cout << "Human Score:     " << setw(10) << human_score << endl;
    cout << "Computer Score:  " << setw(10) << computer_score << endl;
    cout << endl;

    // if the file was loadedd
    if (loadedFromFile)
    {
        // Set the hands for players, boneyard and turn
        cout << "\nLoading Successful.. Resuming the game" << endl;
        round.setComputerHand(computer_hand);
        round.setHumanHand(human_hand);
        round.setDeckBoneyard(boneyard);
        round.setTurn(play_turn);

        // Set the marker if necessary
        if (left_mark)
        {
            round.setLeftMarker(true);
        }
        if (right_mark)
        {
            round.setRighttMarker(true);
        }

        // set the orphan double status upon validity
        if (setup_train[0].getFirsttSide() == setup_train[0].getSecondSide())
        {
            round.setOrphanDouble_C(true);
        }
        if (setup_train[setup_train.size() - 1].getFirsttSide() == setup_train[setup_train.size() - 1].getSecondSide())
        {
            round.setOrphanDouble_H(true);
        }

        // set the train setup
        round.setSetup(setup_train);

        // set the mexican train setup
        round.setMexicanTrain(mexican_setup);

        // print the round details on the screen
        round.printDetails();
    }
    else
    {
        // set hand tiles shuffles the deck, distribute tiles to the players and sets the train
        round.setHandTiles();
        round.printDetails();

        // temp variable
        int start;

        // coin toss
        int head_tail;
        cout << "Score is draw so far. Press 1 for Head, 2 for Tails? " << endl;
        if (human_score < computer_score)
        {
            round.setTurn(1);
        }
        else if (human_score > computer_score)
        {
            round.setTurn(2);
        }
        else
        {
            int temp;
            head_tail = rand() % 2 + 1;

            cin >> temp;

            // Input Validation
            if (cin.fail())
            {
                cout << "ERROR -- You did not enter a valid number ";

                cin.clear();

                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            if (temp == head_tail)
            {
                cout << "Human won the toss, so Human playing first...." << endl;
                round.setTurn(1);
            }
            else
            {
                cout << "Human lost the toss, so Computer playing first...." << endl;
                round.setTurn(2);
            }
        }
    }

    // temp variable
    int n = -1;

    // play game until the game is not over
    while (!round.isGameOver())
    {
        n = round.findTurn();
    }

    // Print Details for the round and  Update Scoress
    cout << "\n--------------------------------------------🎬🎬🎬🎬END OF MEXICAN TRAIN GAME🎬🎬🎬🎬------------------------------------------------\n";
    cout << "\n ROUND: " << playing_round << " STANDING: \n " << endl;

    // Human's hand empty means game ended
    if (round.isHumanHandEmpty())
    {
        cout << "\n......Human played all his tiles...........\n"
             << endl;
        cout << "Human Score: " << round.getHumanScore() << endl;
        human_score += round.getHumanScore();
        computer_score += round.getComputerScore();
        cout << "Computer Score: " << round.getComputerScore() << endl;
        winner = "Human";
        cout << "\nWinner of the Round: " << winner << "🏆🥇🙌🏻\n"
             << endl;
        round.setTurn(1);
    }

    // Computer's hand empty means game ended
    if (round.isComputerHandEmpty())
    {
        cout << "\n......Computer played all its tiles...........\n"
             << endl;
        cout << "Human Score: " << round.getHumanScore() << endl;
        human_score += round.getHumanScore();
        computer_score += round.getComputerScore();
        cout << "Computer Score: " << round.getComputerScore() << endl;
        winner = "Computer";
        cout << "\nWinner of the Round: " << winner << "🏆🥇🙌🏻\n"
             << endl;
        round.setTurn(2);
    }

    // Boneyard empty means game ended
    if (round.isBoneyardEmpty())
    {
        cout << ".........NO MORE TILES LEFT IN THE BONEYARD, GAME ENDED!!........... \n"
             << endl;
        int human_point = round.getHumanScore();
        int computer_point = round.getComputerScore();

        if (human_point < computer_point)
        {
            cout << "Human Score: " << round.getHumanScore() << endl;
            human_score += round.getHumanScore();
            computer_score += round.getComputerScore();
            cout << "Computer Score: " << round.getComputerScore() << endl;
            winner = "Human";
            cout << "\nWinner of the Round: " << winner << "🏆🥇🙌🏻\n"
                 << endl;
            round.setTurn(1);
        }
        else if (human_point > computer_point)
        {
            cout << "Human Score: " << round.getHumanScore() << endl;
            human_score += round.getHumanScore();
            computer_score += round.getComputerScore();
            cout << "Computer Score: " << round.getComputerScore() << endl;
            winner = "Computer";
            cout << "\nWinner of the Round: " << winner << "🏆🥇🙌🏻\n"
                 << endl;
            round.setTurn(2);
        }
        else
        {
            cout << "......GAME was a draw....." << endl;
            human_score += human_point;
            computer_score += computer_point;
        }
    }
    printGameDetails();
    askForAnotherRound();
    loadedFromFile = false;
}

/* *********************************************************************
Function Name: askForAnotherRound
Purpose:
    To ask if the user wanna play another round
Parameters: None
Return Value: None
Local Variables:
Algorithm:
    1. Ask the user if they wanna play another round, start fresh game with updated score and round number if they want
       calling playGame function
Assistance Received: None
********************************************************************* */
void Game::askForAnotherRound()
{
    while (true)
    {
        cout << "Do you want to play another round?? Press 1 if you want, 2 if you don't and want to exit the game... " << endl;
        int temp;
        cin >> temp;

        if (cin.fail())
        {
            cout << "ERROR -- You did not enter a valid number ";

            cin.clear();

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (temp == 1)
        {
            playing_round++;
            playGame();
            break;
        }
        else if (temp == 2)
        {
            cout << "GOOD BYE!!!😇" << endl;
            exit(1);
        }
        else
        {
            continue;
        }
    }
}

/* *********************************************************************
Function Name: printGameDetails
Purpose:
    To print game details to the screen
Parameters: None
Return Value: None
Local Variables:
Algorithm:
    1. Print details
Assistance Received: None
********************************************************************* */
void Game::printGameDetails()
{
    cout << "\n-------------------------------------------------👏🏻👏🏻👏🏻👏🏻WELL PLAYED 👏🏻👏🏻👏🏻👏🏻👏🏻------------------------------------------------------\n";
    cout << "\nGAME STANDING:\n"
         << endl;
    cout << "Human Score:     " << setw(10) << human_score << endl;
    cout << "Computer Score:  " << setw(10) << computer_score << endl;
    cout << endl;
    cout << "\n-------------------------------------------------👏🏻👏🏻👏🏻👏🏻WELL PLAYED 👏🏻👏🏻👏🏻👏🏻👏🏻------------------------------------------------------\n\n";
}

/* *********************************************************************
Function Name: loadFile
Purpose:
    loadFile and set the utility variables accordingly
Parameters: None
Return Value: boolean variable if the game to be loaded or not
Local Variables:
Algorithm:
    1. Ask user if they want to load a saved game, if yes load and set the temporary utility variables
    2. re
Assistance Received: None
********************************************************************* */
bool Game::loadFile()
{
    while (true)
    {

        cout << "Do you want to load a file? Press 1 if you want. 2 if you don't...." << endl;

        int temp;
        cin >> temp;

        // Input validation

        if (cin.fail())
        {
            cout << "ERROR -- You did not enter a valid number ";

            cin.clear();

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (temp == 1)
        {
            // get fileName;
            string file_name;
            cout << "Enter the file name: " << endl;
            cin >> file_name;

            // temp to store computer, human hand, setup and boneyard
            vector<string> c_hand;
            vector<string> h_hand;
            deque<string> t1_setup;
            deque<string> t2_setup;
            vector<string> mt_setup;
            vector<string> b_yard;

            string test;
            int rN = 0;
            int cS = 0;
            int hS = 0;

            ifstream file_open(file_name);

            if (!file_open)
            {
                cout << "Error Opening the file" << endl;
                system("read -n 1 -s -p \"Press any key to exit: \"");
                exit(1);
            }

            // temps
            string str1, str2, str3, str4;
            int a;
            string line;

            // get Round Number;
            getline(file_open, line);
            istringstream ss_rn(line);
            ss_rn >> str1 >> a;
            cout << str1 << endl;
            rN = a;

            // skipping lines
            getline(file_open, line);
            getline(file_open, line);

            // getting computer score
            getline(file_open, line);
            istringstream ss_sc(line);

            ss_sc >> str1 >> a;
            cS = a;

            // getting computer Hands
            getline(file_open, line);
            int pos4 = line.find(":");

            // Copy substring before pos
            test = line.substr(pos4 + 2);

            c_hand = parseVector(test);
            for (int i = 0; i < c_hand.size(); i++)
            {
                computer_hand.push_back(parseTiles(c_hand[i]));
            }

            // getting computer train
            getline(file_open, line);
            int pos6 = line.find(":");

            test = line.substr(pos6 + 2);

            t1_setup = parseDeque(test);
            int count = 0;
            if (t1_setup[0] == "M")
            {
                left_mark = true;
                count = 1;
            }
            for (int i = count; i < t1_setup.size(); i++)
            {
                setup_train.push_back(parseTiles(t1_setup[i]));
            }

            // skip two lines
            getline(file_open, line);
            getline(file_open, line);

            // get human score
            getline(file_open, line);
            istringstream ss_hc(line);
            ss_hc >> str1 >> a;
            hS = a;

            // get Human Hands
            getline(file_open, line);
            int pos3 = line.find(":");

            // Copy substring before pos
            test = line.substr(pos3 + 2);

            h_hand = parseVector(test);
            for (int i = 0; i < h_hand.size(); i++)
            {
                human_hand.push_back(parseTiles(h_hand[i]));
            }

            // getting human train
            getline(file_open, line);
            int pos5 = line.find(":");

            // Copy substring before pos
            test = line.substr(pos5 + 2);

            t2_setup = parseDeque(test);
            int index = t2_setup.size();
            if (t2_setup[t2_setup.size() - 1] == "M")
            {
                index = t2_setup.size() - 1;
                right_mark = true;
            }

            for (int i = 1; i < index; i++)
            {
                setup_train.push_back(parseTiles(t2_setup[i]));
            }

            // skips line
            getline(file_open, line);

            // getMexicanTrainSetup
            getline(file_open, line);

            // Find position of ':' using find()
            int pos = line.find(":");

            // Copy substring before pos
            test = line.substr(pos + 2);

            mt_setup = parseVector(test);

            for (int i = 0; i < mt_setup.size(); i++)
            {
                mexican_setup.push_back(parseTiles(mt_setup[i]));
            }

            // skips line
            getline(file_open, line);

            // gets boneyard
            getline(file_open, line);
            int pos2 = line.find(":");

            // Copy substring before pos
            test = line.substr(pos2 + 2);

            b_yard = parseVector(test);

            for (int i = 0; i < b_yard.size(); i++)
            {
                boneyard.push_back(parseTiles(b_yard[i]));
            }

            // skips a line
            getline(file_open, line);

            // get next player
            getline(file_open, line);
            istringstream ss_np(line);
            ss_np >> str1 >> str2 >> str3;

            if ((str3.compare("Computer")) == 0)
            {
                play_turn = 2;
            }
            else
            {
                play_turn = 1;
            }

            // parameters
            round_number = rN;
            human_score = hS;
            computer_score = cS;
            loadedFromFile = true;

            return true;
            break;
        }
        else if (temp == 2)
        {
            loadedFromFile = false;
            break;
        }
        else
        {
            cout << "Please enter the valid Input only: 1 to load a file and 2 if you don't" << endl;
            continue;
        }
    }
    return false;
}

/* *********************************************************************
Function Name: parseVector
Purpose:
    to parse through the text and store the tiles in a vector
Parameters: None
Return Value: c_hand
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
vector<string> parseVector(string test)
{
    vector<string> c_hand;
    string str;

    stringstream player_hand(test);

    while (player_hand >> str)
    {
        c_hand.push_back(str);
    }
    return c_hand;
}

/* *********************************************************************
Function Name: parseDeque
Purpose:
    to parse through the text and store the tiles in a deque
Parameters: None
Return Value: c_tiles
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
deque<string> parseDeque(string test)
{
    // deque to store tiles
    deque<string> c_tiles;
    string temp;

    stringstream player_hand(test);

    while (player_hand >> temp)
    {
        c_tiles.push_back(temp);
    }
    return c_tiles;
}

/* *********************************************************************
Function Name: parseTiles
Purpose:
    to parse through the text and extract tiles and return them
Parameters: None
Return Value: tile object
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
Tiles parseTiles(string test)
{
    // changing string to Tiles and returning the Tiles
    return Tiles(stoi(test.substr(0, 1)), stoi(test.substr(2, 1)));
}
