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

#pragma comment(lib, "d3dcompiler.lib")

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	WindowsApp* windowsApp = WindowsApp::GetInstance();//WindowsAppクラス読み込み
	windowsApp->CreatWindow(L"DirectXGame");//ウィンドウ作成

	std::unique_ptr<FPS>fps = std::make_unique<FPS>();
	fps->Initialize();

	//DirectX初期化処理 ここから

	DirectX_* directX = DirectX_::GetInstance();//DirectX_クラス読み込み
	directX->Initialize();

	//キー取得開始
	InputManager* input = InputManager::GetInstance();
	input->Initialize();

	// オーディオの初期化
	AudioManager* audioManager = AudioManager::GetInstance();
	audioManager->Initialize();

	//DirectX初期化処理 ここまで

	//描画初期化処理ここから

	TextureManager* textureManager = TextureManager::GetInstance();
	textureManager->StaticInitialize();

	Sprite2D::StaticInitialize();

	Model::StaticInitialize();

	//描画初期化処理ここまで

	std::unique_ptr<GameScene>gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();

	// ゲームループ
	while (true)
	{
		if (!windowsApp->MessageWindow())
		{
			break;
		}

		input->Update();
		audioManager->Update();

		directX->SetClearColor();//背景色を設定 初期値(水色)
		directX->UpdateClear();

		//更新処理
		gameScene->Update();

		//描画処理
		gameScene->Draw();

		directX->UpdateEnd();

		//FPS制御
		fps->Update();
	}
	windowsApp->Break();
	directX->Destroy();
	textureManager->Destroy();
	audioManager->Destroy();

	return 0;
}