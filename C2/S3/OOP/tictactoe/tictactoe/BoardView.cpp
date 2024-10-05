#include "BoardView.h"
#include <iostream>

void BoardView::show(const GameModel & game)
{
	std::cout << std::endl;
	for (int y = 0; y < game.size; ++y)
	{
		for (int x = 0; x < game.size; ++x)
			std::cout << getMarkChar(game.getCellValue(x, y)) << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
