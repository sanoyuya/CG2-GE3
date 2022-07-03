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

	DirectX_.DrawInitialize();

	//描画初期化処理ここまで



	//宣言
	//const int window_width = 1280;//横幅
	//const int window_height = 720;//縦幅

	//Matrix4 MATRIX4;

	//

	////ビュー変換行列	
	//XMMATRIX matView;
	//float angle = 0.0f;//カメラの回転角
	////カメラ生成
	//XMFLOAT3 eye = { 0, 30, -100 };	//視点座標
	//XMFLOAT3 target = { 0, 0, 0 };	//注視点座標
	//XMFLOAT3 up = { 0, 1, 0 };		//上方向ベクトル

	////射影変換行列(透視投影)
	//XMMATRIX matProjection = XMMatrixPerspectiveFovLH(ChangeRadians(45.0f),
	//	(float)window_width / window_height,
	//	0.1f, 1000.0f
	//);



	// ゲームループ
	while (true) {

		if (!windowsApp.MessageWindow()) {
			break;
		}

		input.KeyboardUpdate();
		input.MouseUpdate();

		DirectX_.UpdateClear();

		//更新処理

		//if (input.KeyboardKeepPush(DIK_W) || input.KeyboardKeepPush(DIK_S) || input.KeyboardKeepPush(DIK_D) || input.KeyboardKeepPush(DIK_A)) {
		//	//座標を移動する処理(Z座標)
		//	if (input.KeyboardKeepPush(DIK_W)) { position.z += 1.0f; }
		//	else if (input.KeyboardKeepPush(DIK_S)) { position.z -= 1.0f; }
		//	if (input.KeyboardKeepPush(DIK_D)) { position.x += 1.0f; }
		//	else if (input.KeyboardKeepPush(DIK_A)) { position.x -= 1.0f; }
		//}
		//if (input.KeyboardKeepPush(DIK_UP) || input.KeyboardKeepPush(DIK_DOWN) || input.KeyboardKeepPush(DIK_RIGHT) || input.KeyboardKeepPush(DIK_LEFT)) {
		//	//座標を移動する処理(Z座標)
		//	if (input.KeyboardKeepPush(DIK_UP)) { rotation.x += 1.0f; }
		//	else if (input.KeyboardKeepPush(DIK_DOWN)) { rotation.x -= 1.0f; }
		//	if (input.KeyboardKeepPush(DIK_RIGHT)) { rotation.y -= 1.0f; }
		//	else if (input.KeyboardKeepPush(DIK_LEFT)) { rotation.y += 1.0f; }
		//}
		//if (input.KeyboardKeepPush(DIK_U) || input.KeyboardKeepPush(DIK_I) || input.KeyboardKeepPush(DIK_J) || input.KeyboardKeepPush(DIK_K) || input.KeyboardKeepPush(DIK_N) || input.KeyboardKeepPush(DIK_M)) {
		//	if (input.KeyboardKeepPush(DIK_U)) { scale.x += 0.1f; }
		//	else if (input.KeyboardKeepPush(DIK_I)) { scale.x -= 0.1f; }
		//	if (input.KeyboardKeepPush(DIK_J)) { scale.y += 0.1f; }
		//	else if (input.KeyboardKeepPush(DIK_K)) { scale.y -= 0.1f; }
		//	if (input.KeyboardKeepPush(DIK_N)) { scale.z += 0.1f; }
		//	else if (input.KeyboardKeepPush(DIK_M)) { scale.z -= 0.1f; }
		//	if (scale.x < 0.1) { scale.x = 0.1f; }
		//	if (scale.y < 0.1) { scale.y = 0.1f; }
		//	if (scale.z < 0.1) { scale.z = 0.1f; }
		//}


		//描画処理



		DirectX_.UpdateEnd();

		DirectX_.DrawUpdate();
	}
	windowsApp.Break();

	return 0;
}