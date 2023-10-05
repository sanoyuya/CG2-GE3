#pragma once
#include <cstdint>

enum class Stage
{
	Tutorial,
	Stage1,
	Stage2,
	Stage3
};

class Retention
{
private:

	Stage stageNum_ = Stage::Tutorial;

public:

	void SetStageNum(const Stage stageNum);

	const Stage GetStageNum();

	//�V���O���g��
	static Retention* GetInstance();

private:

	Retention() = default;
	~Retention() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Retention& operator=(const Retention&) = delete;
	Retention(const Retention&) = delete;
};