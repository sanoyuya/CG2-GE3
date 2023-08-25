#pragma once
#include"DrawOversight.h"
#include"BaseScene.h"

class StageSelectScene :public BaseScene
{
private:

	std::unique_ptr<Sprite>sprite_;
	uint32_t spriteTex_ = 0;
	float angle_ = 0.0f;

public:

	//‰Šú‰»ˆ—
	void Initialize()override;

	//I—¹ˆ—
	void Destroy()override;

	//XVˆ—
	void Update()override;

	//•`‰æˆ—
	void Draw()override;
};