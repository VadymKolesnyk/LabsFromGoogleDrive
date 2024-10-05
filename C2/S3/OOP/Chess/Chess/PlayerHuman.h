#pragma once
#include "Player.h"
class PlayerHuman :
	public Player
{
public:
	PlayerHuman();
	PlayerHuman(Game* game, View* view);
	Type PromptType(const std::string& text);
	std::vector<Cell> PromptTurn(const std::string& text);
};

