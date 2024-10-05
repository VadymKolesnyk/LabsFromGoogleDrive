#include "GameModel.h"
#include "ListView.h"
#include "BoardView.h"
#include "SinglePlayerMode.h"
#include "MultiPlayerMode.h"
#include "MatrixModel.h"

int main()
{
	MatrixModel      game [2];
	ListView         list;
	BoardView        board;

	MultiPlayerMode  multiPlayerGame(board, game[0]);
	SinglePlayerMode singlePlayerGame(board, game[1]);

	multiPlayerGame.start();
	singlePlayerGame.start();

	return 0;
}