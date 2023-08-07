#pragma once
#include"DrawOversight.h"
#include"BaseScene.h"

class DemoScene:public BaseScene
{
private:

	std::unique_ptr<Sprite>sprite_;
	uint32_t spriteTex_ = 0;
	float angle_ = 0.0f;

public:

	//初期化処理
	void Initialize()override;

	//終了処理
	void Destroy()override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;
};

