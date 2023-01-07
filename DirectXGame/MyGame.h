#pragma once
#include<Windows.h>
#include "InputManager.h"
#include "DirectX_.h"
#include "WindowsApp.h"
#include"FPS.h"
#include"myMath.h"
#include"GameScene.h"
#include <memory>
#include"TextureManager.h"
#include"Sprite2D.h"
#include "AudioManager.h"
#include"Model.h"
#include"SpriteCommon.h"

#pragma comment(lib, "d3dcompiler.lib")

//ゲーム全体
class MyGame
{
private:

	WindowsApp* windowsApp = nullptr;
	std::unique_ptr<FPS>fps;
	DirectX_* directX = nullptr;
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;
	TextureManager* textureManager = nullptr;
	std::unique_ptr<GameScene>gameScene;

public:

	//初期化処理
	void Initialize();

	//終了処理
	void Destroy();

	//更新処理
	void Update();

	//描画処理
	void Draw();
};