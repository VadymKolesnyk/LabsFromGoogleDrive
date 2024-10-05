#include "ConsoleView.h"
#include <iostream>

void ConsoleView::message(const std::string & text)
{
	std::cout << text << std::endl;
}

int ConsoleView::prompt(const std::string & text)
{
	int result;
	std::cout << text << " ";
	std::cin >> result;
	return result;
}

char ConsoleView::getMarkChar(CellValue mark) const
{
	switch (mark)
	{
		case CellValue::X: return 'x';
		case CellValue::O: return 'o';
		default: return ' ';
	}
}