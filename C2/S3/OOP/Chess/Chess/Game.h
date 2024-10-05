#pragma once
#include "Desk.h"
#include "Player.h"
#include "Figure.h"
#include "Snapshot.h"
#include <vector>
enum class Status { InProgress, WhiteWon, BlackWon, Draw };
class Snapshot;
class Game
{
private:
	Desk desk;
	Color turn;
	Cell attacked;
public:
	Game(const Desk& desk, Color turn);
	Game();
	~Game();
	void SetData(Desk& desk, Color& turn, Cell& attacked);
	std::list<Figure*> GetFigures() const;
	Cell GetAttacked() const;
	int GetAmount() const;
	Status GetStatus();
	Figure* CanMove(std::vector<Cell> turn);
	Figure* CanMove(Figure* figure, Cell finish);
	void DoTurn(Figure* figure, Cell& finish);
	bool IsPawnOnLastLine(Figure* figure) const;
	void GiveTurn();
	Color GetColorTurn();
	bool Is—heck();
	bool Is—heck(Color colorKing);
	bool IsStalemate();
	void ChangeFigure(const Cell& cell, Type type);
	Snapshot* CreateSnapshot();
	std::list<std::vector<Cell>> GetPossibleTurns();
};

