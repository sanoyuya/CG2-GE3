#include "Enemy.h"

void Enemy::SetCamera(Camera* camera)
{
	camera_ = camera;
}

void Enemy::SetPlayer(Player* player)
{
	player_ = player;
}

void Enemy::SetGameTimer(GameTimer* gameTimer)
{
	gameTimer_ = gameTimer;
}