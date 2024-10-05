#include "Knight.h"



Knight::Knight(const Figure* other) : Figure(other)
{
}

Knight::Knight(char vert, int hor, Color color) :Figure(vert, hor, color)
{
}


Knight::~Knight()
{
}
Cell Knight::CanMove(Cell finish, Desk& desk)
{
	if (!desk.IsCellOnDesk(finish))
		return Cell();
	if (this->cell == finish)
		return Cell();
	if ((abs(this->cell.GetHor() - finish.GetHor()) != 1) || (abs(this->cell.GetVert() - finish.GetVert()) != 2))
		if ((abs(this->cell.GetHor() - finish.GetHor()) != 2) || (abs(this->cell.GetVert() - finish.GetVert()) != 1))
			return Cell();
	return finish;
}

Type Knight::GetType() const
{
	return Type::Knight;
}

Knight * Knight::Clone() const
{
	return new Knight(*this);
}

std::list<Cell> Knight::GetPossibleMoves() const
{
	Cell position = this->cell;
	Cell temp;
	std::vector<int> steps2 = { -2, 2 };
	std::vector<int> steps1 = { -1, 1 };
	std::list<Cell> Moves;
	for (int step1 : steps1)
	{
		for (int step2 : steps2)
		{
			temp = Cell(position.GetHor() + step1, position.GetVert() + step2);
			if (temp.IsOnDesk())
				Moves.push_back(temp);
			temp = Cell(position.GetHor() + step2, position.GetVert() + step1);
			if (temp.IsOnDesk())
				Moves.push_back(temp);
		}
	}
	Moves.push_back(temp);
	return Moves;
}
