#include"MyGame.h"
#include"YFramework.h"

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	std::unique_ptr<YFramework>game = std::make_unique<MyGame>();

	game->Run();

	return 0;
}