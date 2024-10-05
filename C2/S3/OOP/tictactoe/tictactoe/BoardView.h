#pragma once
#include "ConsoleView.h"
class BoardView :
	public ConsoleView
{
public:
	void show(const GameModel& game);
};

