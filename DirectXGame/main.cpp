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
	input.Initialize(windowsApp.GetHwnd(), windowsApp.GetW());//初期化処理

	//DirectX初期化処理 ここまで



	//描画初期化処理ここから

	DirectX_.DrawInitialize();

	//描画初期化処理ここまで



	//宣言
	const int window_width = 1280;//横幅
	const int window_height = 720;//縦幅

	Matrix4 MATRIX4;

	//ワールド変換行列
	Matrix4 matWorld;
	//スケーリング行列
	Matrix4 matScale;
	//回転行列
	Matrix4 matRot;
	//平行移動行列
	Matrix4 matTrans;
	//座標
	XMFLOAT3 scale = { 1.0f,1.0f,1.0f };
	//回転角
	XMFLOAT3 rotation = { 0.0f,0.0f,0.0f };
	//座標
	XMFLOAT3 position = { 0.0f,0.0f,0.0f };

	//ビュー変換行列	
	XMMATRIX matView;
	float angle = 0.0f;//カメラの回転角
	//カメラ生成
	XMFLOAT3 eye = { 0, 0, -100 };	//視点座標
	XMFLOAT3 target = { 0, 0, 0 };	//注視点座標
	XMFLOAT3 up = { 0, 1, 0 };		//上方向ベクトル

	//射影変換行列(透視投影)
	Matrix4 matProjection = XMMatrixPerspectiveFovLH(ChangeRadians(45.0f),
		(float)window_width / window_height,
		0.1f, 1000.0f
	);



	// ゲームループ
	while (true) {

		if (!windowsApp.MessageWindow()) {
			break;
		}

		input.Update();

		DirectX_.UpdateClear();

		//更新処理

		if (input.KeepPush(DIK_W) || input.KeepPush(DIK_S) || input.KeepPush(DIK_D) || input.KeepPush(DIK_A)) {
			//座標を移動する処理(Z座標)
			if (input.KeepPush(DIK_W)) { position.z += 1.0f; }
			else if (input.KeepPush(DIK_S)) { position.z -= 1.0f; }
			if (input.KeepPush(DIK_D)) { position.x += 1.0f; }
			else if (input.KeepPush(DIK_A)) { position.x -= 1.0f; }
		}
		if (input.KeepPush(DIK_UP) || input.KeepPush(DIK_DOWN) || input.KeepPush(DIK_RIGHT) || input.KeepPush(DIK_LEFT)) {
			//座標を移動する処理(Z座標)
			if (input.KeepPush(DIK_UP)) { rotation.x += 1.0f; }
			else if (input.KeepPush(DIK_DOWN)) { rotation.x -= 1.0f; }
			if (input.KeepPush(DIK_RIGHT)) { rotation.y -= 1.0f; }
			else if (input.KeepPush(DIK_LEFT)) { rotation.y += 1.0f; }
		}
		if (input.KeepPush(DIK_U) || input.KeepPush(DIK_I) || input.KeepPush(DIK_J) || input.KeepPush(DIK_K) || input.KeepPush(DIK_N) || input.KeepPush(DIK_M)) {
			if (input.KeepPush(DIK_U)) { scale.x += 0.1f; }
			else if (input.KeepPush(DIK_I)) { scale.x -= 0.1f; }
			if (input.KeepPush(DIK_J)) { scale.y += 0.1f; }
			else if (input.KeepPush(DIK_K)) { scale.y -= 0.1f; }
			if (input.KeepPush(DIK_N)) { scale.z += 0.1f; }
			else if (input.KeepPush(DIK_M)) { scale.z -= 0.1f; }
			if (scale.x < 0.1) { scale.x = 0.1f; }
			if (scale.y < 0.1) { scale.y = 0.1f; }
			if (scale.z < 0.1) { scale.z = 0.1f; }
		}
		matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

		MATRIX4.MakeScaling(scale.x, scale.y, scale.z);
		matScale = MATRIX4;

		matRot = MakeIdentity();
		MATRIX4 = MakeIdentity();
		MATRIX4.MakeRotation(ChangeRadians(rotation.x), ChangeRadians(rotation.y), ChangeRadians(rotation.z));
		matRot *= MATRIX4;

		MATRIX4 = MakeIdentity();
		MATRIX4.MakeTranslation(position.x, position.y, position.z);
		matTrans = MATRIX4;

		matWorld = MakeIdentity();//変形リセット
		matWorld *= matScale;//ワールド行列にスケーリング反映
		matWorld *= matRot;//ワールド行列に回転を反映
		matWorld *= matTrans;//ワールド行列に平行移動を反映

		MATRIX4 = MakeIdentity();

		//描画処理



		DirectX_.UpdateEnd(matWorld, matView, matProjection);

		DirectX_.DrawUpdate();
	}
	windowsApp.Break();

	return 0;
}