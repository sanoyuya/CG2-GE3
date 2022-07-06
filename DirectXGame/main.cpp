#include<Windows.h>
#include "Input.h"
#include "DirectX_.h"
#include "WindowsApp.h"
#include"myMath.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WindowsApp windowsApp;//WindowsAppクラス読み込み
	windowsApp.CreatWindow();



	//DirectX初期化処理 ここから

	DirectX_ DirectX_(windowsApp.GetHwnd(), windowsApp.GetW());//DirectXクラス読み込み
	//キー取得開始
	Input input;
	input.KeyboardInitialize(windowsApp.GetHwnd(), windowsApp.GetW());//初期化処理
	input.MouseInitialize(windowsApp.GetHwnd(), windowsApp.GetW());

	//DirectX初期化処理 ここまで



	//描画初期化処理ここから

	DirectX_.DrawInitialize(windowsApp.GetHwnd(), windowsApp.GetW());

	//描画初期化処理ここまで



	//宣言


	// ゲームループ
	while (true) {

		if (!windowsApp.MessageWindow()) {
			break;
		}

		input.KeyboardUpdate();
		input.MouseUpdate();

		DirectX_.UpdateClear();

		//更新処理
		
	


		//描画処理



		DirectX_.UpdateEnd();

		DirectX_.DrawUpdate();
	}
	windowsApp.Break();

	return 0;
}