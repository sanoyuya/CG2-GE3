#pragma once
#include"YFramework.h"
#include"AbstractSceneFactory.h"
#include"PostEffect.h"
#include"MultiRenderPostEffect.h"
#include"MultiTexturePostEffect.h"

//ゲーム全体
class MyGame :public YFramework
{
private:

	//シーンファクトリー
	std::unique_ptr<AbstractSceneFactory>sceneFactory_;

	//ポストエフェクト
	std::unique_ptr<PostEffect>postEffect_;
	std::unique_ptr<MultiRenderPostEffect>multiRenderPostEffect_;
	std::unique_ptr<MultiTexturePostEffect>multiTexturePostEffect_;

public:

	//初期化処理
	void Initialize()override;

	//終了処理
	void Destroy()override;

	//更新処理
	void Update()override;

	//描画処理
	void SceneDraw()override;
	void PostEffectDraw()override;
};