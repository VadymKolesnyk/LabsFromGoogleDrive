#include "MatrixModel.h"

MatrixModel::MatrixModel()
{
	for (int x = 0; x < size; ++x)
		for (int y = 0; y < size; ++y)
			board[x][y] = CellValue::Blank;

	for (int i = 0; i < size; ++i)
	{
		lines.push_back(new BoardLine(*this, size, 0, i, 1, 0));
		lines.push_back(new BoardLine(*this, size, i, 0, 0, 1));
	}
	lines.push_back(new BoardLine(*this, size, 0, 0, 1, 1));
	lines.push_back(new BoardLine(*this, size, size - 1, 0, -1, 1));
}

MatrixModel::~MatrixModel()
{
	for (BoardLine* line : lines)
	{
		delete line;
	}
}

GameStatus MatrixModel::putMark(CellValue mark, int x, int y)
{
	if (mark != CellValue::Blank) 
		board[x][y] = mark;
	return getStatus();
}

bool MatrixModel::checkBlanks() const
{
	for (int x = 0; x < size; ++x)
		for (int y = 0; y < size; ++y)
			if (board[x][y] == CellValue::Blank) return true;
	return false;
}

GameStatus MatrixModel::getStatus() const
{
	GameStatus lineStatus;
	for (BoardLine* line : lines)
	{
		lineStatus = line->checkWin();
		if (lineStatus == GameStatus::XWon || lineStatus == GameStatus::OWon)
			return lineStatus;
	}
	if (!checkBlanks()) return GameStatus::Draw;
	return GameStatus::InProgress;
}

CellValue MatrixModel::getCellValue(int x, int y) const
{
	return board[x][y];
}
