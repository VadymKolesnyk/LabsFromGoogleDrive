#pragma once
#include "GameModel.h"

class BoardLine
{
public:
	BoardLine(const GameModel& model, int length, int xStart, int yStart, int xStep, int yStep);
	GameStatus checkWin() const;
private:
	const GameModel& model;
	const int length, xStart, yStart, xStep, yStep;
	bool checkWin(CellValue testMark) const;
};
