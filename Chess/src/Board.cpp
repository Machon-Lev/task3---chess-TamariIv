#include "Board.h"


Board::Board(string pieces)
{
	turn = 0;
	for (size_t i = 0; i < _BSIZE; i++)
		for (size_t j = 0; j < _BSIZE; j++)
		{
			if (pieces[i * _BSIZE + j] != '#') {
				board[i][j] = createPiece(pieces[i * _BSIZE + j]);
				Piece* ptr = board[i][j];
				if (board[i][j]->getColor())
					blacks.push_back(ptr);
				else
					whites.push_back(ptr);
			}
			else
				board[i][j] = nullptr;
		}
}

int Board::movePiece(string movement)
{
	if (movement.size() != 4)
		return -1;
	int curr_row = movement[0] - 'a'; 
	int curr_col = movement[1] - '0' - 1;
	int dest_row = movement[2] - 'a';
	int dest_col = movement[3] - '0' - 1;

	int validationCode = validateMovePre(curr_row, curr_col, dest_row, dest_col);
	if (validationCode == 1) {
		Piece* tmp_p = board[dest_row][dest_col];
		board[dest_row][dest_col] = board[curr_row][curr_col];
		board[curr_row][curr_col] = nullptr;
		validationCode = validateMovePost(curr_row, curr_col, dest_row, dest_col);
		if (validationCode != LEGAL_CHECK && validationCode != LEGAL_MOVE) {
			board[curr_row][curr_col] = board[dest_row][dest_col];
			board[dest_row][dest_col] = tmp_p;
		}
		else {
			delete tmp_p;
			tmp_p = nullptr;
			turn = !turn;
		}
	}
	return validationCode;
}

int Board::validateMovePre(int curr_row, int curr_col, int dest_row, int dest_col)
{
	if (board[curr_row][curr_col] == nullptr)
		return EMPTY_LOCATION;
	if (turn != board[curr_row][curr_col]->getColor())
		return ENEMYÉÉÉ_MOVE;
	if (board[dest_row][dest_col] != nullptr && board[dest_row][dest_col]->getColor() == turn)
		return DEST_IS_FULL;
	if (!board[curr_row][curr_col]->isValidMove(curr_row, curr_col, dest_row, dest_col, board))
		return ILLEGAL_MOVE;
	return 1;
}

int Board::validateMovePost(int curr_row, int curr_col, int dest_row, int dest_col)
{
	if (isCheck(turn))
		return SELF_CHECK;
	if (isCheck(!turn))
		return LEGAL_CHECK;
	return LEGAL_MOVE;
}



//int Board::validateMove(int curr_row, int curr_col, int dest_row, int dest_col)
//{
//	if (board[curr_row][curr_col] == nullptr)
//		return EMPTY_LOCATION;
//	if (turn != board[curr_row][curr_col]->getColor())
//		return ENEMYÉÉÉ_MOVE;
//	if (board[dest_row][dest_col] != nullptr && board[dest_row][dest_col]->getColor() == turn)
//		return DEST_IS_FULL;
//	if (!board[curr_row][curr_col]->isValidMove(curr_row, curr_col, dest_row, dest_col, board))
//		return ILLEGAL_MOVE;
//	if (isCheck(turn))
//		return SELF_CHECK;
//	if (isCheck(!turn))
//		return LEGAL_CHECK;
//	return LEGAL_MOVE;
//}

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
	// Find the color king
	int k_row = -1;
	int k_col = -1;
	for (size_t i = 0; i < _BSIZE; i++)
		for (size_t j = 0; j < _BSIZE; j++)
			if (board[i][j] && (board[i][j]->getInitial() == 'K' || board[i][j]->getInitial() == 'k')) {
				k_row = i;
				k_col = j;
			}
	if (k_col < 0 || k_row < 0)
		return false;
	for (size_t i = 0; i < _BSIZE; i++)
	{
		for (size_t j = 0; j < _BSIZE; j++)
		{
			if (board[i][j] && std::islower(board[i][j]->getInitial()) != color)
				if (board[i][j]->isValidMove(i, j, k_row, k_col, board))
					return true;
		}
	}
	return false;
}
