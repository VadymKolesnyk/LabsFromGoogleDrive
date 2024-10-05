#pragma once
#include "Figure.h"
class Rook :
	public Figure
{
public:
	Rook(const Figure* other);
	Rook(char vert, int hor, Color color);
	~Rook() override;
	Cell CanMove(Cell finish, Desk& desk) override;
	Type GetType() const override;
	Rook* Clone() const override;
	std::list<Cell> GetPossibleMoves() const override;
};

