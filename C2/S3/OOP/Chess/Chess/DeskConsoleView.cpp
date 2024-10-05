#include "DeskConsoleView.h"
DeskConsoleView::DeskConsoleView(){}
DeskConsoleView::DeskConsoleView(const DeskConsoleView&) {}
void DeskConsoleView::show(const Game& game)
{
	std::string desk[16][8];
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			desk[i][j] = "\t";
		}
	}
	std::list<Figure*> figures = game.GetFigures();
	for (Figure* figure : figures)
	{
		std::string color, type;
		color = GetColorString(figure->GetColor()) + '\t';
		type = GetTypeString(figure->GetType()) + '\t';
		desk[2 * (figure->GetHor() - 'a')][figure->GetVert() - 1] = color;
		desk[2 * (figure->GetHor() - 'a') + 1][figure->GetVert() - 1] = type;
	};
	this->Message("\t|   a   |   b   |   c   |   d   |   e   |   f   |   g   |   h   |");
	this->Message("     --------------------------------------------------------------------");
	for (int j = 0; j < 8; j++)
	{
		std::string m;
		m = ("     " + std::to_string(j + 1) + "\t|");
		for (int i = 0; i < 8; i++)
		{
			m += (desk[2 * i][j] + "|");
		}
		this->Message(m);
		m = "\t|";
		for (int i = 0; i < 8; i++)
		{
			m += (desk[2 * i + 1][j] + "|");
		}
		this->Message(m);
		this->Message("     --------------------------------------------------------------------");
	}
}

View* DeskConsoleView::getInstance()
{
	if (!instance)
		instance = new DeskConsoleView();
	return instance;
}
