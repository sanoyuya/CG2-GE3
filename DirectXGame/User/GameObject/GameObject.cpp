#include "GameObject.h"
Camera* GameObject::sCamera_;
GameTimer* GameObject::sGameTimer_;

void GameObject::SetCamera(Camera* camera)
{
	sCamera_ = camera;
}

void GameObject::SetGameTimer(GameTimer* gameTimer)
{
	sGameTimer_ = gameTimer;
}