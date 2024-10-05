#pragma once
#include "Cell.h"
#include "Desk.h"
#include <vector>
#include <list>
class Desk;
enum class Color { White, Black };
Color operator!(const Color& color);
enum class Type { Pawn, Knight, Bishop, Rook, Queen, King };
class Figure
{
protected:
	Cell cell;
	Cell previous;
	Color color;
	int timeOnCell;
public:
	Figure(const Figure* other);
	Figure(char vert, int hor, Color color);
	virtual ~Figure();
	virtual bool CanAttack(Cell& finish, Desk& desk);
	virtual Cell CanMove(Cell finish, Desk& desk) = 0;
	virtual std::list<Cell> GetPossibleMoves() const = 0;
	virtual Type GetType() const = 0;
	virtual Figure* Clone() const = 0;
	void Move(const Cell& cell);
	void AddTime();
	int GetTime();
	Cell GetPosition() const;
	int GetVert() const;
	char GetHor() const;

	Cell GetPreviousPosition() const;
	int GetPreviousVert() const;
	char GetPreviousHor() const;

	void Copy(const Figure* other);
	Color GetColor() const;

	void ChangePosition(const Cell& cell);
	void ChangePosition(char vert, int hor);

};

