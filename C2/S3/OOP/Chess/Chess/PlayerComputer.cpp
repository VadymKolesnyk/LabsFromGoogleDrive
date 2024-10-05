#include "PlayerComputer.h"
#include <ctime>

PlayerComputer::PlayerComputer(Game* game, View* view) :Player(game, view)
{
	srand(time(NULL));
}

PlayerComputer::PlayerComputer():Player()
{
}

Type PlayerComputer::PromptType(const std::string& text)
{
	view->Message(text);
	int type = rand() % 4;
	switch (type)
	{
	case 0:
		view->Message(view->GetTypeString(Type::Knight));
		return Type::Knight;
	case 1:
		view->Message(view->GetTypeString(Type::Bishop));
		return Type::Bishop;
	case 2:
		view->Message(view->GetTypeString(Type::Queen));
		return Type::Queen;
	case 3:
		view->Message(view->GetTypeString(Type::Rook));
		return Type::Rook;
	default:
		break;
	}
	return Type::Pawn;
}

std::vector<Cell> PlayerComputer::PromptTurn(const std::string& text)
{
	view->Message(text);
	std::list<std::vector<Cell>> turns = this->game->GetPossibleTurns();
	int randTurn = rand() % turns.size();
	std::list<std::vector<Cell>>::iterator iterator = turns.begin();
	for (int i = 0; i < randTurn; i++)
	{
		iterator++;
	}
	std::vector<Cell> turn = (*iterator);
	std::string message(turn[0].GetHor() + std::to_string(turn[0].GetVert()) + turn[1].GetHor() + std::to_string(turn[1].GetVert()));
	view->Message(message);
	return turn;
}
