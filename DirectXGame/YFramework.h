#pragma once
#include<Windows.h>
#include "InputManager.h"
#include "DirectXBase.h"
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
#include<memory>
#include"ImGuiManager.h"

#pragma comment(lib, "d3dcompiler.lib")

//ゲーム全体
class YFramework
{
protected:

	std::wstring title;
	float window_width = 0;//横幅
	float window_height = 0;//縦幅

	bool endRequest = false;

	WindowsApp* windowsApp = nullptr;
	std::unique_ptr<FPS>fps;
	DirectXBase* directX = nullptr;
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;
	TextureManager* textureManager = nullptr;
	ImGuiManager* imGuiManager = nullptr;

public:

	virtual ~YFramework() = default;

	//初期化処理
	virtual void Initialize();

	//終了処理
	virtual void Destroy();

	//更新処理
	virtual void Update();

	//描画処理
	virtual void Draw() = 0;

	virtual bool& GetEndRequest();

public:

	/// <summary>
	/// ウィンドウの設定
	/// </summary>
	/// <param name="title">タイトルバーの名前</param>
	/// <param name="width">ウィンドウの横幅</param>
	/// <param name="height">ウィンドウの縦幅</param>
	void SetWindowData(const std::string& title = "DirectXGame", const int width = 1280, const int height = 720);

	//実行処理
	void Run();
};