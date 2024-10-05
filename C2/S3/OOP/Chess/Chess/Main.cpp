#include <iostream>
#include <string>
#include "Game.h"
#include "DeskConsoleView.h"
#include "ListConsoleView.h"
#include "GameMode.h"
#include "PlayerHuman.h"
#include "PlayerComputer.h"

int main()
{
	Game chess;
	View& view = *(DeskConsoleView::getInstance());
	Player* playerWhite = new PlayerComputer();
	Player* playerBlack = new PlayerHuman();
	GameMode gameMode(view, chess, playerBlack, playerWhite);
	gameMode.start();
	return 0;
}