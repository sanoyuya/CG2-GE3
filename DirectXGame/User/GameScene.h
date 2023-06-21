#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include"Camera.h"
#include"DrawOversight.h"
#include"BaseScene.h"
#include"Collision.h"
#include"LightManager.h"

class GameScene :public BaseScene
{
private:

	//クラス読み込み
	InputManager* input_ = nullptr;
	AudioManager* audioManager_ = nullptr;

	std::unique_ptr<Camera>camera_;
	std::unique_ptr<LightManager>lightManager_;
	myMath::Vector3 lightPos_ = { 0.0f,0.0f ,0.0f };
	myMath::Vector3 lightColor_ = { 0.0f,0.0f ,0.0f };
	myMath::Vector3 lightAtten_ = { 0.0f,0.0f ,0.0f };

	//天球
	std::unique_ptr<Model>model_;
	Transform modelTrans_;
	uint32_t modelTex_;

	//Phong球
	std::unique_ptr<Model>sphere_;
	Transform sphereTrans_;
	uint32_t sphereTex_;
	uint32_t sphereTex2_;
	Sphere spherePos_;
	float sphereTime_;
	myMath::Vector4 color_ = { 0.5f,0.0f,0.0f ,1.0f };
	bool texFlag_ = false;

	//Toon球
	std::unique_ptr<Model>sphere2_;
	Transform sphere2Trans_;
	uint32_t sphere2Tex_ = 0;

	//リムライト球
	std::unique_ptr<Model>sphere3_;
	Transform sphere3Trans_;

	std::unique_ptr<Model>lightSphere_;
	Transform lightSphereTrans_;
	bool lightDisplayFlag_ = false;

	myMath::Vector3 cameraPos_;
	float angleX_ = 0.0f;
	float angleY_ = 0.0f;
	const float length_ = 50.0f;

	std::unique_ptr<Model>assimpModel_;
	Transform assimpModelTrans_;
	uint32_t assimpModelTex_;

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
	void ImGuiUpdate();
};