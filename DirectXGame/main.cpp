#include<Windows.h>
#include "InputManager.h"
#include "DirectX_.h"
#include "WindowsApp.h"
#include"FPS.h"
#include"myMath.h"
#include"GameScene.h"
#include <memory>
#include"TextureManager.h"
#include"Sprite2D.h"
#include "AudioManager.h"
#include"Model.h"

#pragma comment(lib, "d3dcompiler.lib")

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	WindowsApp* windowsApp = WindowsApp::GetInstance();//WindowsApp�N���X�ǂݍ���
	windowsApp->CreatWindow(L"DirectXGame");//�E�B���h�E�쐬

	std::unique_ptr<FPS>fps = std::make_unique<FPS>();
	fps->Initialize();

	//DirectX���������� ��������

	DirectX_* directX = DirectX_::GetInstance();//DirectX_�N���X�ǂݍ���
	directX->Initialize();

	//�L�[�擾�J�n
	InputManager* input = InputManager::GetInstance();
	input->Initialize();

	// �I�[�f�B�I�̏�����
	AudioManager* audioManager = AudioManager::GetInstance();
	audioManager->Initialize();

	//DirectX���������� �����܂�

	//�`�揉����������������

	TextureManager* textureManager = TextureManager::GetInstance();
	textureManager->StaticInitialize();

	Sprite2D::StaticInitialize();

	Model::StaticInitialize();

	//�`�揉�������������܂�

	std::unique_ptr<GameScene>gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();

	// �Q�[�����[�v
	while (true)
	{
		if (!windowsApp->MessageWindow())
		{
			break;
		}

		input->Update();
		audioManager->Update();

		directX->SetClearColor();//�w�i�F��ݒ� �����l(���F)
		directX->UpdateClear();

		//�X�V����
		gameScene->Update();

		//�`�揈��
		gameScene->Draw();

		directX->UpdateEnd();

		//FPS����
		fps->Update();
	}
	windowsApp->Break();
	directX->Destroy();
	textureManager->Destroy();
	audioManager->Destroy();

	return 0;
}