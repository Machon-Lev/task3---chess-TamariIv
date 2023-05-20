#pragma once
#include <string>

using std::string;
class Board;
class Piece
{
	char _initial;
	bool _color; // 0 for white 1 for black

public:
	Piece(char initial, bool color);
	virtual ~Piece() = default;

	virtual bool isValidMove(int curr_row, int curr_col, int row, int col, Piece* const (&board)[8][8]) const = 0;
	bool getColor();
	char getInitial();
};
