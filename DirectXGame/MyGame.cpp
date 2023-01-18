#include "MyGame.h"
#include"SceneFactory.h"

bool MyGame::endRequest;

void MyGame::Initialize()
{
	//���N���X�̏���������
	YFramework::Initialize();
	sceneManager = SceneManager::GetInstance();

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

	//�V�[���t�@�N�g���[�𐶐����A�}�l�[�W���ɃZ�b�g
	AbstractSceneFactory* sceneFactory = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory);

	//�V�[���}�l�[�W���[�ɍŏ��̃V�[�����Z�b�g
	SceneManager::GetInstance()->ChangeScene("TITLE");
}

void MyGame::Destroy()
{
	windowsApp->Break();
	directX->Destroy();
	textureManager->Destroy();
	audioManager->Destroy();

	//���N���X�̏I������
	YFramework::Destroy();
}

void MyGame::Update()
{
	//���N���X�̍X�V����
	YFramework::Update();

	if (!windowsApp->MessageWindow())
	{
		endRequest = true;
	}

	input->Update();
	audioManager->Update();

	directX->SetClearColor();//�w�i�F��ݒ� �����l(���F)
	directX->UpdateClear();

	//�X�V����
	//gameScene->Update();
}

void MyGame::Draw()
{
	sceneManager->Draw();
	//gameScene->Draw();

	directX->UpdateEnd();

	//FPS����
	fps->Update();
}

const bool& MyGame::GetEndRequest()
{
	return endRequest;
}