#include "FPS.h"

void FPS::Initialize()
{
	reference_ = std::chrono::steady_clock::now();//���݂̎��Ԃ���
}

void FPS::Update(float fixedFps, bool flag)
{
	//1/fixedFps�b�҂�����
	std::chrono::microseconds minTime(uint64_t(1000000.0f / fixedFps));
	//1/fixedFps�b���킸���ɒZ������
	std::chrono::microseconds minCheckTime(uint64_t(1000000.0f / (fixedFps + 5.0f)));

	//���ݎ��Ԃ��擾
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	//�O��L�^����̌o�ߎ��Ԃ��擾����
	std::chrono::microseconds elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - reference_);

	if (flag == false)
	{
		//1/fixedFps�b(���킸���ɒZ������)�o���Ă��Ȃ��ꍇ
		if (elapsed < minTime)
		{
			//1/fixedFps�b�o�߂���܂Ŕ����ȃX���[�v���J��Ԃ�
			while (std::chrono::steady_clock::now() - reference_ < minTime)
			{
				//1�}�C�N���b�X���[�v
				std::this_thread::sleep_for(std::chrono::microseconds(1));
			}
		}
	}
	else
	{
		//1/fixedFps�b(���킸���ɒZ������)�o���Ă��Ȃ��ꍇ
		if (elapsed < minCheckTime)
		{
			//1/fixedFps�b�o�߂���܂Ŕ����ȃX���[�v���J��Ԃ�
			while (std::chrono::steady_clock::now() - reference_ < minCheckTime)
			{
				//1�}�C�N���b�X���[�v
				std::this_thread::sleep_for(std::chrono::microseconds(1));
			}
		}
	}
	
	//���݂̎��Ԃ��L�^����
	reference_ = std::chrono::steady_clock::now();
}