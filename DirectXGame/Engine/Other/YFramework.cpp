#include "YFramework.h"
#include "MyGame.h"
#include"SceneFactory.h"
#include"SceneManager.h"
#include"imgui.h"
#include"LightManager.h"

void YFramework::Initialize()
{
	windowsApp_ = std::make_unique<WindowsApp>();//WindowsApp�N���X�ǂݍ���
	windowsApp_->CreatWindow(title_.c_str(), windowWidth_, windowHeight_);//�E�B���h�E�쐬

	fps_ = std::make_unique<FPS>();
	fps_->Initialize();

	//DirectX���������� ��������

	directX_ = DirectXBase::GetInstance();//DirectX_�N���X�ǂݍ���
	directX_->Initialize(windowsApp_.get());

	//imGui�̏�����
	imGuiManager_ = ImGuiManager::GetInstance();
	imGuiManager_->Initialize(windowsApp_.get());

	//�L�[�擾�J�n
	input_ = InputManager::GetInstance();
	input_->Initialize(windowsApp_.get());

	// �I�[�f�B�I�̏�����
	audioManager_ = AudioManager::GetInstance();
	audioManager_->Initialize();

	//DirectX���������� �����܂�

	//�`�揉����������������

	Camera::StaticInitialize(windowsApp_.get());

	TextureManager::GetInstance()->StaticInitialize();

	SpriteCommon::Initialize();
	Sprite2D::StaticInitialize(windowsApp_.get());

	Model::StaticInitialize();

	LightManager::StaticInitialize(DirectXBase::GetInstance()->GetDevice().Get());

	//�`�揉�������������܂�

	windowsApp_->Appearance();

	//�V�[���t�@�N�g���[�𐶐����A�}�l�[�W���ɃZ�b�g
	AbstractSceneFactory* sceneFactory = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory);

	postEffect_ = std::make_unique<PostEffect>();
	postEffect_->Initialize();
}

void YFramework::Destroy()
{
	imGuiManager_->Destroy();
	directX_->Destroy();
	audioManager_->Destroy();
}

void YFramework::Update()
{
	if (!windowsApp_->MessageWindow())
	{
		endRequest_ = true;
	}

	input_->Update();
	audioManager_->Update();

	directX_->SetClearColor();//�w�i�F��ݒ� �����l(���F)
	directX_->UpdateClear(windowsApp_.get());
}

void YFramework::SetWindowData(const std::string& title, const float width, const float height)
{
	wchar_t wtitle[256];

	MultiByteToWideChar(CP_ACP, 0, title.c_str(), -1, wtitle, _countof(wtitle));

	title_ = wtitle;
	windowWidth_ = width;//����
	windowHeight_ = height;//�c��
}

void YFramework::SetWindowColor(const myMath::Vector4& color)
{
	DirectXBase::GetInstance()->SetClearColor(color);
}

void YFramework::Run()
{
	//����������
	Initialize();

	// �Q�[�����[�v
	while (true)
	{
		//�X�V����
		imGuiManager_->Begin();

		Update();

		imGuiManager_->End();

		if (GetEndRequest())
		{
			break;
		}

		//�`�揈��
		Draw();
		postEffect_->Draw();

#ifdef _DEBUG

		

#endif // DEBUG

		imGuiManager_->Draw();//AL�̕]���ۑ�o���܂ł͂�����

		directX_->UpdateEnd();

		//FPS����
		fps_->Update();
	}
	Destroy();
}

void YFramework::Draw()
{
}

bool& YFramework::GetEndRequest()
{
	return endRequest_;
}