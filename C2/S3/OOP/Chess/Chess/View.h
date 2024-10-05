#pragma once
#include "Game.h"
#include "Cell.h"
#include <vector>
#include <string>
class Game;
class View
{
protected:
	static View* instance;
	View();
	View(const View&);
public:
	virtual void show(const Game& game) = 0;
	virtual void Message(const std::string& text) = 0;
	virtual std::vector<Cell> PromptTurn(const std::string& text) = 0;
	virtual Type PromptType(const std::string& text) = 0;
	std::string GetColorString(Color color) const;
	std::string GetTypeString(Type type) const;
};

