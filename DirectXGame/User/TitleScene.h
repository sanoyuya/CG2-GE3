#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"DrawOversight.h"
#include"Camera.h"
#include"AudioManager.h"
#include"Collision.h"
#include"LevelEditor.h"
#include <map>

//タイトルシーン
class TitleScene :public BaseScene
{
private:

	//クラス読み込み
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Camera>camera;

	//天球
	std::unique_ptr<DrawOversight>skyDome;
	Transform skyDomeTrans;
	uint32_t skyDomeTex;

	myMath::Vector3 cameraPos;
	float angleX = 0.0f;
	float angleY = 0.0f;
	const float length = 50.0f;

	LevelData* levelData = nullptr;
	std::map<std::string, Model*>models;
	std::vector<Model*>objects;
	std::vector<Transform>transforms;

	uint32_t playerTex = 0;
	uint32_t sphereTex = 0;
	uint32_t tex = 0;

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
	
	void camUpdate();
};