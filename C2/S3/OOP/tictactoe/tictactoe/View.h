#pragma once
#include "GameModel.h"
#include <string>
class View
{
public:
	virtual void show(const GameModel& game) = 0;
	virtual void message(const std::string & text) = 0;
	virtual int prompt(const std::string & text) = 0;
};