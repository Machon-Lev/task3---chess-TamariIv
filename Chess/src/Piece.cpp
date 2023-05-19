#include "Piece.h"

Piece::Piece(char _initial, bool _color) :
	initial(_initial), color(_color)
{}

bool Piece::getColor()
{
	return color;
}

char Piece::getInitial()
{
	return initial;
}
