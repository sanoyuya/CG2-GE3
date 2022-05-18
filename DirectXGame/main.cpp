#include<Windows.h>
#include "Input.h"
#include "DirectX_.h"
#include "WindowsApp.h"

#pragma comment(lib, "d3dcompiler.lib")

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WindowsApp windowsApp;//WindowsAppクラス読み込み
	windowsApp.CreatWindow();



	//DirectX初期化処理 ここから

	DirectX_ DirectX_(windowsApp.GetHwnd(), windowsApp.GetW());//DirectXクラス読み込み

	//DirectX初期化処理 ここまで



	//描画初期化処理ここから

	DirectX_.DrawInitiaize();

	//描画初期化処理ここまで



	// ゲームループ
	while (true) {

		if (!windowsApp.MessageWindow()) {
			break;
		}



		//DirectX毎フレーム処理　ここから

		DirectX_.Update();
		DirectX_.DrawUpdate();

		//DirectX毎フレーム処理　ここまで



	}
	windowsApp.Break();

	return 0;
}