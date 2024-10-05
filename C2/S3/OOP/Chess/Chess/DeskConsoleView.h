#pragma once
#include "ConsoleView.h"
class DeskConsoleView :
	public ConsoleView
{
private:
	DeskConsoleView();
	DeskConsoleView(const DeskConsoleView&);
public:
	void show(const Game& game);
	static View* getInstance();
};

