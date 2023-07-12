#include "..\include\King.h"

King::King(bool color) : 
	Piece(color ? 'k' : 'K', color)
{}

// Check if the move is possible for a rook
bool King::isValidMove(int curr_row, int curr_col, int row, int col, Piece* const(&board)[8][8]) const
{
	if (row > curr_row + 1 || row < curr_row -1 || col < curr_col - 1 || col > curr_col + 1)
		return false;
	return true;
	
}
