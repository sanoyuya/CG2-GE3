#include "YFramework.h"
#include "MyGame.h"
#include"SceneFactory.h"
#include"SceneManager.h"
#include"imgui.h"

void YFramework::Initialize()
{
	windowsApp = WindowsApp::GetInstance();//WindowsApp�N���X�ǂݍ���
	windowsApp->CreatWindow(title.c_str(), window_width, window_height);//�E�B���h�E�쐬

	fps = std::make_unique<FPS>();
	fps->Initialize();

	//DirectX���������� ��������

	directX = DirectXBase::GetInstance();//DirectX_�N���X�ǂݍ���
	directX->Initialize();

	//imGui�̏�����
	imGuiManager = ImGuiManager::GetInstance();
	imGuiManager->Initialize();

	//�L�[�擾�J�n
	input = InputManager::GetInstance();
	input->Initialize();

	// �I�[�f�B�I�̏�����
	audioManager = AudioManager::GetInstance();
	audioManager->Initialize();

	//DirectX���������� �����܂�

	//�`�揉����������������

	TextureManager::GetInstance()->StaticInitialize();

	SpriteCommon::Initialize();
	Sprite2D::StaticInitialize();

	Model::StaticInitialize();

	//�`�揉�������������܂�

	//�V�[���t�@�N�g���[�𐶐����A�}�l�[�W���ɃZ�b�g
	AbstractSceneFactory* sceneFactory = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory);
}

void YFramework::Destroy()
{
	windowsApp->Break();
	imGuiManager->Destroy();
	directX->Destroy();
	textureManager->Destroy();
	audioManager->Destroy();
}

void YFramework::Update()
{
	if (!windowsApp->MessageWindow())
	{
		endRequest = true;
	}

	input->Update();
	audioManager->Update();

	directX->SetClearColor();//�w�i�F��ݒ� �����l(���F)
	directX->UpdateClear();
}

void YFramework::SetWindowData(const std::string& title_, const float width, const float height)
{
	wchar_t wtitle[256];

	MultiByteToWideChar(CP_ACP, 0, title_.c_str(), -1, wtitle, _countof(wtitle));

	title = wtitle;
	window_width = width;//����
	window_height = height;//�c��
}

void YFramework::Run()
{
	//����������
	Initialize();

	// �Q�[�����[�v
	while (true)
	{
		//�X�V����
		imGuiManager->Begin();

		Update();

		imGuiManager->End();

		if (GetEndRequest())
		{
			break;
		}

		//�`�揈��
		Draw();

#ifdef _DEBUG

		

#endif // DEBUG

		imGuiManager->Draw();//AL�̕]���ۑ�o���܂ł͂�����

		directX->UpdateEnd();

		//FPS����
		fps->Update();
	}
	Destroy();
}

void YFramework::Draw()
{
}

bool& YFramework::GetEndRequest()
{
	return endRequest;
}