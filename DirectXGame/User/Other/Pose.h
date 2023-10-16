#pragma once
#include"DrawOversight.h"

class Pose
{
private:

	bool poseFlag_ = false;

	std::unique_ptr<Sprite>poseSprite_;
	uint32_t poseTex_ = 0;

	std::unique_ptr<Sprite>poseBack_;
	uint32_t poseBackTex_ = 0;

public:

	void Initialize();

	void Update();

	void Draw();

	void SetPoseFlag(const bool flag);

	const bool GetPoseFlag();

	//シングルトン
	static Pose* GetInstance();

private:

	Pose() = default;
	~Pose() = default;

	//コピーコンストラクタ・代入演算子削除
	Pose& operator=(const Pose&) = delete;
	Pose(const Pose&) = delete;
};

