#include "GameMode.h"

void GameMode::start()
{
	Status status;
	Player* player = this->playerWhite;
	this->view.show(game);
	while ((status = this->game.GetStatus()) == Status::InProgress)
	{
		Snapshot* preservation = this->game.CreateSnapshot();
		this->preservations.push(preservation);
		Figure* current;
		std::vector<Cell> turn(2);
		if (this->game.IsÑheck())
		{
			this->view.Message("Check on " + this->view.GetColorString(this->game.GetColorTurn()) + " king!");
		}
		do
		{
			turn = player->PromptTurn("Enter turn (" + this->view.GetColorString(this->game.GetColorTurn()) + "): ");
		} while (!(current = this->game.CanMove(turn)));
		this->game.DoTurn(current, turn[1]);
		if (this->game.IsPawnOnLastLine(current))
		{
			Type type = player->PromptType("Enter new type of pawn (bishop, khight, queen, rook): ");
			this->game.ChangeFigure(current->GetPosition(), type);
		}
		this->game.GiveTurn();
		(player == this->playerWhite) ? (player = this->playerBlack) : (player = this->playerWhite);
		this->view.show(game);
	}
	switch (status)
	{
	case Status::WhiteWon:
		this->view.Message("White won, black king was checkmated");
		break;
	case Status::BlackWon:
		this->view.Message("Black won, white king was checkmated");
		break;
	case Status::Draw:
		this->view.Message("Draw");
		break;
	default:
		break;
	}
}

GameMode::GameMode(View& view, Game& game, Player* playerBlack, Player* playerWhite) : view(view), game(game), playerBlack(playerBlack), playerWhite(playerWhite)
{
	this->playerBlack->SetData(&game, &view);
	this->playerWhite->SetData(&game, &view);
}
