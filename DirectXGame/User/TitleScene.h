#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"DrawOversight.h"
#include"Camera.h"
#include"AudioManager.h"

//タイトルシーン
class TitleScene :public BaseScene
{
private:

	//クラス読み込み
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Camera>camera;
	myMath::Vector3 cameraPos;

	//天球
	std::unique_ptr<DrawOversight>skyDome;
	Transform skyDomeTrans;
	uint32_t skyDomeTex = 0;

	//3Dスプライト
	std::unique_ptr<Sprite>pokeSprite3D;
	Transform pokeSprite3DTrans;
	uint32_t pokeSprite3DTex = 0;
	myMath::Vector3 pokeSprite3DPos;
	uint16_t pokeNowNum = 0;
	uint8_t pokeTime = 0;

public:

	//初期化処理
	void Initialize()override;

	//終了処理
	void Destroy()override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;
};