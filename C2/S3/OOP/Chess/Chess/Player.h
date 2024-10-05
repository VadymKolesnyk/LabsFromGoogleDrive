#pragma once
#include "Desk.h"
#include "Game.h"
#include "View.h"
#include <string>
class Game;
class View;
class Player
{
protected:
	Game* game;
	View* view;
public:
	Player();
	Player(Game* game, View* view);
	void SetData(Game* game, View* view);
	~Player();
	virtual std::vector<Cell> PromptTurn(const std::string& text) = 0;
	virtual Type PromptType(const std::string& text) = 0;
};

