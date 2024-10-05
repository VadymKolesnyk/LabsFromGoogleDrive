#pragma once
#include "GameMode.h"
class MultiPlayerMode :
	public GameMode
{
public:
	MultiPlayerMode(View& view, Game& game);
	~MultiPlayerMode();
	void start();
};

