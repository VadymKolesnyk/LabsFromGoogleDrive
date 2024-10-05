#pragma once
#include "View.h"
#include "Game.h"
#include "Snapshot.h"
#include "stack"

class GameMode
{
protected:
	View& view;
	Game& game;
	Player* playerWhite;
	Player* playerBlack;
	std::stack<Snapshot*> preservations;
public:
	void start();
	GameMode(View& view, Game& game, Player* playerBlack, Player* playerWhite);
};

