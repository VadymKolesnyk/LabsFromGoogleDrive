#pragma once
#include "GameMode.h"
class View;
class GameModel;
class MultiPlayerMode :
	public GameMode
{
public:
	MultiPlayerMode(View& view, GameModel& game);
	~MultiPlayerMode();
	void start();
private:
	View& view;
	GameModel& game;
};

