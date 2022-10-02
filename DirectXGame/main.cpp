#include<Windows.h>
#include "InputManager.h"
#include "DirectX_.h"
#include "WindowsApp.h"
#include"myMath.h"
#include"GameScene.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WindowsApp* windowsApp = WindowsApp::GetInstance();//WindowsApp�N���X�ǂݍ���
	windowsApp->CreatWindow();

	//DirectX���������� ��������

	DirectX_ directX_(windowsApp->GetHwnd(), windowsApp->GetW());//DirectX�N���X�ǂݍ���

	//�L�[�擾�J�n
	InputManager* input = InputManager::GetInstance();
	input->Initialize();

	//DirectX���������� �����܂�

	//�`�揉����������������

	directX_.DrawInitialize(windowsApp->GetHwnd(), windowsApp->GetW());

	//�`�揉�������������܂�

	GameScene* gameScene = GameScene::GetInstance();
	gameScene->Initialize();

	// �Q�[�����[�v
	while (true) {

		if (!windowsApp->MessageWindow()) {
			break;
		}

		input->Update();

		directX_.UpdateClear();

		//�X�V����
		gameScene->Update();

		//�`�揈��
		gameScene->Draw();

		directX_.UpdateEnd();
		directX_.DrawUpdate();
	}
	windowsApp->Break();

	return 0;
}