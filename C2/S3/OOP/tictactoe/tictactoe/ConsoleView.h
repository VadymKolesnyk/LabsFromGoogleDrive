#pragma once
#include "View.h"
class ConsoleView :
	public View
{
public:
	void message(const std::string & text);
	int prompt(const std::string & text);
protected:
	char getMarkChar(CellValue mark) const;
};

