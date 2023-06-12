#pragma once
#include"YFramework.h"
#include"AbstractSceneFactory.h"

//ゲーム全体
class MyGame :public YFramework
{
private:

	//シーンファクトリー
	std::unique_ptr<AbstractSceneFactory>sceneFactory_;

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