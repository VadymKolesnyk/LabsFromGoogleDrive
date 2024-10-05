#include "Snapshot.h"

Snapshot::Snapshot(Game* game, Desk& desk, Color& turn, Cell& attaked)
{
	this->game = game;
	this->desk = desk;
	this->turn = turn;
	this->attacked = attacked;
}

void Snapshot::restore()
{
	this->game->SetData(this->desk, this->turn, this->attacked);
}
