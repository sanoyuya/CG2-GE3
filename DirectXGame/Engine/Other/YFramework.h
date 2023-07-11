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

//ゲーム全体
class YFramework
{
protected:

	std::wstring title_ = L"";
	float windowWidth_ = 0.0f;//横幅
	float windowHeight_ = 0.0f;//縦幅

	myMath::Vector4 windowColor_ = { 0.0f ,0.0f ,0.0f ,0.0f };

	bool endRequest_ = false;

	std::unique_ptr<WindowsApp> windowsApp_;
	std::unique_ptr<FPS>fps_;

public:

	virtual ~YFramework() = default;

	//初期化処理
	virtual void Initialize();

	//終了処理
	virtual void Destroy();

	//更新処理
	virtual void Update();

	//描画処理
	virtual void SceneDraw() = 0;
	virtual void PostEffectDraw() = 0;

	//終了フラグの取得
	virtual bool& GetEndRequest();

public:

	/// <summary>
	/// ウィンドウの設定
	/// </summary>
	/// <param name="title">タイトルバーの名前</param>
	/// <param name="width">ウィンドウの横幅</param>
	/// <param name="height">ウィンドウの縦幅</param>
	void SetWindowData(const std::string& title = "DirectXGame", const float width = 1280.0f, const float height = 720.0f);

	/// <summary>
	/// ウィンドウの色を変更
	/// </summary>
	/// <param name="color"></param>
	void SetWindowColor(const myMath::Vector4& color = { 0.1f,0.25f,0.5f,0.0f });

	//実行処理
	void Run();
};