#pragma once
#include <cstdint>
#include"myMath.h"
#include"WindowsApp.h"

/// <summary>
/// シーンを跨いでも保持したいものを保持するクラス
/// </summary>
class Retention
{
private:

	uint16_t stageNum_ = 0;

public:

	void SetStageNum(const uint16_t stageNum);

	const uint16_t GetStageNum();

	//シングルトン
	static Retention* GetInstance();

private:

	Retention() = default;
	~Retention() = default;

	//コピーコンストラクタ・代入演算子削除
	Retention& operator=(const Retention&) = delete;
	Retention(const Retention&) = delete;
};