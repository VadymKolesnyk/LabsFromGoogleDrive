#include "Bishop.h"



Bishop::Bishop(const Figure* other):Figure(other)
{
}

Bishop::Bishop(char vert, int hor, Color color) : Figure(vert, hor, color)
{
}


Bishop::~Bishop()
{
}

Cell Bishop::CanMove(Cell finish, Desk& desk) 
{
	if (!desk.IsCellOnDesk(finish))
		return Cell();
	if (this->cell == finish)
		return Cell();
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

Type Bishop::GetType() const
{
	return Type::Bishop;
}

Bishop * Bishop::Clone() const
{
	return new Bishop(*this);
}

std::list<Cell> Bishop::GetPossibleMoves() const
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
	}	
	return Moves;
}
