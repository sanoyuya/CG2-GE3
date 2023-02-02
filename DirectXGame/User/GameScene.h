#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include"Camera.h"
#include"DrawOversight.h"
#include"BaseScene.h"
#include"Collision.h"

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

	//球
	std::unique_ptr<DrawOversight>sphere;
	Transform sphereTrans;
	uint32_t sphereTex;
	uint32_t sphereTex2;
	Sphere spherePos;
	float sphereTime;
	myMath::Vector4 color = { 0.0f,0.0f,0.0f ,0.0f };

	//床
	std::unique_ptr<DrawOversight>triangle;
	Triangle trianglePos;
	Transform triangleTrans;
	uint32_t triangleTex = 0;

	myMath::Vector3 cameraPos;
	float angleX = 0.0f;
	float angleY = 0.0f;
	const float length = 50.0f;

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
};