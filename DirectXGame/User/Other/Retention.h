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

	//シングルトン
	static Retention* GetInstance();

private:

	Retention() = default;
	~Retention() = default;

	//コピーコンストラクタ・代入演算子削除
	Retention& operator=(const Retention&) = delete;
	Retention(const Retention&) = delete;
};