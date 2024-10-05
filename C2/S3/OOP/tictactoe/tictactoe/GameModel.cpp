#include "GameModel.h"

GameStatus GameModel::winStatusByMark(CellValue mark)
{
	switch (mark)
	{
	case CellValue::X: return GameStatus::XWon;
	case CellValue::O: return GameStatus::OWon;
	}
	return GameStatus::InProgress;
}