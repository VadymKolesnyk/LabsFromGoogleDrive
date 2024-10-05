#pragma once
#include "View.h"
#include <iostream>

class ConsoleView :
	public View
{
public:
	void Message(const std::string& text);
	Type PromptType(const std::string& text);
	std::vector<Cell> PromptTurn(const std::string& text);
};

