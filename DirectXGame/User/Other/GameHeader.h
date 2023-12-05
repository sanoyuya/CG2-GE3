#pragma once
#include"myMath.h"
#include"WindowsApp.h"

class GameHeader
{
public:

	static float sFps_;

	static myMath::Vector2 windowsSize_;
	static myMath::Vector2 windowsCenter_;

	static void SetApp(WindowsApp* app);
};