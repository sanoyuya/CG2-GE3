#pragma once
#include"DrawOversight.h"

class Pose
{
private:

	bool poseFlag_ = false;

	std::unique_ptr<Sprite>poseSprite_;
	static uint32_t sPoseTex_;

	std::unique_ptr<Sprite>poseBack_;
	static uint32_t sPoseBackTex_;

public:

	void Initialize();

	void Draw();

	void SetPoseFlag(const bool flag);

	const bool GetPoseFlag();

	static void LoadAsset();
};