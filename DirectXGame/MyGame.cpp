#include "MyGame.h"

void MyGame::Initialize()
{
	windowsApp = WindowsApp::GetInstance();//WindowsApp�N���X�ǂݍ���
	windowsApp->CreatWindow(L"DirectXGame");//�E�B���h�E�쐬

	fps = std::make_unique<FPS>();
	fps->Initialize();

	//DirectX���������� ��������

	directX = DirectX_::GetInstance();//DirectX_�N���X�ǂݍ���
	directX->Initialize();

	//�L�[�擾�J�n
	input = InputManager::GetInstance();
	input->Initialize();

	// �I�[�f�B�I�̏�����
	audioManager = AudioManager::GetInstance();
	audioManager->Initialize();

	//DirectX���������� �����܂�

	//�`�揉����������������

	textureManager = TextureManager::GetInstance();
	textureManager->StaticInitialize();

	SpriteCommon::Initialize();
	Sprite2D::StaticInitialize();

	Model::StaticInitialize();

	//�`�揉�������������܂�

	gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();
}

void MyGame::Destroy()
{
	windowsApp->Break();
	directX->Destroy();
	textureManager->Destroy();
	audioManager->Destroy();
}

void MyGame::Update()
{
	input->Update();
	audioManager->Update();

	directX->SetClearColor();//�w�i�F��ݒ� �����l(���F)
	directX->UpdateClear();

	//�X�V����
	gameScene->Update();
}

void MyGame::Draw()
{
	gameScene->Draw();

	directX->UpdateEnd();

	//FPS����
	fps->Update();
}
