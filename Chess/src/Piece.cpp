#include "Piece.h"

Piece::Piece(char initial, bool color) :
	_initial(initial), _color(color)
{}

bool Piece::getColor()
{
	return _color;
}

char Piece::getInitial()
{
	return _initial;
}
