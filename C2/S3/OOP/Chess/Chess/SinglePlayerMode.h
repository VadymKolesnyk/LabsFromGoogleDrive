#pragma once
#include "GameMode.h"

class SinglePlayerMode :
	public GameMode
{
public:
	SinglePlayerMode(View& view, Game& game);
	~SinglePlayerMode();
	void start();
};

