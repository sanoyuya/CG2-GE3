#include"MyGame.h"
#include"YFramework.h"

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	YFramework* game = new MyGame();

	game->Run();

	delete game;

	return 0;
}