#include "ListConsoleView.h"

void ListConsoleView::show(const Game& game)
{
	std::list<Figure*> figures = game.GetFigures();
	int i = 1;
	for (Figure* figure : figures)
	{
		std::string color, type, hor, vert;
		color = GetColorString(figure->GetColor());
		type = GetTypeString(figure->GetType());
		hor = figure->GetHor();
		vert = std::to_string(figure->GetVert());
		this->Message("figure[" + std::to_string(i++) + "]:");
		this->Message("\ttype = " + type);
		this->Message("\tcolor = " + color);
		this->Message("\tposition = " + hor + vert);
	}
}
