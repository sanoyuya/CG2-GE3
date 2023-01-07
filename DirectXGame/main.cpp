#include"MyGame.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	MyGame game;

	//ゲームの初期化処理
	game.Initialize();

	// ゲームループ
	while (true)
	{
		//更新処理
		game.Update();

		/*if (!windowsApp->MessageWindow())
		{
			break;
		}*/

		//描画処理
		game.Draw();
	}
	game.Destroy();

	return 0;
}