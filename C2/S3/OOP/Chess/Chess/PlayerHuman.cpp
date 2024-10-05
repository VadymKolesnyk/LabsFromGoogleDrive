#include "PlayerHuman.h"

PlayerHuman::PlayerHuman(Game* game, View* view):Player(game, view)
{
}

PlayerHuman::PlayerHuman():Player()
{
}

Type PlayerHuman::PromptType(const std::string& text)
{
	return view->PromptType(text);
}

std::vector<Cell> PlayerHuman::PromptTurn(const std::string& text)
{
	return view->PromptTurn(text);
}