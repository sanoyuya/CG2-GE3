#include "MyGame.h"
#include"SceneManager.h"

void MyGame::Initialize()
{
	YFramework::SetWindowData();

	//���N���X�̏���������
	YFramework::Initialize();

#ifdef _DEBUG

	//�V�[���}�l�[�W���[�ɍŏ��̃V�[�����Z�b�g
	SceneManager::GetInstance()->ChangeScene("TITLE");

#endif

#ifndef _DEBUG

	//�V�[���}�l�[�W���[�ɍŏ��̃V�[�����Z�b�g
	SceneManager::GetInstance()->ChangeScene("EngineOP");

#endif 
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

	//�V�[���}�l�[�W���[�̍X�V����
	SceneManager::GetInstance()->Update();
}

void MyGame::Draw()
{
	SceneManager::GetInstance()->Draw();
}