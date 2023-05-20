#include "Board.h"


Board::Board(string pieces)
{
	_turn = 0;
	for (size_t i = 0; i < _BSIZE; i++)
		for (size_t j = 0; j < _BSIZE; j++)
		{
			if (pieces[i * _BSIZE + j] != '#') {
				_board[i][j] = createPiece(pieces[i * _BSIZE + j]);
				Piece* ptr = _board[i][j];
			}
			else
				_board[i][j] = nullptr;
		}
}

Board::~Board()
{
	for (size_t i = 0; i < _BSIZE; i++)
		for (size_t j = 0; j < _BSIZE; j++)
			if (_board[i][j])
				delete _board[i][j];
}

// Move the piece according to the movement string thaat was received
int Board::movePiece(string movement)
{
	if (movement.size() != 4)
		return -1;
	int curr_row = movement[0] - 'a'; 
	int curr_col = movement[1] - '0' - 1;
	int dest_row = movement[2] - 'a';
	int dest_col = movement[3] - '0' - 1;

	int validationCode = validateMovePre(curr_row, curr_col, dest_row, dest_col);
	// if the move is valid so far, keep checking
	if (validationCode == 1) {
		Piece* tmp_p = _board[dest_row][dest_col]; // save the content of the destination place in case we need to restore it
		_board[dest_row][dest_col] = _board[curr_row][curr_col];
		_board[curr_row][curr_col] = nullptr;
		validationCode = validateMovePost(curr_row, curr_col, dest_row, dest_col);
		if (validationCode != LEGAL_CHECK && validationCode != LEGAL_MOVE) {
			// if the move was not legal, restore the board before the move
			_board[curr_row][curr_col] = _board[dest_row][dest_col];
			_board[dest_row][dest_col] = tmp_p;
		}
		else {
			if (tmp_p)
				delete tmp_p;
			tmp_p = nullptr;
			_turn = !_turn;
		}
	}
	return validationCode;
}

// Validate the move is legal before executing it
int Board::validateMovePre(int curr_row, int curr_col, int dest_row, int dest_col)
{
	if (_board[curr_row][curr_col] == nullptr)
		return EMPTY_LOCATION;
	if (_turn != _board[curr_row][curr_col]->getColor())
		return ENEMYÉÉÉ_MOVE;
	if (_board[dest_row][dest_col] != nullptr && _board[dest_row][dest_col]->getColor() == _turn)
		return DEST_IS_FULL;
	if (!_board[curr_row][curr_col]->isValidMove(curr_row, curr_col, dest_row, dest_col, _board))
		return ILLEGAL_MOVE;
	return 1;
}

// Validate the move was legal after it was done
int Board::validateMovePost(int curr_row, int curr_col, int dest_row, int dest_col)
{
	if (isCheck(_turn))
		return SELF_CHECK;
	if (isCheck(!_turn))
		return LEGAL_CHECK;
	return LEGAL_MOVE;
}

// Create a new piece according to the char that was received
Piece* Board::createPiece(char ch)
{
	bool color = std::islower(ch);
	Piece* ret = nullptr;
	switch (ch)
	{
	case 'r':
	case 'R':
		ret = new Rook(color);
		break;
	case 'K':
	case 'k':
		ret = new King(color);
		break;
	default:
		break;
	}
	return ret;
}

// Check if the color that was received is under check
bool Board::isCheck(bool color) const
{
	int k_row = -1;
	int k_col = -1;
	// find the king of the color
	for (size_t i = 0; i < _BSIZE; i++)		
		for (size_t j = 0; j < _BSIZE; j++)
			if (_board[i][j] && ((_board[i][j]->getInitial() == 'K' && !color) || (_board[i][j]->getInitial() == 'k' && color))) {
				k_row = i;
				k_col = j;
			}
	if (k_col < 0 || k_row < 0)
		return false;
	for (size_t i = 0; i < _BSIZE; i++)
	{
		for (size_t j = 0; j < _BSIZE; j++)
		{
			// for each piece of the other color, check if it threatens the king
			if (_board[i][j] && std::islower(_board[i][j]->getInitial()) != color)
				if (_board[i][j]->isValidMove(i, j, k_row, k_col, _board))
					return true;
		}
	}
	return false;
}
