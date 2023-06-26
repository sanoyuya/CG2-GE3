#include "MyGame.h"
#include"SceneManager.h"

void MyGame::Initialize()
{
	YFramework::SetWindowData();
	YFramework::SetWindowColor();

	//基底クラスの初期化処理
	YFramework::Initialize();

	postEffect_ = std::make_unique<PostEffect>();
	postEffect_->Initialize(windowsApp_.get());

	multiRenderPostEffect_= std::make_unique<MultiRenderPostEffect>();
	multiRenderPostEffect_->Initialize(windowsApp_.get());

	multiTexturePostEffect_ = std::make_unique<MultiTexturePostEffect>();
	multiTexturePostEffect_->Initialize(windowsApp_.get());

#ifdef _DEBUG

	//シーンマネージャーに最初のシーンをセット
	SceneManager::GetInstance()->ChangeScene("TITLE");

#endif

#ifndef _DEBUG

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

	//シーンマネージャーの更新処理
	SceneManager::GetInstance()->Update();
}

void MyGame::SceneDraw()
{
	if (SceneManager::GetInstance()->GetSceneName() == "TITLE")
	{
		multiTexturePostEffect_->PreDrawScene(windowsApp_.get());
		SceneManager::GetInstance()->Draw();
		multiTexturePostEffect_->PostDrawScene();
	}
	else if (SceneManager::GetInstance()->GetSceneName() == "GAME")
	{
		postEffect_->PreDrawScene(windowsApp_.get());
		SceneManager::GetInstance()->Draw();
		postEffect_->PostDrawScene();
	}

	/*multiRenderPostEffect_->PreDrawScene(windowsApp_.get());
	SceneManager::GetInstance()->Draw();
	multiRenderPostEffect_->PostDrawScene();*/
}

void MyGame::PostEffectDraw()
{
	if (SceneManager::GetInstance()->GetSceneName() == "TITLE")
	{
		multiTexturePostEffect_->Draw();
	}
	else if (SceneManager::GetInstance()->GetSceneName() == "GAME")
	{
		postEffect_->Draw();
	}

	//multiRenderPostEffect_->Draw();
}