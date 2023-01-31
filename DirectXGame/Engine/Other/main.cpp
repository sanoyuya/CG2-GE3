#include"MyGame.h"
#include"YFramework.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	std::unique_ptr<YFramework>game = std::make_unique<MyGame>();

	game->Run();

	return 0;
}