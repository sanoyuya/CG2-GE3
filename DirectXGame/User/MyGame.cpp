#include "MyGame.h"
#include"SceneManager.h"

void MyGame::Initialize()
{
	YFramework::SetWindowData();

	//基底クラスの初期化処理
	YFramework::Initialize();

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

void MyGame::Draw()
{
	SceneManager::GetInstance()->Draw();
}