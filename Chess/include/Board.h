#pragma once
#include <vector>
#include "Piece.h"
#include "Rook.h"
#include "King.h"
#include <string>
#include <cctype>


enum Code
{
	EMPTY_LOCATION = 11,
	ENEMY………_MOVE = 12,
	DEST_IS_FULL = 13,
	ILLEGAL_MOVE = 21,
	SELF_CHECK = 31,
	LEGAL_MOVE = 42,
	LEGAL_CHECK = 41
};

using std::string;

const int _BSIZE = 8;
class Piece;

class Board {
public:
	Piece* _board[_BSIZE][_BSIZE];
	bool _turn; // 0 for white 1 for black

	Board(string pieces);
	~Board();

	int movePiece(string movement);

private:
	int validateMovePre(int curr_row, int curr_col, int dest_row, int dest_col);
	int validateMovePost(int curr_row, int curr_col, int dest_row, int dest_col);

	Piece* createPiece(char ch);
	bool isCheck(bool color) const;

};