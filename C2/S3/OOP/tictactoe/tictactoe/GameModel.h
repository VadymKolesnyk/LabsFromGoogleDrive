#pragma once

enum class CellValue {X, O, Blank};
enum class GameStatus {InProgress, XWon, OWon, Draw};

class GameModel
{
public:
	static const int size = 3;
	virtual GameStatus putMark(CellValue mark, int x, int y) = 0;
	virtual CellValue getCellValue(int x, int y) const = 0;
	virtual GameStatus getStatus() const = 0;
	static GameStatus winStatusByMark(CellValue mark);
};
