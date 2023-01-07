#include "YFramework.h"
#include "MyGame.h"

void YFramework::Initialize()
{
}

void YFramework::Destroy()
{
}

void YFramework::Update()
{
}

void YFramework::Run()
{
	//初期化処理
	Initialize();

	// ゲームループ
	while (true)
	{
		//更新処理
		Update();

		if (MyGame::GetEndRequest())
		{
			break;
		}

		//描画処理
		Draw();
	}
	Destroy();
}