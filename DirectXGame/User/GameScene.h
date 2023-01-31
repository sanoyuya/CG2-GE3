#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include"Camera.h"
#include"DrawOversight.h"
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

	std::unique_ptr<DrawOversight>object;
	Transform objectTrans;
	uint32_t cubeTex;
	uint32_t objectTex;
	myMath::Vector4 objectColor = {};
	bool texFlag = false;

	std::unique_ptr<DrawOversight>object2;
	Transform objectTrans2;

	//球
	std::unique_ptr<DrawOversight>sphere;
	Transform sphereTrans;
	uint32_t sphereTex;

	myMath::Vector3 cameraPos;
	float angleX = 0.0f;
	float angleY = 0.0f;
	const float length = 50.0f;

	float time = 0.0f;

	uint32_t bgm = 0;
	float bgmVolume = 0.0f;
	bool bgmFlag = false;

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