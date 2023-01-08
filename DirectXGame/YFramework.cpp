#include "YFramework.h"
#include "MyGame.h"

void YFramework::Initialize()
{
	sceneManager = SceneManager::GetInstance();
}

void YFramework::Destroy()
{
	sceneManager->Destroy();
}

void YFramework::Update()
{
	//�V�[���}�l�[�W���[�̍X�V����
	sceneManager->Update();
}

void YFramework::Run()
{
	//����������
	Initialize();

	// �Q�[�����[�v
	while (true)
	{
		//�X�V����
		Update();

		if (MyGame::GetEndRequest())
		{
			break;
		}

		//�`�揈��
		Draw();
	}
	Destroy();
}