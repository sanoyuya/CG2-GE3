#pragma once
#include <chrono>

class FPS
{
private:

	//�L�^����(FPS�Œ�p)
	std::chrono::steady_clock::time_point reference;

public:

	void Initialize();

	/// <summary>
	/// fps�Œ�̍X�V����
	/// </summary>
	/// <param name="fixedFps">fps�Œ�l</param>
	/// <param name="flag">���[�ȃ��j�^�[���ǂ���(���[�Ȃ�true)</param>
	void Update(float fixedFps = 60.0f, bool flag = true);

};