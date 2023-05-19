#include "..\include\King.h"

//bool King::isValidMove(int curr_row, int curr_col, int row, int col, Piece* const(&board)[21][21]) const
//{
//	if (row > curr_row + 1 || row < curr_row -1 || col < curr_col - 1 || col > curr_col + 1)
//		return false;
//	return true;
//
//}

King::King(bool _color) : 
	Piece(_color ? 'K' : 'k', _color)
{}

bool King::isValidMove(int curr_row, int curr_col, int row, int col, Piece* const(&board)[8][8]) const
{
	if (row > curr_row + 1 || row < curr_row -1 || col < curr_col - 1 || col > curr_col + 1)
		return false;
	return true;
	
}
