#include"MyGame.h"

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	MyGame game;

	//�Q�[���̏���������
	game.Initialize();

	// �Q�[�����[�v
	while (true)
	{
		//�X�V����
		game.Update();

		/*if (!windowsApp->MessageWindow())
		{
			break;
		}*/

		//�`�揈��
		game.Draw();
	}
	game.Destroy();

	return 0;
}