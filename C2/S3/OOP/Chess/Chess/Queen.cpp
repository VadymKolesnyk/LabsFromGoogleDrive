#include "Queen.h"



Queen::Queen(const Figure* other) : Figure(other)
{
}

Queen::Queen(char vert, int hor, Color color) :Figure(vert, hor, color)
{
}


Queen::~Queen()
{
}

Cell Queen::CanMove(Cell finish, Desk& desk)
{
	if (!desk.IsCellOnDesk(finish))
		return Cell();
	if (this->cell == finish)
		return Cell();
	if ((this->cell.GetHor() != finish.GetHor()) && (this->cell.GetVert() != finish.GetVert()))
		if (abs(this->cell.GetHor() - finish.GetHor()) != abs(this->cell.GetVert() - finish.GetVert()))
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

Type Queen::GetType() const
{
	return Type::Queen;
}

Queen * Queen::Clone() const
{
	return new Queen(*this);
}

std::list<Cell> Queen::GetPossibleMoves() const
{
	Cell position = this->cell;
	Cell temp;
	std::list<Cell> Moves;
	for (int step = 1; step <= 7; step++)
	{
		temp = Cell(position.GetHor() + step, position.GetVert() + step);
		if (temp.IsOnDesk())
			Moves.push_back(temp);
		temp = Cell(position.GetHor() + step, position.GetVert() - step);
		if (temp.IsOnDesk())
			Moves.push_back(temp);
		temp = Cell(position.GetHor() - step, position.GetVert() + step);
		if (temp.IsOnDesk())
			Moves.push_back(temp);
		temp = Cell(position.GetHor() - step, position.GetVert() - step);
		if (temp.IsOnDesk())
			Moves.push_back(temp);
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
