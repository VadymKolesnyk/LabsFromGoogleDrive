#pragma once
#include "Figure.h"
class King :
	public Figure
{
public:
	King(char vert, int hor, Color color);
	~King() override;
	Cell CanMove(Cell finish, Desk& desk) override;
	bool CanAttack(Cell& finish, Desk& desk) override;
	Type GetType() const override;
	King* Clone() const override;
	std::list<Cell> GetPossibleMoves() const override;
};

