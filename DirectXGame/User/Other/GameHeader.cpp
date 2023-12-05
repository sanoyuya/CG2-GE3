#include "GameHeader.h"
myMath::Vector2 GameHeader::windowsSize_;
myMath::Vector2 GameHeader::windowsCenter_;

void GameHeader::SetApp(WindowsApp* app)
{
	windowsSize_ = { app->GetWidth(),app->GetHeight() };
	windowsCenter_ = { app->GetWidth() / 2,app->GetHeight() / 2 };
}