#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include<memory>
#include"Camera.h"
#include"Sprite.h"
#include"TextureManager.h"
#include"DrawManager.h"

class GameScene
{
private:

	//クラス読み込み
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Camera>camera;

	std::unique_ptr<DrawManager>draw;
	TextureData tex;
	std::unique_ptr<DrawManager>draw2;
	TextureData tex2;

	uint32_t titleBGM;

	float angle = 0.0f;
	myMath::Vector2 hoge = { 0,0 };

	float timeY = 0;

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