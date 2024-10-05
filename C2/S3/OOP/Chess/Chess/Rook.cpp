#include "Rook.h"

Rook::Rook(const Figure* other) : Figure(other)
{
}

Rook::Rook(char vert, int hor, Color color):Figure(vert, hor, color)
{
}

Rook::~Rook()
{
}


Cell Rook::CanMove(Cell finish, Desk& desk)
{
	if (!desk.IsCellOnDesk(finish))
		return Cell();
	if (this->cell == finish)
		return Cell();
	if ((this->cell.GetHor() != finish.GetHor()) && (this->cell.GetVert() != finish.GetVert()))
		return Cell();
	std::vector<Cell> line = desk.GetLine(this->cell, finish);
	for (Cell cell : line)
	{
		for (Figure* figure : desk.GetFigures())
		{
			if (figure->GetPosition() == cell)
			{
				return Cell();
			}
		}
	}
	return finish;
}


Type Rook::GetType() const
{
	return Type::Rook;
}

Rook* Rook::Clone() const
{
	return new Rook(*this);
}

std::list<Cell> Rook::GetPossibleMoves() const
{
	Cell position = this->cell;
	Cell temp;
	std::list<Cell> Moves;
	for (int step = 1; step <= 7; step++)
	{
		temp = Cell(position.GetHor(), position.GetVert() + step);
		if (temp.IsOnDesk())
			Moves.push_back(temp);
		temp = Cell(position.GetHor(), position.GetVert() - step);
		if (temp.IsOnDesk())
			Moves.push_back(temp);
		temp = Cell(position.GetHor() + step, position.GetVert());
		if (temp.IsOnDesk())
			Moves.push_back(temp);
		temp = Cell(position.GetHor() - step, position.GetVert());
		if (temp.IsOnDesk())
			Moves.push_back(temp);
	}
	return Moves;
}
