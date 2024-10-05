#include "Figure.h"

Color operator!(const Color& color)
{
	if (color == Color::White)
		return Color::Black;
	return Color::White;
}

Figure::Figure(const Figure* other)
{
	this->cell = other->cell;
	this->color = other->color;
	this->previous = other->previous;
	this->timeOnCell = other->timeOnCell;
}
Figure::Figure(char vert, int hor, Color color)
{
	this->color = color;
	this->cell.SetCoord(vert, hor);
	this->previous.SetCoord(vert, hor);
	this->timeOnCell = 1;
}

Figure::~Figure()
{
}

bool Figure::CanAttack(Cell& finish, Desk& desk)
{
	return (CanMove(finish, desk) == Cell()) ? false : true;
}

//void Figure::Move(char hor, int vert) 
//{
//	this->cell.SetCoord(hor, vert);
//}

void Figure::Move(const Cell& cell)
{
	this->timeOnCell = 0;
	this->previous = this->cell;
	this->cell = cell;
}

void Figure::AddTime()
{
	this->timeOnCell++;
}

int Figure::GetTime()
{
	return this->timeOnCell;
}

Cell Figure::GetPosition() const
{
	return cell;
}

Cell Figure::GetPreviousPosition() const
{
	return this->previous;
}

int Figure::GetPreviousVert() const
{
	return this->previous.GetVert();
}

char Figure::GetPreviousHor() const
{
	return this->previous.GetHor();
}





void Figure::Copy(const Figure* other)
{
	this->cell = other->cell;
	this->color = other->color;
	this->previous = other->previous;
	this->timeOnCell = other->timeOnCell;
}

Color Figure::GetColor() const
{
	return color;
}

void Figure::ChangePosition(const Cell& cell)
{
	this->cell = cell;
}

void Figure::ChangePosition(char vert, int hor)
{
	Cell cell(vert, hor);
	this->ChangePosition(cell);
}

int Figure::GetVert() const
{
	return this->cell.GetVert();
}
char Figure::GetHor() const
{
	return this->cell.GetHor();
}

