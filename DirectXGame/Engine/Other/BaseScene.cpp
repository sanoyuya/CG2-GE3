#include "BaseScene.h"
myMath::Vector2 BaseScene::windowsSize_;
myMath::Vector2 BaseScene::windowsCenter_;

void BaseScene::StaticInitialize(WindowsApp* windowsApp)
{
	windowsSize_ = { windowsApp->GetWidth(),windowsApp->GetHeight() };
	windowsCenter_ = { windowsApp->GetWidth() / 2,windowsApp->GetHeight() / 2 };
}