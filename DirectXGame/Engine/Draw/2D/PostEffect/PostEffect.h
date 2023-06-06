#pragma once
#include"DirectXBase.h"
#include "Sprite2D.h"
#include"myMath.h"

class PostEffect : public Sprite2D
{
private:

	myMath::Vector2 position = { 0.0f,0.0f };
	myMath::Vector2 scale = { 0.0f,0.0f };
	float rotation = 0.0f;
	myMath::Vector4 color = { 0.0f,0.0f,0.0f,0.0f };
	myMath::Vector2 anchorpoint = { 0.0f,0.0f };
	bool flipX = false;
	bool flipY = false;

	uint32_t tex = 0;

public:

	/// <summary>
	/// ‰Šú‰»ˆ—
	/// </summary>
	void Initialize();

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw();
};