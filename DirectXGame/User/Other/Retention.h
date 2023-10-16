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

class Retention
{
private:

	myMath::Vector2 windowsSize_;
	myMath::Vector2 windowsCenter_;

	Stage stageNum_ = Stage::Tutorial;

public:

	void SetWindowData(WindowsApp* windowsApp);
	myMath::Vector2 GetWindowsSize();
	myMath::Vector2 GetWindowsCenter();
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