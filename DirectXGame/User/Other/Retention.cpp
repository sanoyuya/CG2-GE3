#include "Retention.h"

void Retention::SetWindowData(WindowsApp* windowsApp)
{
	windowsSize_ = { windowsApp->GetWidth(),windowsApp->GetHeight() };
	windowsCenter_ = { windowsApp->GetWidth() / 2,windowsApp->GetHeight() / 2 };
}

myMath::Vector2 Retention::GetWindowsSize()
{
	return windowsSize_;
}

myMath::Vector2 Retention::GetWindowsCenter()
{
	return windowsCenter_;
}

void Retention::SetStageNum(const Stage stageNum)
{
	stageNum_ = stageNum;
}

const Stage Retention::GetStageNum()
{
	return stageNum_;
}

Retention* Retention::GetInstance()
{
	static Retention instance;
	return &instance;
}