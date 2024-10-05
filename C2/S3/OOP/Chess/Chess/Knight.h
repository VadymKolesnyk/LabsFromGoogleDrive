#pragma once
#include "Figure.h"
class Knight :
	public Figure
{
public:
	Knight(const Figure* other);
	Knight(char vert, int hor, Color color);
	~Knight() override;
	Cell CanMove(Cell finish, Desk& desk) override;
	Type GetType() const override;
	Knight* Clone() const override;
	std::list<Cell> GetPossibleMoves() const override;
};

