/*
* File:   MP3Final.cpp
* Author: Calista Grantham
* Date:   11/10/2022
*
* Description: A two player tic-tac-toe game that displays game stats and
*			   can be played infinitely until the users no longer wish to play.
*/

#include <iostream>
#include <string>
using namespace std;

int getPlayerInput(string playerName);
/*
getPlayerInput - uses the playerName to ask for location input
@param playerName - string of player 1 or 2's chosen name for the game
@return playerInput - returns an integer 1-9 of what the player chose
*/

bool isLegalMove(char board[], int location);
/*
isLegalMove - boolean function that checks whether or not the player's chosen location
			  on the board has already been used
@param board[] - character array of the board's potential locations 0-8
@location - integer 1-9 of the player's selected location input on the board
@returns true if the location has not already been used, false if the location has been used
*/

void placeMarkOnBoard(char board[], char playerMark, int location);
/*
placeMarkOnBoard - function which places 'X' or 'O' on the players specified location on the board
@param board[] - character array of the potential board locations 1-9
@param playerMark - character 'X' or 'O' for the respective player
@param location - integer
*/

void clearBoard(char board[]);
/*
clearBoard - function that replaces any player marks on the board with the original numbers
@param board[] - character array of the potential board locations 1-9
*/

bool hasThreeInRow(char board[], char playerMark);
/*
hasThreeInRow - bool function that checks whether or not a player has achieved a three in a row
@param board[] - character array of the potential board locations 1-9
@param playerMark - character 'X' or 'O' depending on which player's turn it is
@returns true if there is a three in a row present and false if there is not
*/

void displayBoard(char board[]);
/*
displayBoard - function that outputs the tic tac toe board with the potential player mark locations and current marks
@param board[] - character array of the potential board locations 1-9
*/

void displayGameStats(int ties, int player1Score, int player2Score);
/*
displayGameStats - function that outputs the number of games player 1 and 2 have won as well as the number of ties after each completed game
@param ties - integer count of how many ties have happened
@param player1Score - integer count of how many times player 1 has won
@param player2Score - integer count of how many times player 2 has won
*/

bool keepPlaying(char newRoundInput);
/*
keepPlaying - bool function that takes user input on whether or not to play another game
@param newRoundInput - character for user input
@returns true if the player inputs 'P' or 'p' and false if the player inputs 'Q' or 'q'
*/

int main()
{
	// array definition
	const int SIZE = 9;
	char board[SIZE] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	// variable declarations and initializations
	int possibleTurns = 9;
	char playerMark = 'X';
	int location = 0;
	int inputResult;
	int ties = 0;
	int player1Score = 0;
	int player2Score = 0;
	int loopIteration = 0;
	string playerName;
	string player1Name;
	string player2Name;
	char newRoundInput = ' ';


	// output and input to get player's usernames
	cout << "Player 1, please enter your username: ";
	cin >> player1Name;
	cout << "Player 2, please enter your username: ";
	cin >> player2Name;
	cout << endl;

	// outer do loop which runs until the end of a game and then prompts the user to play again or quit
	do
	{
		// inner do loop which runs player 1 and 2's turns until someone wins or there is a tie
		do
		{
			// loopIteration tracks how many turns have been made (player 1 and 2 together)
			loopIteration++;

			// player 1's turn
			// set the name and mark to player 1's
			playerName = player1Name;
			playerMark = 'X';

			// displays up to date board
			displayBoard(board);
			cout << endl;

			// get player input for a board location that is a legal move
			do
			{
				inputResult = (getPlayerInput(playerName));
			} while (isLegalMove(board, inputResult) == false);

			// place player 1's 'X' on the selected location on the board 
			placeMarkOnBoard(board, playerMark, inputResult);

			/* check if player 1 has gotten three in a row,
			   if true then add 1 point to their score, display the game stats and end the current game */
			if (hasThreeInRow(board, playerMark))
			{
				player1Score++;
				displayGameStats(ties, player1Score, player2Score);
				break;
			}

			/* if statement to check if the limit of possible turns has been reached,
			   add to tie count, display game stats and end game if true */
			if (loopIteration == 5)
			{
				ties++;
				displayGameStats(ties, player1Score, player2Score);
				break;
			}

			// player 2's turn
			playerName = player2Name;
			playerMark = 'O';

			// displays up to date board
			cout << endl;
			displayBoard(board);
			cout << endl;

			// get player input for a board location that is a legal move
			do
			{
				inputResult = (getPlayerInput(playerName));
			} while (isLegalMove(board, inputResult) == false);

			// place player 2's 'O' on the selected location on the board
			placeMarkOnBoard(board, playerMark, inputResult);
			cout << endl;

			/* check if player 2 has gotten three in a row,
			   if true then add 1 point to their score, display the game stats and end the current game */
			if (hasThreeInRow(board, playerMark))
			{
				player2Score++;
				displayGameStats(ties, player1Score, player2Score);
				break;
			}

		} while (hasThreeInRow(board, playerMark) == false);

		// reset the tic-tac-toe board and number of turns before potentially starting a new game
		clearBoard(board);
		loopIteration = 0;

	} while (keepPlaying(newRoundInput));

	return 0;
}

// function definitions

int getPlayerInput(string playerName)
{
	int playerInput = 0;
	// prompt for input until an integer between 1 and 9 is provided
	while (playerInput < 1 || playerInput > 9)
	{
		cout << playerName << ", please choose an empty space on the board 1-9: ";
		cin >> playerInput;
	}
	return playerInput - 1;
}

bool isLegalMove(char board[], int location)
{
	// check if the chosen location hs already been taken
	if (board[location] == 'X' || board[location] == 'O')
	{
		return false;
	}
	return true;
}

void placeMarkOnBoard(char board[], char playerMark, int location)
{
	// place the player's mark on the selected board location
	board[location] = playerMark;
}

void clearBoard(char board[])
{
	// for loop to reset the board to the original format using ASCII values
	for (int i = 0; i < 9; i++)
	{
		board[i] = i + 49;
	}
}

bool hasThreeInRow(char board[], char playerMark)
{
	// if branches for testing horizontal three in a rows
	if (board[0] == playerMark && board[1] == playerMark && board[2] == playerMark)
	{
		return true;
	}
	if (board[3] == playerMark && board[4] == playerMark && board[5] == playerMark)
	{
		return true;
	}
	if (board[6] == playerMark && board[7] == playerMark && board[8] == playerMark)
	{
		return true;
	}

	// if branches for testing vertical three in a rows
	if (board[0] == playerMark && board[3] == playerMark && board[6] == playerMark)
	{
		return true;
	}
	if (board[1] == playerMark && board[4] == playerMark && board[7] == playerMark)
	{
		return true;
	}
	if (board[2] == playerMark && board[5] == playerMark && board[8] == playerMark)
	{
		return true;
	}

	// if branches for testing diagonal three in a rows
	if (board[6] == playerMark && board[4] == playerMark && board[2] == playerMark)
	{
		return true;
	}
	if (board[0] == playerMark && board[4] == playerMark && board[8] == playerMark)
	{
		return true;
	}

	return false;
}

void displayBoard(char board[])
{
	// statements that display a traditional tic-tac-toe board with the array values
	cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
	cout << "---+---+----\n";
	cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
	cout << "---+---+----\n";
	cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
}

void displayGameStats(int ties, int player1Score, int player2Score)
{
	// cout statement to display player 1 and 2's score as well as the number of ties
	cout << endl << "Player 1: " << player1Score << endl << "Player 2: " << player2Score << endl << "Ties: " << ties << endl;
}

bool keepPlaying(char newRoundInput)
{
	// while loop to prompt for input until 'P', 'p', 'Q', or 'q' is given
	while ((newRoundInput != 'P') && (newRoundInput != 'p') && (newRoundInput != 'Q')  (newRoundInput != 'q'))
	{
		cout << endl << "Please press P to play or again or Q to quit...";
		cin >> newRoundInput;
		cout << endl;
	}

	// input that will start a new game
	if (newRoundInput == 'P' || newRoundInput == 'p')
	{
		return true;
	}

	// input that will stop the program
	if (newRoundInput == 'Q' || newRoundInput == 'q')
	{
		return false;
	}
}