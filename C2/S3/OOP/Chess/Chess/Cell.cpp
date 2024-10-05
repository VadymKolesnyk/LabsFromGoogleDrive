#include "Cell.h"


Cell::Cell()
{
	this->hor = '$';
	this->vert = 0;
}

Cell::Cell(char hor, int vert)
{
	this->hor = hor;
	this->vert = vert;
}
Cell::Cell(const Cell& other)
{
	this->hor = other.hor;
	this->vert = other.vert;
}


Cell::~Cell()
{
}

int Cell::GetVert() const
{
	return this->vert;
}
char Cell::GetHor() const
{
	return this->hor;
}

void Cell::SetCoord(char hor, int vert)
{
	this->vert = vert;
	this->hor = hor;
}
Cell& Cell::operator =(const Cell& other)
{
	this->hor = other.hor;
	this->vert = other.vert;
	return *this;
}

bool Cell::operator ==(const Cell& other) const
{
	return (this->hor == other.hor && this->vert == other.vert);
}

bool Cell::operator!=(const Cell& other) const
{
	return (this->hor != other.hor || this->vert != other.vert);
}

bool Cell::IsOnDesk()
{
	if (this->vert <= 8 && this->vert >= 1)
		if (this->hor <= 'h' && this->hor >= 'a')
			return true;
	return false;
}
