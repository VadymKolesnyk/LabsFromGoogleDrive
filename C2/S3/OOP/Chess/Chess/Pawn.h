#pragma once
#include "Figure.h"
class Pawn :
	public Figure
{
public:
	Pawn(char vert, int hor, Color color);
	~Pawn() override;
	Cell CanMove(Cell finish, Desk& desk) override;
	bool CanAttack(Cell& finish, Desk& desk) override;
	Type GetType() const override;
	Pawn* Clone() const override;
	std::list<Cell> GetPossibleMoves() const override;
};

