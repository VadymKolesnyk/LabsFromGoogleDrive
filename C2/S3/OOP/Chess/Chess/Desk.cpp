#include "Desk.h"
#include "Rook.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Bishop.h"

Desk::Desk(const Desk& other)
{
	this->amount = other.amount;
	Figure *f;
	std::list<Figure*> figures = other.figures;
	for (Figure* figure: figures)
	{
		f = figure->Clone();
		this->figures.push_back(f);
	};
	this->time = other.time;
}

Desk::Desk()
{
	amount = 32;
	char c = 'a';
	Figure* f = new Rook(c++, 8, Color::Black);
	this->figures.push_back(f);
	f = new Knight(c++, 8, Color::Black);
	this->figures.push_back(f);
	f = new Bishop(c++, 8, Color::Black);
	this->figures.push_back(f);
	f = new Queen(c++, 8, Color::Black);
	this->figures.push_back(f);
	f = new King(c++, 8, Color::Black);
	this->figures.push_back(f);
	f = new Bishop(c++, 8, Color::Black);
	this->figures.push_back(f);
	f = new Knight(c++, 8, Color::Black);
	this->figures.push_back(f);
	f = new Rook(c++, 8, Color::Black);
	this->figures.push_back(f);
	c = 'a';
	for (int i = 0; i < 8; i++)
	{
		f = new Pawn(c++, 7, Color::Black);
		this->figures.push_back(f);
	}
		
	c = 'a';
	for (int i = 0; i < 8; i++)
	{
		f = new Pawn(c++, 2, Color::White);
		this->figures.push_back(f);
	}
		
	c = 'a';
	f = new Rook(c++, 1, Color::White);
	this->figures.push_back(f);
	f = new Knight(c++, 1, Color::White);
	this->figures.push_back(f);
	f = new Bishop(c++, 1, Color::White);
	this->figures.push_back(f);
	f = new Queen(c++, 1, Color::White);
	this->figures.push_back(f);
	f = new King(c++, 1, Color::White);
	this->figures.push_back(f);
	f = new Bishop(c++, 1, Color::White);
	this->figures.push_back(f);
	f = new Knight(c++, 1, Color::White);
	this->figures.push_back(f);
	f = new Rook(c++, 1, Color::White);
	this->figures.push_back(f);
	this->time = 1;
}

Desk::~Desk()
{
	for (std::list<Figure*>::iterator figure = this->figures.begin(); figure != this->figures.end(); figure++)
	{
		delete *figure;
	}
	this->figures.clear();
}

Desk& Desk::operator=(const Desk& other)
{
	for (Figure* figure : this->figures)
		delete figure;
	this->figures.clear();
	this->amount = other.amount;
	for (Figure* figure : other.figures)
	{
		this->figures.push_back(figure->Clone());
	}
	this->time = other.time;
	return (*this);
}


std::list<Figure*> Desk::GetFigures() const
{
	return this->figures;
}

void Desk::ChangeFigure(const Cell& cell, Type type)
{
	for (std::list<Figure*>::iterator figure = this->figures.begin(); figure != this->figures.end(); figure++)
	{
		if ((*figure)->GetPosition() == cell)
		{
			Figure* changed = *figure;
			Figure* newTypeFigure;
			switch (type)
			{
			case Type::Knight:
				newTypeFigure = new Knight(changed);
				break;
			case Type::Bishop:
				newTypeFigure = new Bishop(changed);
				break;
			case Type::Rook:
				newTypeFigure = new Rook(changed);
				break;
			case Type::Queen:
				newTypeFigure = new Queen(changed);
				break;
			default:
				return;
				break;
			}
			*figure = newTypeFigure;
			delete changed;
		}
	};
}


void Desk::AddTime()
{
	this->time++;
}

int Desk::GetTime()
{
	return this->time;
}

bool Desk::EatFigure(const Cell& cell)
{
	for (std::list<Figure*>::iterator figure = this->figures.begin(); figure != this->figures.end(); figure++)
	{
		if ((*figure)->GetPosition() == cell)
		{
			this->amount--;
			Figure* attacked = *figure;
			this->figures.erase(figure);
			delete attacked;
			return true;
		}
	};
	return false;
}

int Desk::GetAmount() const
{
	return this->amount;
}

std::vector<Cell> Desk::GetLine(Cell start, Cell finish) const
{
	if (start.GetHor() == finish.GetHor())
	{ 
		int size = abs(finish.GetVert() - start.GetVert());
		int step = (finish.GetVert() - start.GetVert()) / size;
		std::vector<Cell> line(size - 1);
		int vert = start.GetVert() + step;
		for (int i = 0; i < size - 1; i++)
		{
			line[i] = Cell(start.GetHor(), vert);
			vert += step;
		}
		return line;
	}
	else if (start.GetVert() == finish.GetVert())
	{
		int size = abs(finish.GetHor() - start.GetHor());
		int step = (finish.GetHor() - start.GetHor()) / size;
		std::vector<Cell> line(size - 1);
		int hor = start.GetHor() + step;
		for (int i = 0; i < size - 1; i++)
		{
			line[i] = Cell(hor, start.GetVert());
			hor += step;
		}
		return line;
	}
	else if (abs(finish.GetHor() - start.GetHor()) == abs(finish.GetVert() - start.GetVert()))
	{
		int size = abs(finish.GetHor() - start.GetHor());
		int stephor = (finish.GetHor() - start.GetHor()) / size;
		int stepvert = (finish.GetVert() - start.GetVert()) / size;
		std::vector<Cell> line(size - 1);
		int hor = start.GetHor() + stephor;
		int vert = start.GetVert() + stepvert;
		for (int i = 0; i < size - 1; i++)
		{
			line[i] = Cell(hor, vert);
			hor += stephor;
			vert += stepvert;
		}
		return line;
	}
	else
	{
		return std::vector<Cell>(1, finish);
	}
}

bool Desk::IsCheckOnCell(Cell& cell, Color colorKing)
{
	for (Figure* figure : this->GetFigures())
	{
		if (figure->GetColor() != colorKing)
		{
			if (figure->CanAttack(cell, *this))
				return true;
		}
	}
	return false;
}

bool Desk::IsCellOnDesk(Cell& cell)
{
	return cell.IsOnDesk();
}


