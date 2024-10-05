#pragma once
#include "Figure.h"
class Queen :
	public Figure
{
public:
	Queen(const Figure* other);
	Queen(char vert, int hor, Color color);
	~Queen() override;
	Cell CanMove(Cell finish, Desk& desk) override;
	Type GetType() const override;
	Queen* Clone() const override;
	std::list<Cell> GetPossibleMoves() const override;
};

