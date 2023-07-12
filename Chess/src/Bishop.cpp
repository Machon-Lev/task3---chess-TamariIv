#include "..\include\Bishop.h"

Bishop::Bishop(bool color) :
	Piece(color ? 'b' : 'B', color)
{}

// Check if the move is possible for a queen
bool Bishop::isValidMove(int curr_row, int curr_col, int row, int col, Piece* const(&board)[8][8]) const
{
	// Check if there was any movement
	if (curr_row == row && curr_col == col)
		return false;

	// Check if the diagonal move is valid
	if (curr_row != row && curr_col != col && abs(curr_row - row) != abs(curr_col - col))
		return false;

	// Check if no one is blocking the path (queens cant jump over other pieces) 
	int horizontal_step = 0;
	int vertical_step = 0;
	if (col < curr_col)
		horizontal_step = -1;
	else if (col > curr_col)
		horizontal_step = 1;
	if (row < curr_row)
		vertical_step = -1;
	else if (row > curr_row)
		vertical_step = 1;
	for (int i = curr_row, j = curr_col; i != row && j != col; i += horizontal_step, j += vertical_step)
	{
		if (board[i][j] != nullptr)
			return false;
	}
	return true;
}
