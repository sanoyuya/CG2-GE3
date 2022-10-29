#include<Windows.h>
#include "InputManager.h"
#include "DirectX_.h"
#include "WindowsApp.h"
#include"FPS.h"
#include"myMath.h"
#include"GameScene.h"
#include <memory>
#include"TextureManager.h"
//#include"Sprite.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	WindowsApp* windowsApp = WindowsApp::GetInstance();//WindowsApp�N���X�ǂݍ���
	windowsApp->CreatWindow(L"DirectXGame");

	std::unique_ptr<FPS>fps;
	fps = std::make_unique<FPS>();
	fps->Initialize();

	//DirectX���������� ��������

	DirectX_* directX = DirectX_::GetInstance();//DirectX_�N���X�ǂݍ���
	directX->Initialize();

	//�L�[�擾�J�n
	InputManager* input = InputManager::GetInstance();
	input->Initialize();

	//DirectX���������� �����܂�

	//�`�揉����������������

	TextureManager* textureManager = TextureManager::GetInstance();
	textureManager->Initialize();

	//�`�揉�������������܂�

	GameScene* gameScene = GameScene::GetInstance();
	gameScene->Initialize();

	// �Q�[�����[�v
	while (true)
	{
		if (!windowsApp->MessageWindow())
		{
			break;
		}

		input->Update();

		directX->UpdateClear();
		/*sprite->SpriteCommonBigin();*/

		//�X�V����
		gameScene->Update();

		//�`�揈��
		gameScene->Draw();

		directX->UpdateEnd();

		fps->Update();
	}
	windowsApp->Break();

	return 0;
}