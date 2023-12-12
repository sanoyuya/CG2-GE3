#pragma once
#include <cstdint>
#include"myMath.h"
#include"WindowsApp.h"

enum class Stage
{
	Tutorial,
	Stage1,
	Stage2,
	Stage3
};

/// <summary>
/// シーンを跨いでも保持したいものを保持するクラス
/// </summary>
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