#include "SinglePlayerMode.h"
#include "View.h"
#include "GameModel.h"

SinglePlayerMode::SinglePlayerMode(View & view, GameModel & game)
	: view(view), game(game)
{
}

SinglePlayerMode::~SinglePlayerMode()
{
}

void SinglePlayerMode::start()
{
	int playerId = 0;
	while (game.getStatus() == GameStatus::InProgress)
	{
		playerId %= 2;
		int x, y;
		if (!playerId)
		{
			x = view.prompt("x = ");
			y = view.prompt("y = ");
			game.putMark(CellValue::X, x, y);
		}
		else
		{
			for (int i = 0; i < game.size * game.size; ++i)
			{
				x = i % game.size;
				y = i / game.size;
				if (game.getCellValue(x, y) == CellValue::Blank) break;
			}
			game.putMark(CellValue::O, x, y);
		}
		view.show(game);
		++playerId;
	}
	switch (game.getStatus())
	{
	case GameStatus::Draw: view.message("Game is draw"); break;
	case GameStatus::XWon: view.message("Player won"); break;
	case GameStatus::OWon: view.message("AI won"); break;
	}
}
