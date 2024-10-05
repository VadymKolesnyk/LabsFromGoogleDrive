#pragma once
#include "Figure.h"
class Bishop :
	public Figure
{
public:
	Bishop(const Figure* other);
	Bishop(char vert, int hor, Color color);
	~Bishop() override;
	Cell CanMove(Cell finish, Desk& desk) override;
	Type GetType() const override;
	Bishop* Clone() const override;
	std::list<Cell> GetPossibleMoves() const override;
};

