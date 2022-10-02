#include<Windows.h>
#include "InputManager.h"
#include "DirectX_.h"
#include "WindowsApp.h"
#include"myMath.h"
#include"GameScene.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WindowsApp* windowsApp = WindowsApp::GetInstance();//WindowsAppクラス読み込み
	windowsApp->CreatWindow();

	//DirectX初期化処理 ここから

	DirectX_ directX_(windowsApp->GetHwnd(), windowsApp->GetW());//DirectXクラス読み込み

	//キー取得開始
	InputManager* input = InputManager::GetInstance();
	input->Initialize();

	//DirectX初期化処理 ここまで

	//描画初期化処理ここから

	directX_.DrawInitialize(windowsApp->GetHwnd(), windowsApp->GetW());

	//描画初期化処理ここまで

	GameScene* gameScene = GameScene::GetInstance();
	gameScene->Initialize();

	// ゲームループ
	while (true) {

		if (!windowsApp->MessageWindow()) {
			break;
		}

		input->Update();

		directX_.UpdateClear();

		//更新処理
		gameScene->Update();

		//描画処理
		gameScene->Draw();

		directX_.UpdateEnd();
		directX_.DrawUpdate();
	}
	windowsApp->Break();

	return 0;
}