/*
==================================================
        Filename:   text2048.cpp

     Description:   Text-based 2048 game. Please
                    set your terminal to 80 x 25.

         Version:   1.0
         Created:   2014-10-02
        Revision:   none
        Compiler:   gcc

          Author:   David Amirault
==================================================
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <limits>

using namespace std;

int numDigits(int i)
{
	int digits = 0;
	while (i != 0)
	{
		digits++;
		i = i / 10;
	}
	return digits;
}

void displayBoard(int board[][4], int gameState)
{
	cout << "                  _______        _     ___   ___  _  _   ___   " << endl
		 << "                 |__   __|      | |   |__ \\ / _ \\| || | / _ \\  " << endl
		 << "                    | | _____  _| |_     ) | | | | || || (_) | " << endl
		 << "                    | |/ _ \\ \\/ / __|   / /| | | |__   _> _ <  " << endl
		 << "                    | |  __/>  <| |_   / /_| |_| |  | || (_) | " << endl
		 << "                    |_|\\___/_/\\_\\\\__| |____|\\___/   |_| \\___/  " << endl
		 << "                      ________ ________ ________ ________" << endl;
	int spaces;
	for (int i = 0; i < 4; i++)
	{
		cout << "                     |        |        |        |        |" << endl
			 << "                     |";
		for (int j = 0; j < 4; j++)
		{
			spaces = (8 - numDigits(board[i][j])) / 2;
			for (int k = 0; k < spaces; k++)
				cout << " ";
			if (board[i][j] != 0)
				cout << board[i][j];
			if (numDigits(board[i][j]) % 2 == 1)
				cout << " ";
			for (int k = 0; k < spaces; k++)
				cout << " ";
			cout << "|";
		}
		cout << "\n                     |        |        |        |        |" << endl
			 << "                     |________|________|________|________|" << endl;
	}
	if (gameState == 1)
		cout << "\n                     Enter direction (w, a, s, d): ";
}

void addNum(int board[][4], int* gameState)
{
	int num = rand() % 2;
	int freeSquares = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] == 0)
				freeSquares++;
		}
	}
	if (freeSquares != 0)
	{
		int square = rand() % freeSquares;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (board[i][j] == 0)
					freeSquares--;
				if (freeSquares == square)
				{
					if (num == 0)
						board[i][j] = 2;
					else
						board[i][j] = 4;
					return;
				}
			}
		}
	}
}

void checkState(int board[][4], int* gameState)
{
	(*gameState) = 0;
	for (int  i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i != 3 && board[i][j] == board[i + 1][j])
				(*gameState) = 1;
			if (j != 3 && board[i][j] == board[i][j + 1])
				(*gameState) = 1;
			if (board[i][j] == 0)
				(*gameState) = 1;
			if (board[i][j] == 2048)
			{
				(*gameState) = 2;
				break;
			}
		}
	}
}

void calculate(int board[][4], bool merge[][4], char direction, int* gameState)
{
	bool moved = false;
	if (direction == 'a' || direction == 'w')
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					if (direction == 'a')
					{
						if (k != 0 && board[j][k] != 0)
						{
							if (board[j][k] == board[j][k - 1]
									&& merge[j][k] == false
									&& merge[j][k - 1] == false)
							{
								board[j][k - 1] *= 2;
								board[j][k] = 0;
								moved = true;
								merge[j][k - 1] = true;
							}
							if (board[j][k - 1] == 0)
							{
								board[j][k - 1] = board[j][k];
								board[j][k] = 0;
								moved = true;
								merge[j][k - 1] = merge[j][k];
								merge[j][k] = false;
							}
						}
					}
					if (direction == 'w')
					{
						if (j != 0 && board[j][k] != 0)
						{
							if (board[j][k] == board[j - 1][k]
									&& merge[j][k] == false
									&& merge[j - 1][k] == false)
							{
								board[j - 1][k] *= 2;
								board[j][k] = 0;
								moved = true;
								merge[j][k - 1] = true;
							}
							if (board[j - 1][k] == 0)
							{
								board[j - 1][k] = board[j][k];
								board[j][k] = 0;
								moved = true;
								merge[j - 1][k] = merge[j][k];
								merge[j][k] = false;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 3; j >= 0; j--)
			{
				for (int k = 3; k >= 0; k--)
				{
					if (direction == 'd')
					{
						if (k != 3 && board[j][k] != 0)
						{
							if (board[j][k] == board[j][k + 1]
									&& merge[j][k] == false
									&& merge[j][k + 1] == false)
							{
								board[j][k + 1] *= 2;
								board[j][k] = 0;
								moved = true;
								merge[j][k + 1] = true;
							}
							if (board[j][k + 1] == 0)
							{
								board[j][k + 1] = board[j][k];
								board[j][k] = 0;
								moved = true;
								merge[j][k + 1] = merge[j][k];
								merge[j][k] = false;
							}
						}
					}
					if (direction == 's')
					{
						if (j != 3 && board[j][k] != 0)
						{
							if (board[j][k] == board[j + 1][k]
									&& merge[j][k] == false
									&& merge[j + 1][k] == false)
							{
								board[j + 1][k] *= 2;
								board[j][k] = 0;
								moved = true;
								merge[j + 1][k] = true;
							}
							if (board[j + 1][k] == 0)
							{
								board[j + 1][k] = board[j][k];
								board[j][k] = 0;
								moved = true;
								merge[j + 1][k] = merge[j][k];
								merge[j][k] = false;
							}
						}
					}
				}
			}
		}
	}
	if (moved == true)
		addNum(board, gameState);
	checkState(board, gameState);
}

int main()
{
	srand(time(NULL));
	int board[4][4] = {0};
	bool merge[4][4] = {false};
	int gameState = 1;
	addNum(board, &gameState);
	char direction;
	while (gameState == 1)
	{
		displayBoard(board, gameState);
		cin >> direction;
		if (direction == 'w' || direction == 'a' || direction == 's' || direction == 'd')
		{
			calculate(board, merge, direction, &gameState);
			memset(merge, false, sizeof(merge[0][0]) * 4 * 4);
		}
		if (direction == 'q')
			gameState = -1;
		if (gameState == 0)
		{
			displayBoard(board, gameState);
			cout << "\n                     You lose! Better luck next time!";
		}
		if (gameState == 2)
		{
			displayBoard(board, gameState);
			cout << "\n                     You win! Thanks for playing!";
		}
	}

	cout << "\n                     Enter * to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '*');
	return 0;
}

