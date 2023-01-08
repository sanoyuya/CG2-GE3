#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include<memory>
#include"Camera.h"
#include"DrawOversight.h"
#include"Transform.h"
#include"Sprite.h"
#include"BaseScene.h"

class GameScene :public BaseScene
{
private:

	//クラス読み込み
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Camera>camera;

	//天球
	std::unique_ptr<DrawOversight>model;
	Transform modelTrans;
	uint32_t modelTex;

	//ステージキューブ
	std::unique_ptr<DrawOversight>cube;
	Transform cubeTrans;
	uint32_t cubeTex;

	//球
	std::unique_ptr<DrawOversight>sphere;
	Transform sphereTrans;
	uint32_t sphereTex;

	//2Dスプライト
	std::unique_ptr<Sprite>sprite;
	uint32_t spriteTex;

	//3Dスプライト
	std::unique_ptr<Sprite>sprite3D;
	Transform sprite3DTrans;
	uint32_t sprite3DTex;

	myMath::Vector3 cameraPos;
	float angleX = 0.0f;
	float angleY = 0.0f;
	const float length = 50.0f;

	uint8_t scene = 0;

public:

	//初期化処理
	void Initialize()override;

	//終了処理
	void Destroy()override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;

private:
	void Rotation();
	void CamMove();
	void Reset();
};