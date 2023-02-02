#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"DrawOversight.h"
#include"Camera.h"
#include"Collision.h"

class Scene3 :public BaseScene
{
private:

	//クラス読み込み
	InputManager* input = nullptr;

	std::unique_ptr<Camera>camera;

	//天球
	std::unique_ptr<DrawOversight>model;
	Transform modelTrans;
	uint32_t modelTex;

	//レイ
	std::unique_ptr<DrawOversight>ray;
	Transform rayTrans;
	uint32_t rayTex;
	Ray rayPos;
	float rayTime;
	myMath::Vector4 color = { 0.0f,0.0f,0.0f ,0.0f };

	//キューブ
	std::unique_ptr<DrawOversight>cube;
	Transform cubeTrans;

	//床
	std::unique_ptr<DrawOversight>plane;
	Transform planeTrans;
	uint32_t planeTex = 0;
	Plane planePos;

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
	void CamUpdate();
};