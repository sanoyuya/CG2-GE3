#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include<memory>
#include"Camera.h"
#include"DrawOversight.h"
#include"Transform.h"

class GameScene
{
private:

	//クラス読み込み
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Camera>camera;

	std::unique_ptr<DrawOversight>kami;
	uint32_t kamiTex = 0;
	uint16_t kamiNum = 0;
	float kamiTime = 0.0f;
	myMath::Vector2 hoge = { 0,0 };

	//右下のパッケージタイトル
	std::unique_ptr<DrawOversight>violet;
	uint32_t violetTex = 0;

	//左上のポケモン
	std::unique_ptr<DrawOversight>poke;
	uint32_t pokeTex = 0;
	float flame = 0.0f;
	uint16_t pokeNum = 0;

	//天球
	std::unique_ptr<DrawOversight>model;
	Transform modelTrans;
	uint32_t modelTex;

	//戦闘機のやつ
	std::unique_ptr<DrawOversight>fModel;
	Transform fModelTrans;
	uint32_t fModelTex;
	uint32_t fModel2Tex;
	float angle = 0.0f;

	myMath::Vector3 cameraPos;

	//uint32_t titleBGM = 0;

public:
	GameScene();
	~GameScene();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
};