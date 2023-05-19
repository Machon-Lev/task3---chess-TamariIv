#pragma once
#include "Piece.h"

//class Piece;
class Board;
class Rook: public Piece
{
public:
	Rook(bool _color);

private:
	virtual bool isValidMove(int curr_row, int curr_col, int row, int col, Piece* const (&board)[8][8]) const override;
	//virtual bool isValidMove(int curr_row, int curr_col, int row, int col) const override;

};

