#include "BuildingBase.h"
Camera* BuildingBase::sCamera_;
GameTimer* BuildingBase::sGameTimer_;

void BuildingBase::StaticInitialize()
{
}

void BuildingBase::SetCamera(Camera* camera)
{
	sCamera_ = camera;
}

void BuildingBase::SetGameTimer(GameTimer* gameTimer)
{
	sGameTimer_ = gameTimer;
}