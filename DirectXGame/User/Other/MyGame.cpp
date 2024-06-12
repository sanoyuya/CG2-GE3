#include "MyGame.h"
#include"SceneManager.h"
#include"GameHeader.h"

void MyGame::Initialize()
{
#ifdef _DEBUG
	YFramework::SetWindowData("YamoEngine(Debug)");
#else
	YFramework::SetWindowData("YamoEngine");
#endif
	YFramework::SetWindowColor();

	//基底クラスの初期化処理
	YFramework::Initialize();

	GameHeader::SetApp(windowsApp_.get());

	//ポストエフェクトの初期化
	postEffect_ = std::make_unique<MultiTexturePostEffect>();
	postEffect_->Initialize(windowsApp_.get());

	LoadAsset();

#ifdef _DEBUG
	//シーンマネージャーに最初のシーンをセット
	SceneManager::GetInstance()->ChangeScene("DEMO");
#else
	//シーンマネージャーに最初のシーンをセット
	SceneManager::GetInstance()->ChangeScene("DEMO");
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

	//シーンマネージャーの更新処理
	SceneManager::GetInstance()->Update();

	GameHeader::ImGuiUpdate();
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

void MyGame::LoadAsset()
{
	
}