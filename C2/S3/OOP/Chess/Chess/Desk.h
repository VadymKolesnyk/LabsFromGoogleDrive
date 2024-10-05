#pragma once
#include "Figure.h"
#include <list>
#include <vector>
class Figure;
enum class Color;
enum class Type;
class Desk
{
private:
	int amount;
	int time;

	std::list<Figure*> figures;
public:
	Desk(const Desk& other);
	Desk();
	~Desk();
	Desk& operator=(const Desk& other);
	std::list<Figure*> GetFigures() const;
	void ChangeFigure(const Cell& cell, Type type);
	void AddTime();
	int GetTime();
	bool EatFigure(const Cell& cell);
	int GetAmount() const;
	std::vector<Cell> GetLine(Cell start, Cell finish) const;
	bool IsCheckOnCell(Cell& cell, Color colorKing);
	bool IsCellOnDesk(Cell& cell);
};