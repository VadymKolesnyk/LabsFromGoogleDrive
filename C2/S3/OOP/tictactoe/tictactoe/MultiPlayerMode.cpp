#include "MultiPlayerMode.h"
#include "View.h"
#include "GameModel.h"

MultiPlayerMode::MultiPlayerMode(View & view, GameModel & game)
	: view(view), game(game)
{
}

MultiPlayerMode::~MultiPlayerMode()
{
}

void MultiPlayerMode::start()
{
	int playerId = 0;
	while (game.getStatus() == GameStatus::InProgress)
	{
		playerId %= 2;
		int x, y;
		x = view.prompt("x = ");
		y = view.prompt("y = ");
		if (!playerId)
		{
			game.putMark(CellValue::X, x, y);
		}
		else
		{
			game.putMark(CellValue::O, x, y);
		}
		view.show(game);
		++playerId;
	}
	switch (game.getStatus())
	{
		case GameStatus::Draw: view.message("Game is draw"); break;
		case GameStatus::XWon: view.message("X's won"); break;
		case GameStatus::OWon: view.message("O's won"); break;
	}
}
