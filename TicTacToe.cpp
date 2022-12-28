/*
Write the game of Tic Tac Toe. 
It's a game with a 3 by 3 grid played by 2 players. One player places O markers and the other player places X markers. 
Each player takes turns placing his/her marker in order to get 3 of their markers to line up on the board.
A player wins when 3 or their markers line up either horizontally, vertically or diagonally.
If no player has their markers line up in that fashion, and the board is full, then the game is called a "Cat Game". 
Your program should output the winner of the game or "Cat Game" if there was no winner. 
The user should be prompted if they would like to play again when the game is over. 
If they choose to play again, the player who started second last game should go first.
*/

/*
	do {
		PlayGame()
	} while(WantToPlayAgain())


	PlayGame()
	---------
	board = MakeBoard(3, 3);
	DrawBoard(board);
	user = 1;
	numberOfYourUserTurns = 3x3
	do {
		row = GetRow()
		col = GetCol()
		user = GetUser(user) -> user % 2 == 0 ? 2 : 1;
		marker = GetMaker(user) -> user % 2 == 0 ? o : x; -> check the current value of rowcol and check is valid or not
		UpdateBoard(row, col, board, user, marker, numberOfYourUsersTurns)
		DrawBoard(board)
	} while (IsGameOver(board, numberOfUsersTurns));

	DisplayResult(board, user)

	MakeBoard(3, 3)
	--------------
	board = make 1D array of 3x3
	for (length of board) {
		board[i] = '-';
	}

	return board;

	UpdateBoard(row, col, board, user, numberOfUsersTurns)
	------------------------
	marker is valid, user is valid
	output your user turn
	if (GetValue(board, row, maxRow, col) != '-') {
		board[GetValue(board, row, maxRow, col)] = marker;
	}
	
	--numberOfUsersTurns


	IsGameOver(board, numberOfUsersTurns)
	----------------
	isVictory = false
	isFullBoard = numberOfUsersTurns != 0
	for (length of board && !isFullBoard) {
		currentSquare
		if(CheckVerticallySquare(currentSquare) ||
 		CheckHorizontallySquare(currentSquare) ||
		CheckDiogonallySquare(currentSquare) ) {
			isVictory = true;
		}
	}
	
	return isVictory;

*/

#include <iostream>
#include "Utils.h"

const int MAX_ROW = 3;
const int PRIMARY_USER = 1;
const int SECONDARY_USER = 2;
const char X_MARKER = 'x';
const char O_MARKER = '0';
const char DASH_CHARACTER = '-';
const char* INPUT_INVALID_ERROR = "Input error! Please re-enter";

void PlayGame();
bool WantToPlayAgain();
char* MakeBoard(const int, const int);
void DrawBoard(char*, int);
int GetRow();
int GetCol();
int GetUsersTurn(const int);
char GetMarker(const int);
void UpdateBoard(char*, int, int, int, int&, char, char, int&);
bool IsGameOver(const char*, int, int, int, int, bool&);
void DisplayResult(int, int, bool);
bool CheckVerticallyBoard(const char* board, int row, int maxRow, int col);
bool CheckHorizontallyBoard(const char* board, int row, int maxRow, int col);
bool CheckAxesBoard(const char* board, int row, int maxRow, int col);

/// <summary>
/// Test
/// </summary>
void TestCheckHorizontallyBoard();
void TestCheckVerticallyBoard();
void TestCheckAxesBoard();

int main()
{
	do {
		system("cls");
		PlayGame();
	} while (WantToPlayAgain());
	
	/*TestCheckHorizontallyBoard();
	TestCheckVerticallyBoard();*/
	//TestCheckAxesBoard();
	//char board[] = { X_MARKER, '-', '-',
	//				 X_MARKER, '-', '-',
	//				 X_MARKER, '-', '-' };
	//DrawBoard(board, MAX_ROW, true);
	
	return 0;
}

void TestCheckVerticallyBoard() {
	char board[] = { X_MARKER, '-', '-', 
					 X_MARKER, '-', '-', 
					 X_MARKER, '-', '-' };
	if (CheckVerticallyBoard(board, 2, MAX_ROW, 0)) {
		std::cout << "Is winner";
	}
}

void TestCheckHorizontallyBoard() {
	char board[] = { X_MARKER, X_MARKER, X_MARKER, 
					 O_MARKER, '-', '-', 
					 O_MARKER, '-', '-'};
	if (CheckHorizontallyBoard(board, 0, MAX_ROW, 0)) {
		std::cout << "Is winner";
	}
}

void TestCheckAxesBoard() {
	char board[] = { X_MARKER, O_MARKER, X_MARKER, 
					 O_MARKER, O_MARKER, '-', 
					 X_MARKER, '-', O_MARKER};
	if (CheckAxesBoard(board, 1, MAX_ROW, 1)) {
		std::cout << "Is Winner";
	}
}

void PlayGame() {
	char* board = MakeBoard(MAX_ROW, MAX_ROW);
	int user = PRIMARY_USER, numberOfUsersTurns = MAX_ROW * MAX_ROW;
	int row, col;
	char marker, lastMarker;
	bool isVictory;
	 
	std::cout << "Player " << user << " move to: " << std::endl;
	DrawBoard(board, MAX_ROW);

	do {
		isVictory = false;
		row = GetRow();
		col = GetCol();
		user = GetUsersTurn(user);
		marker = GetMarker(user);
		lastMarker = marker;
		system("cls");
		UpdateBoard(board, row, MAX_ROW, col, numberOfUsersTurns, marker, lastMarker, user);
		std::cout << "Player " << user << " move to: " << std::endl;
		DrawBoard(board, MAX_ROW);
	} while (!IsGameOver(board, row, MAX_ROW, col, numberOfUsersTurns, isVictory));

	DisplayResult(numberOfUsersTurns, user, isVictory);

	delete[] board;
	board = nullptr;
}

bool WantToPlayAgain() {
	const char validInput[] = {'y', 'n'};
	
	char response = GetCharacter("Do you want to play again? (y/n)", 
								  INPUT_INVALID_ERROR, 
								  validInput, 
								  2);
	return response == 'y';
}

char* MakeBoard(const int row, const int col) {
	const int length = row * col;
	char* board = new char[length + 1];
	
	for (int i = 0; i < length; ++i) {
		board[i] = DASH_CHARACTER;
	}

	board[length] = '\0';

	return board;
}

void DrawLine(char line, int numberOfLines) {
	for (int i = 0; i < numberOfLines; ++i) {
		std::cout << line << " ";
	}
	std::cout << std::endl;
}

void DrawBoard(char* board, int maxRow) {
	for (int i = 0; i < maxRow; ++i) {
		DrawLine(DASH_CHARACTER, 7);
		for (int j = 0; j < maxRow; ++j) {
			std::cout << "| " << board[i * maxRow + j] << " ";
		}
		std::cout << "|" << std::endl;
	}
	DrawLine(DASH_CHARACTER, 7);
}

int GetRow() {
	return GetInt("Please enter your row: ", INPUT_INVALID_ERROR);
}

int GetCol() {
	return GetInt("Please enter your column: ", INPUT_INVALID_ERROR);
}

int GetUsersTurn(const int user) {
	return user % 2 == 0 ? PRIMARY_USER : SECONDARY_USER;
}

char GetMarker(const int user) {
	return user % 2 == 0 ? O_MARKER : X_MARKER;
}

void UpdateBoard(char* board, int row, int maxRow, int col, int& numberOfUsersTurns, char marker, char lastMarker, int& user) {
	const int squareIndex = row * maxRow + col;
	const char currentSquare = board[squareIndex];
	
	if (currentSquare != DASH_CHARACTER) {
		if (marker == lastMarker) {
			user = GetUsersTurn(user);
			std::cout << "You can not mark because the square of your competitor has been marked!" << std::endl;
			std::cout << "Please re-enter!" << std::endl << std::endl;
		}
		else {
			user = GetUsersTurn(user);
			std::cout << "You can not mark because the square of mine has been marked!" << std::endl;
			std::cout << "Please re-enter!" << std::endl << std::endl;
		}
	}
	else {
		board[squareIndex] = marker;
		--numberOfUsersTurns;
	}
}

bool CheckVerticallyBoard(const char* board, int row, int maxRow, int col) {
	const char newMarker = board[row * maxRow + col];

	if (row < 0 || col > maxRow) {
		std::cout << "You must be mark the greater than " << 0 << " and less than " << maxRow << std::endl;
		return false;
	}

	if (newMarker != DASH_CHARACTER) {
		for (int i = 0; i < maxRow; ++i) {
			if (board[0 * maxRow + i] == newMarker) {
				if (board[1 * maxRow + i] == newMarker) {
					if (board[2 * maxRow + i] == newMarker) {
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

bool CheckHorizontallyBoard(const char* board, int row, int maxRow, int col) {
	const char newMarker = board[row * maxRow + col];

	if (row < 0 || col > maxRow) {
		std::cout << "You must be mark the greater than " << 0 << " and less than " << maxRow << std::endl;
		return false;
	}

	if (newMarker != DASH_CHARACTER) {
		for (int i = 0; i < maxRow; ++i) {
			if (board[i * maxRow + 0] == newMarker) {
				if (board[i * maxRow + 1] == newMarker) {
					if (board[i * maxRow + 2] == newMarker) {
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool CheckAxesBoard(const char* board, int row, int maxRow, int col) {
	const char newMarker = board[row * maxRow + col];

	if (row < 0 || col > maxRow) {
		std::cout << "You must be mark the greater than " << 0 << " and less than " << maxRow << std::endl;
		return false;
	}

	if (newMarker != DASH_CHARACTER) {
		if (board[0 * maxRow + 0] == newMarker) {
			if (board[1 * maxRow + 1] == newMarker) {
				if (board[2 * maxRow + 2] == newMarker) {
					return true;
				}
			}
		}

		if (board[0 * maxRow + 2] == newMarker) {
			if (board[1 * maxRow + 1] == newMarker) {
				if (board[2 * maxRow + 0] == newMarker) {
					return true;
				}
			}
		}
	}

	return false;
}

bool IsGameOver(const char* board, int row, int maxRow, int col, int numberOfUsersTurns, bool& isVictory) {
	// check winner

	if (CheckVerticallyBoard(board, row, maxRow, col)) {
		isVictory = true;
		return true;
	}

	if (CheckHorizontallyBoard(board, row, maxRow, col)) {
		isVictory = true;
		return true;
	}

	if (CheckAxesBoard(board, row, maxRow, col)) {
		isVictory = true;
		return true;
	}

	for (int i = 0; i < maxRow; ++i) {
		for (int j = 0; j < maxRow; ++j) {
			if (board[i * maxRow + j] == DASH_CHARACTER) {
				return false;
			}
		}
	}

	// can be deleted
	return numberOfUsersTurns == 0;
}

void DisplayResult(int numberOfUsersTurns, int user, bool isVictory) {
	if (isVictory) {
		std::cout << "The player  " << user << " is winner " << std::endl;
	} else if (numberOfUsersTurns == 0) {
		std::cout << "Game is ties " << std::endl;
	}
}