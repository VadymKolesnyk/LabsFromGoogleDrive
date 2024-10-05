#include "BoardLine.h"

BoardLine::BoardLine(const GameModel& model, int length, int xStart, int yStart, int xStep, int yStep)
	: model(model), length(length), xStart(xStart), yStart(yStart), xStep(xStep), yStep(yStep)
{}

bool BoardLine::checkWin(CellValue testMark) const
{
	int x = xStart, y = yStart;
	for (int i = 0; i < length; ++i)
	{
		if (model.getCellValue(x, y) != testMark) return false;
		x += xStep;
		y += yStep;
	}
	return true;
}

GameStatus BoardLine::checkWin() const
{
	CellValue testMarks[] = { CellValue::X, CellValue::O };
	GameStatus statuses[] = { GameStatus::XWon, GameStatus::OWon };
	for (CellValue mark : testMarks)
		if (checkWin(mark)) return GameModel::winStatusByMark(mark);
	return GameStatus::InProgress;
}

