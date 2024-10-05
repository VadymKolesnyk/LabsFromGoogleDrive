#include "ListView.h"
#include <iostream>

void ListView::show(const GameModel & game)
{
	std::cout << std::endl;
	for (int y = 0; y < game.size; ++y)
		for (int x = 0; x < game.size; ++x)
			if (game.getCellValue(x, y) != CellValue::Blank)
				std::cout << x << "," << y << ": " << getMarkChar(game.getCellValue(x, y)) << std::endl;
	std::cout << std::endl;
}
