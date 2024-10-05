#include "Pawn.h"



Pawn::Pawn(char vert, int hor, Color color) :Figure(vert, hor, color)
{
}


Pawn::~Pawn()
{
}

Cell Pawn::CanMove(Cell finish, Desk& desk)
{
	if (!desk.IsCellOnDesk(finish))
		return Cell();
	if (this->color == Color::White)
	{
		if ((this->GetVert() == 5) && (finish.GetVert() == 6) && (abs(this->GetHor() - finish.GetHor()) == 1))
			for (Figure* figure : desk.GetFigures())
				if ((figure->GetColor() == Color::Black) && (figure->GetType() == Type::Pawn))
					if ((figure->GetPosition() == Cell(finish.GetHor(), 5)))
						if ((figure->GetPreviousVert() == 7) && (figure->GetTime() == 1))
							return Cell(finish.GetHor(), 5);
		if (finish.GetHor() == this->GetHor())
		{
			if ((this->GetVert() == 2) && (finish.GetVert() == 4))
			{
				Cell cell(this->GetHor(), 3);
				for (Figure* figure : desk.GetFigures())
					if ((figure->GetPosition() == cell) || (figure->GetPosition() == finish))
						return Cell();
				return finish;
			}
			if (this->GetVert() + 1 == finish.GetVert())
			{
				for (Figure* figure : desk.GetFigures())
					if (figure->GetPosition() == finish)
						return Cell();
				return finish;
			}
		}
		if (abs(finish.GetHor() - this->GetHor()) == 1)
			if (this->GetVert() + 1 == finish.GetVert())
				for (Figure* figure : desk.GetFigures())
					if (figure->GetPosition() == finish)
						if (figure->GetColor() == Color::Black)
							return finish;
	}
	if (this->color == Color::Black)
	{
		if ((this->GetVert() == 4) && (finish.GetVert() == 3) && (abs(this->GetHor() - finish.GetHor()) == 1))
			for (Figure* figure : desk.GetFigures())
				if ((figure->GetColor() == Color::White) && (figure->GetType() == Type::Pawn))
					if ((figure->GetPosition() == Cell(finish.GetHor(), 4)))
						if ((figure->GetPreviousVert() == 2) && (figure->GetTime() == 1))
							return Cell(finish.GetHor(), 4);
		if (finish.GetHor() == this->GetHor())
		{
			if ((this->GetVert() == 7) && (finish.GetVert() == 5))
			{
				Cell cell(this->GetHor(), 6);
				for (Figure* figure : desk.GetFigures())
					if ((figure->GetPosition() == cell) || (figure->GetPosition() == finish))
						return Cell();
				return finish;
			}
			if (this->GetVert() - 1 == finish.GetVert())
			{
				for (Figure* figure : desk.GetFigures())
					if (figure->GetPosition() == finish)
						return Cell();
				return finish;
			}
		}
		if (abs(finish.GetHor() - this->GetHor()) == 1)
			if (this->GetVert() - 1 == finish.GetVert())
				for (Figure* figure : desk.GetFigures())
					if (figure->GetPosition() == finish)
						if (figure->GetColor() == Color::White)
							return finish;
	}
	return Cell();
}

bool Pawn::CanAttack(Cell& finish, Desk& desk)
{
	if (this->color == Color::White)
		if (abs(finish.GetHor() - this->GetHor()) == 1)
			if (this->GetVert() + 1 == finish.GetVert())
				return true;
	if (this->color == Color::Black)
		if (abs(finish.GetHor() - this->GetHor()) == 1)
			if (this->GetVert() - 1 == finish.GetVert())
				return true;
	return false;
}

Type Pawn::GetType() const
{
	return Type::Pawn;
}

Pawn * Pawn::Clone() const
{
	return new Pawn(*this);
}

std::list<Cell> Pawn::GetPossibleMoves() const
{
	Cell position = this->cell;
	Cell temp;
	std::list<Cell> Moves;
	if (this->color == Color::Black)
	{
		temp = Cell(position.GetHor(), position.GetVert() - 1);
		if (temp.IsOnDesk())
			Moves.push_back(temp);
		if (position.GetVert() == 7)
		{
			temp = Cell(position.GetHor(), position.GetVert() - 2);
			Moves.push_back(temp);
		}
		temp = Cell(position.GetHor() + 1, position.GetVert() - 1);
		if (temp.IsOnDesk())
			Moves.push_back(temp);
		temp = Cell(position.GetHor() - 1, position.GetVert() - 1);
		if (temp.IsOnDesk())
			Moves.push_back(temp);
	}
	else
	{
		temp = Cell(position.GetHor(), position.GetVert() + 1);
		if (temp.IsOnDesk())
			Moves.push_back(temp);
		if (position.GetVert() == 2)
		{
			temp = Cell(position.GetHor(), position.GetVert() + 2);
			Moves.push_back(temp);
		}
		temp = Cell(position.GetHor() + 1, position.GetVert() + 1);
		if (temp.IsOnDesk())
			Moves.push_back(temp);
		temp = Cell(position.GetHor() - 1, position.GetVert() + 1);
		if (temp.IsOnDesk())
			Moves.push_back(temp);
	}
	return Moves;
}
