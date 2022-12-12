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

	std::unique_ptr<DrawOversight>draw;
	uint32_t tex = 0;
	std::unique_ptr<DrawOversight>draw2;
	uint32_t tex2 = 0;
	std::unique_ptr<DrawOversight>draw3;
	uint32_t tex3 = 0;
	std::unique_ptr<DrawOversight>draw4;
	uint32_t tex4 = 0;
	std::unique_ptr<DrawOversight>violet;
	uint32_t violetTex = 0;
	std::unique_ptr<DrawOversight>poke;
	uint32_t pokeTex = 0;
	float pokeFlame = 0.0f;
	uint16_t pokeNum = 0;
	float flame = 0.0f;
	uint16_t num = 0;

	uint32_t titleBGM = 0;

	float angle = 0.0f;
	myMath::Vector2 hoge = { 0,0 };

	float aTime = 0.0f;
	float reimuTime = 0.0f;

	float mTime = 0.0f;

	std::unique_ptr<DrawOversight>model;
	Transform modelTrans;
	uint32_t modelTex;

	std::unique_ptr<DrawOversight>f;
	Transform fTrans;
	uint32_t fTex;

	myMath::Vector3 cameraPos;

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