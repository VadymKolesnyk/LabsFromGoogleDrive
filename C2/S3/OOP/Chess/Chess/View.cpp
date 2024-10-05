#include "View.h"
View* View::instance = nullptr;
View::View(){}
View::View(const View&){}
std::string View::GetColorString(Color color) const
{
	switch (color)
	{
	case Color::White:
		return "white";
	case Color::Black:
		return "black";
	default:
		return "ERROR_color";
	}
}

std::string View::GetTypeString(Type type) const
{
	switch (type)
	{
	case Type::Pawn:
		return "pawn";
	case Type::Knight:
		return "knight";
	case Type::Bishop:
		return "bishop";
	case Type::Rook:
		return "rook";
	case Type::Queen:
		return "queen";
	case Type::King:
		return "king";
	default:
		return "ERROR_type";
	}
}