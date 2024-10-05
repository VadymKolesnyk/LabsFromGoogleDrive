#pragma once
#include "Player.h"
class PlayerComputer :
	public Player
{
public:
	PlayerComputer();
	PlayerComputer(Game* game, View* view);
	Type PromptType(const std::string& text);
	std::vector<Cell> PromptTurn(const std::string& text);
};

