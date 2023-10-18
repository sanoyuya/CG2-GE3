#include "MyGame.h"
#include"SceneManager.h"
#include"SceneChangeAnimation.h"
#include"Enemy.h"
#include"HitEffect.h"
#include"Pose.h"
#include"Retention.h"

void MyGame::Initialize()
{
	YFramework::SetWindowData("AirBattle");
	YFramework::SetWindowColor();

	//基底クラスの初期化処理
	YFramework::Initialize();

	//ポストエフェクトの初期化
	postEffect_ = std::make_unique<MultiTexturePostEffect>();
	postEffect_->Initialize(windowsApp_.get());

	Retention::GetInstance()->SetWindowData(windowsApp_.get());

	SceneChangeAnimation::GetInstance()->StaticInitialize();

	Enemy::StaticInitialize();

	HitEffect::StaticInitialize();

	Pose::GetInstance()->Initialize();

#ifdef _DEBUG
	//シーンマネージャーに最初のシーンをセット
	SceneManager::GetInstance()->ChangeScene("TITLE");
#else
	//シーンマネージャーに最初のシーンをセット
	SceneManager::GetInstance()->ChangeScene("EngineOP");
#endif
}

void MyGame::Destroy()
{
	SceneManager::GetInstance()->Destroy();

	//基底クラスの終了処理
	YFramework::Destroy();
}

void MyGame::Update()
{
	//基底クラスの更新処理
	YFramework::Update();

	//シーンチェンジアニメーションの更新処理
	SceneChangeAnimation::GetInstance()->Update();

	//シーンマネージャーの更新処理
	SceneManager::GetInstance()->Update();
}

void MyGame::SceneDraw()
{
	postEffect_->PreDrawScene(windowsApp_.get());
	SceneManager::GetInstance()->Draw();
	postEffect_->PostDrawScene();
}

void MyGame::PostEffectDraw()
{
	postEffect_->Draw();
}