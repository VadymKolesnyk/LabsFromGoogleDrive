#include "Player.h"



//Player::Player()
//{
//}


Player::Player(Game* game, View* view)
{
	this->view = view;
	this->game = game;
}

void Player::SetData(Game* game, View* view)
{
	this->view = view;
	this->game = game;
}

Player::Player()
{
	this->view = nullptr;
	this->game = nullptr;
}

Player::~Player()
{
}
