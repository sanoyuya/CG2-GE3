#include "GameHeader.h"
#include"InputManager.h"
myMath::Vector2 GameHeader::windowsSize_;
myMath::Vector2 GameHeader::windowsCenter_;
float GameHeader::sFps_ = 60.0f;
bool GameHeader::isImgui_ = false;

void GameHeader::SetApp(WindowsApp* app)
{
	windowsSize_ = { app->GetWidth(),app->GetHeight() };
	windowsCenter_ = { app->GetWidth() / 2,app->GetHeight() / 2 };
}

void GameHeader::ImGuiUpdate()
{
	if (InputManager::GetInstance()->KeyboardTriggerPush(DIK_F11))
	{
		if (isImgui_ == false)
		{
			isImgui_ = true;
		}
		else
		{
			isImgui_ = false;
		}
	}
}