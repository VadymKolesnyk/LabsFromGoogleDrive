#pragma once
#include "ConsoleView.h"
class ListView :
	public ConsoleView
{
public:
	void show(const GameModel& game);
};

