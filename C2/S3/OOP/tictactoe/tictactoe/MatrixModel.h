#pragma once
#include "GameModel.h"
#include "BoardLine.h"
#include <vector>

class MatrixModel: public GameModel
{
public:
	MatrixModel();
	~MatrixModel();

	static const int size = 3;
	GameStatus putMark(CellValue mark, int x, int y);
	CellValue getCellValue(int x, int y) const;
	GameStatus getStatus() const;

private:
	CellValue board[size][size];
	std::vector<BoardLine*> lines;
	bool checkBlanks() const;
};
