#include "MyGame.h"
#include"SceneManager.h"

void MyGame::Initialize()
{
	YFramework::SetWindowData();

	//���N���X�̏���������
	YFramework::Initialize();

	//�V�[���}�l�[�W���[�ɍŏ��̃V�[�����Z�b�g
	SceneManager::GetInstance()->ChangeScene("TITLE");
}

void MyGame::Destroy()
{
	//���N���X�̏I������
	YFramework::Destroy();

	SceneManager::GetInstance()->Destroy();
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