#include "YFramework.h"
#include "MyGame.h"

void YFramework::Initialize()
{
}

void YFramework::Destroy()
{
}

void YFramework::Update()
{
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