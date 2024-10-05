#pragma once
#include "GameMode.h"
class View;
class GameModel;
class SinglePlayerMode :
	public GameMode
{
public:
	SinglePlayerMode(View& view, GameModel& game);
	~SinglePlayerMode();
	void start();
private:
	View& view;
	GameModel& game;
};

