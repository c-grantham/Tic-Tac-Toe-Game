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
bool isLegalMove(char board[], int location);
void placeMarkOnBoard(char board[], char playerMark, int location);
void clearBoard(char board[]);
bool hasThreeInRow(char board[], char playerMark);
void displayBoard(char board[]);
void displayGameStats(int ties, int player1Score, int player2Score);
bool keepPlaying(char newRoundInput);

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
	int turnTracker = 0;
	int gameTracker = 0;
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
			turnTracker++;

			// if the number of games played is even, player 1 starts
			if ((gameTracker % 2) == 0)
			{
				// set the name and mark to player 1's
				playerName = player1Name;
				playerMark = 'X';
			}

			// if the number of games is odd, player 2 starts
			if ((gameTracker % 2) == 1)
			{
				// set the name and mark to player 2's
				playerName = player2Name;
				playerMark = 'O';
			}

			// displays up to date board
			displayBoard(board);
			cout << endl;

			// get player input for a board location that is a legal move
			do
			{
				inputResult = (getPlayerInput(playerName));
			} while (isLegalMove(board, inputResult) == false);

			// places player's mark on the selected location on the board 
			placeMarkOnBoard(board, playerMark, inputResult);

			/* check if player  has gotten three in a row,
			   if true then add 1 point to their score, display the game stats and end the current game */
			if (hasThreeInRow(board, playerMark))
			{
				if (playerName == player1Name)
				{
					player1Score++;
				}
				else { player2Score++; }
				displayGameStats(ties, player1Score, player2Score);
				break;
			}

			/* if statement to check if the limit of possible turns has been reached,
			   add to tie count, display game stats and end game if true */
			if (turnTracker == 5)
			{
				ties++;
				displayGameStats(ties, player1Score, player2Score);
				break;
			}

			// if the number of games is even, player 2 goes second
			if ((gameTracker % 2) == 0)
			{
				// set the name and mark to player 2's
				playerName = player2Name;
				playerMark = 'O';
			}

			// if the number of games is odd, player 1 goes second
			if ((gameTracker % 2) == 1)
			{
				// set the name and mark to player 1's
				playerName = player1Name;
				playerMark = 'X';
			}

			// displays up to date board
			displayBoard(board);
			cout << endl;

			// get player input for a board location that is a legal move
			do
			{
				inputResult = (getPlayerInput(playerName));
			} while (isLegalMove(board, inputResult) == false);

			// places player's mark on the selected location on the board 
			placeMarkOnBoard(board, playerMark, inputResult);

			/* check if player  has gotten three in a row,
			   if true then add 1 point to their score, display the game stats and end the current game */
			if (hasThreeInRow(board, playerMark))
			{
				if (playerName == player1Name)
				{
					player1Score++;
				}
				else { player2Score++; }
				displayGameStats(ties, player1Score, player2Score);
				break;
			}
		} while (hasThreeInRow(board, playerMark) == false);

		// reset the tic-tac-toe board
		clearBoard(board);
		// resets the number of turn for potential new game
		turnTracker = 0;
		// adds one to the number of games played tracker
		gameTracker++;

	} while (keepPlaying(newRoundInput));

	return 0;
}

// function definitions

/*
getPlayerInput - uses the playerName to ask for location input
@param playerName - string of player 1 or 2's chosen name for the game
@return playerInput - returns an integer 1-9 of what the player chose
*/
int getPlayerInput(string playerName)
{
	int playerInput = 0;
	// prompt for input until an integer between 1 and 9 is provided
	while (playerInput < 1 || playerInput > 9)
	{
		cout << playerName << ", please choose an empty space on the board 1-9: ";
		cin >> playerInput;
	}
	cout << endl;
	return playerInput - 1;
}

/*
isLegalMove - boolean function that checks whether or not the player's chosen location
			  on the board has already been used
@param board[] - character array of the board's potential locations 0-8
@location - integer 1-9 of the player's selected location input on the board
@returns true if the location has not already been used, false if the location has been used
*/
bool isLegalMove(char board[], int location)
{
	// check if the chosen location hs already been taken
	if (board[location] == 'X' || board[location] == 'O')
	{
		return false;
	}
	return true;
}

/*
placeMarkOnBoard - function which places 'X' or 'O' on the players specified location on the board
@param board[] - character array of the potential board locations 1-9
@param playerMark - character 'X' or 'O' for the respective player
@param location - integer location of the player's selected location on the board
*/
void placeMarkOnBoard(char board[], char playerMark, int location)
{
	// place the player's mark on the selected board location
	board[location] = playerMark;
}

/*
clearBoard - function that replaces any player marks on the board with the original numbers
@param board[] - character array of the potential board locations 1-9
*/
void clearBoard(char board[])
{
	// for loop to reset the board to the original format using ASCII values
	for (int i = 0; i < 9; i++)
	{
		board[i] = i + 49;
	}
}

/*
hasThreeInRow - bool function that checks whether or not a player has achieved a three in a row
@param board[] - character array of the potential board locations 1-9
@param playerMark - character 'X' or 'O' depending on which player's turn it is
@returns true if there is a three in a row present and false if there is not
*/
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

/*
displayBoard - function that outputs the tic tac toe board with the potential player mark locations and current marks
@param board[] - character array of the potential board locations 1-9
*/
void displayBoard(char board[])
{
	// statements that display a traditional tic-tac-toe board with the array values
	cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
	cout << "---+---+----\n";
	cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
	cout << "---+---+----\n";
	cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
}

/*
displayGameStats - function that outputs the number of games player 1 and 2 have won as well as the number of ties after each completed game
@param ties - integer count of how many ties have happened
@param player1Score - integer count of how many times player 1 has won
@param player2Score - integer count of how many times player 2 has won
*/
void displayGameStats(int ties, int player1Score, int player2Score)
{
	// cout statement to display player 1 and 2's score as well as the number of ties
	cout << endl << "Player 1: " << player1Score << endl << "Player 2: " << player2Score << endl << "Ties: " << ties << endl;
}

/*
keepPlaying - bool function that takes user input on whether or not to play another game
@param newRoundInput - character for user input
@returns true if the player inputs 'P' or 'p' and false if the player inputs 'Q' or 'q'
*/
bool keepPlaying(char newRoundInput)
{
	// while loop to prompt for input until 'P', 'p', 'Q', or 'q' is given
	while ((newRoundInput != 'P') && (newRoundInput != 'p') && (newRoundInput != 'Q') && (newRoundInput != 'q'))
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
