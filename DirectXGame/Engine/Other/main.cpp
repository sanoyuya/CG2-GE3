#include"MyGame.h"
#include"YFramework.h"

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	std::unique_ptr<YFramework>game = std::make_unique<MyGame>();

	game->Run();

	return 0;
}