#include "ConsoleView.h"

void ConsoleView::Message(const std::string& text)
{
	std::cout << text << std::endl;
}

Type ConsoleView::PromptType(const std::string& text)
{
	std::string type;
	while (true)
	{
		std::cout << text;
		std::cin >> type;
		for (int i = 0; i < type.length(); i++)
		{
			type[i] = tolower(type[i]);
		}
		if (type == "queen")
			return Type::Queen;
		else if (type == "rook")
			return Type::Rook;
		else if (type == "knight")
			return Type::Knight;
		else if (type == "bishop")
			return Type::Bishop;
	}
	return Type::Pawn;
}

std::vector<Cell> ConsoleView::PromptTurn(const std::string& text)
{
	std::cout << text;
	int sv, fv;
	char sh, fh;
	std::cin >> sh >> sv >> fh >> fv;
	std::vector<Cell> turn(2);
	turn[0].SetCoord(sh, sv);
	turn[1].SetCoord(fh, fv);
	return turn;
}

