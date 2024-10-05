#include "Game.h"



Game::Game(const Desk& desk,Color turn):desk(desk)
{
	this->turn = turn;
}

Game::Game():desk(), turn(Color::White)
{
}

Game::~Game()
{
}

void Game::SetData(Desk& desk, Color& turn, Cell& attacked)
{
	this->attacked = attacked;
	this->desk = desk;
	this->turn = turn;
}

std::list<Figure*> Game::GetFigures() const
{
	return this->desk.GetFigures();
}

Cell Game::GetAttacked() const
{
	return this->attacked;
}

Status Game::GetStatus()
{
	if (this->GetFigures().size() == 2)
		return Status::Draw;
	if (this->IsStalemate())
		if (this->IsÑheck(this->turn))
			return (this->turn == Color::Black) ? Status::WhiteWon : Status::BlackWon;
		else
			return Status::Draw;
	else
		return Status::InProgress;
}

Figure* Game::CanMove(std::vector<Cell> turn)
{
	Figure *current = nullptr;
	std::list<Figure*> figures = this->desk.GetFigures();
	for (Figure* figure : figures)
	{
		if (figure->GetPosition() == turn[0])
		{
			if (figure->GetColor() != this->turn)
				return nullptr;
			current = figure;
			break;
		}
	}
	if (!current)
		return nullptr;
	return this->CanMove(current, turn[1]);
}

Figure* Game::CanMove(Figure* figure, Cell finish)
{
	std::list<Figure*> figures = this->desk.GetFigures();
	this->attacked = figure->CanMove(finish, this->desk);
	if (this->attacked == Cell())
		return nullptr;
	for (Figure* figure : figures)
	{
		if (figure->GetPosition() == this->attacked)
		{
			if (figure->GetColor() == this->turn)
				return nullptr;
		}
	}

	Cell currentCell(figure->GetPosition());
		Figure* attackedFigure = nullptr;
	for (Figure* figure : this->desk.GetFigures())
	{
		if (figure->GetPosition() == this->attacked)
		{
			attackedFigure = figure;
			break;
		}
	}
	if (attackedFigure)
		attackedFigure->ChangePosition('$', 0);
	figure->ChangePosition(finish);
	if (this->IsÑheck(this->turn))
	{
		if (attackedFigure)
			attackedFigure->ChangePosition(this->attacked);
		figure->ChangePosition(currentCell);
		return nullptr;
	}
	if (attackedFigure)
		attackedFigure->ChangePosition(this->attacked);
	figure->ChangePosition(currentCell);
	return figure;
}

void Game::DoTurn(Figure* figure, Cell& finish)
{
	if ((figure->GetType() == Type::King) && (abs(figure->GetHor() - finish.GetHor()) == 2))
	{
		int step = abs(finish.GetHor() - figure->GetHor()) / (finish.GetHor() - figure->GetHor());
		Cell intermediate(figure->GetHor() + step, finish.GetVert());
		for (Figure* rook : this->GetFigures())
		{
			if (step > 0 && rook->GetPosition() == Cell('h' ,figure->GetVert()))
				rook->Move(intermediate);
			if (step < 0 && rook->GetPosition() == Cell('a' ,figure->GetVert()))
				rook->Move(intermediate);
		}
	}
	this->desk.EatFigure(this->attacked);
	figure->Move(finish);
}

bool Game::IsPawnOnLastLine(Figure* figure) const
{
	if (figure->GetType() == Type::Pawn)
	{
		if (((figure->GetColor() == Color::Black) && (figure->GetVert() == 1)) || ((figure->GetColor() == Color::White) && (figure->GetVert() == 8)))
		{
			return true;
		}
	}
	return false;
}

void Game::GiveTurn()
{
	this->desk.AddTime();
	for (Figure *figure : this->GetFigures())
	{
		figure->AddTime();
	}
	//(this->turn == Color::White) ? (this->turn = Color::Black) : (this->turn = Color::White);
	this->turn = !(this->turn);
}

Color Game::GetColorTurn()
{
	return this->turn;
}

bool Game::IsÑheck()
{
	return this->IsÑheck(this->turn);
}

bool Game::IsÑheck(Color colorKing)
{
	for (Figure* figure : this->GetFigures())
	{
		if ((figure->GetType() == Type::King) && (figure->GetColor() == colorKing))
		{
			Cell cell(figure->GetPosition());
			return this->desk.IsCheckOnCell(cell, this->turn);
		}
	}
	return false;
}

bool Game::IsStalemate()
{
	Color colorKing = this->turn;
	std::list<Figure*> figures = this->GetFigures();
	for (Figure* figure : figures)
	{
		if (figure->GetColor() == colorKing)
		{
			std::list<Cell> moves = figure->GetPossibleMoves();
			for (Cell move : moves)
			{
				if (this->CanMove(figure, move))
				{
					return false;
				}
			}
		}
	}
	return true;
}

void Game::ChangeFigure(const Cell& cell, Type type)
{
	this->desk.ChangeFigure(cell, type);
}

Snapshot* Game::CreateSnapshot()
{
	return new Snapshot(this, this->desk, this->turn, this->attacked);
}

std::list<std::vector<Cell>> Game::GetPossibleTurns()
{
	Color colorPlayer = this->turn;
	const int start = 0;
	const int finish = 1;
	std::list<std::vector<Cell>> turns;
	std::list<Figure*> figures = this->GetFigures();
	for (Figure* figure : figures)
	{
		if (figure->GetColor() == colorPlayer)
		{
			std::list<Cell> moves = figure->GetPossibleMoves();
			for (Cell move : moves)
			{
				if (this->CanMove(figure, move))
				{
					std::vector<Cell> turn(2);
					turn[start] = figure->GetPosition();
					turn[finish] = move;
					turns.push_back(turn);
				}
			}
		}
	}
	return turns;
}

int Game::GetAmount() const
{
	return this->desk.GetAmount();
}