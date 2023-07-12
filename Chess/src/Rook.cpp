#include "..\include\Rook.h"


Rook::Rook(bool color) : 
	Piece(color ? 'r' : 'R', color)
{}

// Check if the move is possible for a rook
bool Rook::isValidMove(int curr_row, int curr_col, int row, int col, Piece* const(&board)[8][8]) const
{
	// Check if the step is only forward, backward, left or right
	if ((curr_row != row && curr_col != col)|| (curr_row == row && curr_col == col))
		return false;
	
	// Check if no one is blocking the path (rooks cant jump over other pieces) 
	if (curr_col < col) {
		for (int i = curr_col + 1; i < col; i++)
		{
			if (board[curr_row][i] != nullptr)
				return false;
		}
	}
	else if (curr_col > col) {
		for (int i = curr_col - 1; i > col; i--)
		{
			if (board[curr_row][i] != nullptr)
				return false;
		}
	}
	else if (curr_row < row) {
		for (int i = curr_row + 1; i < row; i++)
		{
			if (board[i][curr_col] != nullptr)
				return false;
		}
	}
	else if (curr_row > row) {
		for (int i = curr_row - 1; i > row; i--)
		{
			if (board[i][curr_col] != nullptr)
				return false;
		}
	}
	return true;
}
