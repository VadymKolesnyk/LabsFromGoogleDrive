#pragma once
#include "Game.h"
class Game;
class Snapshot
{
private:
	Game* game;
	Desk desk;
	Color turn;
	Cell attacked;
public:
	Snapshot(Game* game, Desk& desk, Color& turn, Cell& attaked);
	void restore();
};

