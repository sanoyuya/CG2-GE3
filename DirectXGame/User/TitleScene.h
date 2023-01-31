#pragma once
#include"BaseScene.h"
#include"InputManager.h"

//タイトルシーン
class TitleScene :public BaseScene
{
private:

	//クラス読み込み
	InputManager* input = nullptr;

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