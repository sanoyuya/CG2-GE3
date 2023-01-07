#include"MyGame.h"
#include"YFramework.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	YFramework* game = new MyGame();

	game->Run();

	delete game;

	return 0;
}