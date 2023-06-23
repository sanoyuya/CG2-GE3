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

	//DirectXBase�N���X�ǂݍ���
	DirectXBase::GetInstance()->Initialize(windowsApp_.get());

	//imGui�̏�����
	ImGuiManager::GetInstance()->Initialize(windowsApp_.get());

	//�L�[�擾�J�n
	InputManager::GetInstance()->Initialize(windowsApp_.get());

	// �I�[�f�B�I�̏�����
	AudioManager::GetInstance()->Initialize();

	//DirectX���������� �����܂�

	//�`�揉����������������

	Camera::StaticInitialize(windowsApp_.get());

	TextureManager::GetInstance()->StaticInitialize();

	SpriteCommon::StaticInitialize();
	Sprite2D::StaticInitialize(windowsApp_.get());

	Model::StaticInitialize();

	LightManager::StaticInitialize(DirectXBase::GetInstance()->GetDevice().Get());

	//�`�揉�������������܂�

	windowsApp_->Appearance();

	//�V�[���t�@�N�g���[�𐶐����A�}�l�[�W���ɃZ�b�g
	AbstractSceneFactory* sceneFactory = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory);

	postEffect_ = std::make_unique<PostEffect>();
	postEffect_->Initialize(windowsApp_.get());

	/*multiRenderPostEffect_= std::make_unique<MultiRenderPostEffect>();
	multiRenderPostEffect_->Initialize(windowsApp_.get());*/

	multiTexturePostEffect_ = std::make_unique<MultiTexturePostEffect>();
	multiTexturePostEffect_->Initialize(windowsApp_.get());
}

void YFramework::Destroy()
{
	ImGuiManager::GetInstance()->Destroy();
	Model::StaticDestory();
	DirectXBase::GetInstance()->Destroy();
	AudioManager::GetInstance()->Destroy();
}

void YFramework::Update()
{
	if (!windowsApp_->MessageWindow())
	{
		endRequest_ = true;
	}

	InputManager::GetInstance()->Update();
	AudioManager::GetInstance()->Update();

	DirectXBase::GetInstance()->SetClearColor();//�w�i�F��ݒ� �����l(���F)
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
		ImGuiManager::GetInstance()->Begin();

		Update();

		if (SceneManager::GetInstance()->GetSceneName() == "TITLE")
		{
			multiTexturePostEffect_->PreDrawScene(windowsApp_.get());
			Draw();
			multiTexturePostEffect_->PostDrawScene();
		}
		else if (SceneManager::GetInstance()->GetSceneName() == "GAME")
		{
			postEffect_->PreDrawScene(windowsApp_.get());
			Draw();
			postEffect_->PostDrawScene();
		}

		/*multiRenderPostEffect_->PreDrawScene(windowsApp_.get());
		Draw();
		multiRenderPostEffect_->PostDrawScene();*/

		ImGuiManager::GetInstance()->End();

		DirectXBase::GetInstance()->PreDraw(windowsApp_.get());

		if (GetEndRequest())
		{
			break;
		}

		//�`�揈��
		if (SceneManager::GetInstance()->GetSceneName() == "TITLE")
		{
			multiTexturePostEffect_->Draw();
		}
		else if (SceneManager::GetInstance()->GetSceneName() == "GAME")
		{
			postEffect_->Draw();
		}

#ifdef _DEBUG

		//ImGuiManager::GetInstance()->Draw();

#endif // DEBUG

		ImGuiManager::GetInstance()->Draw();

		DirectXBase::GetInstance()->PostDraw();

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