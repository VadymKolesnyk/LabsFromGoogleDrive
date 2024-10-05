#include "King.h"



King::King(char vert, int hor, Color color) :Figure(vert, hor, color)
{
}


King::~King()
{
}

Cell King::CanMove(Cell finish, Desk& desk)
{
	if (!desk.IsCellOnDesk(finish))
		return Cell();
	if (this->timeOnCell == desk.GetTime())
	{
		if (abs(this->cell.GetHor() - finish.GetHor()) == 2)
		{
			if (desk.IsCheckOnCell(this->cell, this->color))
				return Cell();
			int step = abs(finish.GetHor() - this->GetHor()) / (finish.GetHor() - this->GetHor());
			Cell intermediate(this->GetHor() + step, finish.GetVert());
			if (desk.IsCheckOnCell(intermediate, this->color) || desk.IsCheckOnCell(finish, this->color))
				return Cell();
			for (Figure* figure : desk.GetFigures())
			{
				if ((figure->GetPosition() == intermediate) || (figure->GetPosition() == finish))
					return Cell();
				if (step < 0 && figure->GetPosition() == Cell('b', this->GetVert()))
					return Cell();
			}
			for (Figure* figure : desk.GetFigures())
			{
				if ((figure->GetColor() == this->GetColor()) && (figure->GetType() == Type::Rook))
				{
					if (figure->GetTime() == desk.GetTime())
					{
						int newStep = abs(figure->GetHor() - this->GetHor()) / (figure->GetHor() - this->GetHor());
						if (newStep == step)
							return finish;
					}
				}
			}
		}
	}
	if (this->cell == finish)
		return Cell();
	if ((abs(this->cell.GetHor() - finish.GetHor()) <= 1) && (abs(this->cell.GetVert() - finish.GetVert()) <= 1))
	{
		return finish;
	}
	return Cell();
}

bool King::CanAttack(Cell& finish, Desk& desk)
{
	if (this->cell == finish)
		return false;
	if ((abs(this->cell.GetHor() - finish.GetHor()) <= 1) && (abs(this->cell.GetVert() - finish.GetVert()) <= 1))
	{
		return true;
	}
	return false;
}

Type King::GetType() const
{
	return Type::King;
}

King * King::Clone() const
{
	return new King(*this);
}

std::list<Cell> King::GetPossibleMoves() const
{
	std::list<Cell> Moves;
	Cell position(this->GetPosition());
	Cell temp;
	for (int vertStep = -1; vertStep <= 1; vertStep++)
		for (int horStep = -1; horStep <= 1; horStep++)
		{
			temp = Cell(position.GetHor() + horStep, position.GetVert() + vertStep);
			if (temp.IsOnDesk() && temp != position)
				Moves.push_back(temp);
		}
	return Moves;
}
