#include "MyGame.h"
#include"SceneManager.h"
#include"SceneChangeAnimation.h"
#include"Enemy.h"

void MyGame::Initialize()
{
	YFramework::SetWindowData("AirBattle");
	YFramework::SetWindowColor();

	//���N���X�̏���������
	YFramework::Initialize();

	//�|�X�g�G�t�F�N�g�̏�����
	postEffect_ = std::make_unique<PostEffect>();
	postEffect_->Initialize(windowsApp_.get());

	SceneChangeAnimation::GetInstance()->StaticInitialize();

	Enemy::StaticInitialize();

	//�V�[���}�l�[�W���[�ɍŏ��̃V�[�����Z�b�g
	SceneManager::GetInstance()->ChangeScene("EngineOP");
}

void MyGame::Destroy()
{
	SceneManager::GetInstance()->Destroy();

	//���N���X�̏I������
	YFramework::Destroy();
}

void MyGame::Update()
{
	//���N���X�̍X�V����
	YFramework::Update();

	//�V�[���`�F���W�A�j���[�V�����̍X�V����
	SceneChangeAnimation::GetInstance()->Update();

	//�V�[���}�l�[�W���[�̍X�V����
	SceneManager::GetInstance()->Update();
}

void MyGame::SceneDraw()
{
	postEffect_->PreDrawScene(windowsApp_.get());
	SceneManager::GetInstance()->Draw();
	postEffect_->PostDrawScene();
}

void MyGame::PostEffectDraw()
{
	postEffect_->Draw();
}