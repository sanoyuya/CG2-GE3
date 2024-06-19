#include"MyGame.h"
#include"YFramework.h"
#define _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING

//Windowsアプリでのエントリーポイント(main関数)
int32_t WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int32_t)
{
	std::unique_ptr<YFramework>game = std::make_unique<MyGame>();

	game->Run();

	return 0;
}