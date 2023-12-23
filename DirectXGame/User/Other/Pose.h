#pragma once
#include"DrawOversight.h"
#include"InputManager.h"

enum class PoseMode
{
	RESUME,
	RESTART,
	TITLE
};

class Pose
{
private:

	InputManager* input_ = nullptr;

	bool poseFlag_ = false;
	PoseMode poseMode_ = PoseMode::RESUME;
	int8_t poseModeNum_ = 0;

	std::unique_ptr<Sprite>poseSprite_;
	static uint32_t sPoseTex_;

	std::unique_ptr<Sprite>poseBack_;
	static uint32_t sPoseBackTex_;

	std::unique_ptr<Sprite>poseSelectFlameSprite_;
	static uint32_t sPoseSelectFlameSpriteTex_;

	std::array<std::unique_ptr<Sprite>,3>poseSelectSprite_;
	static std::array<uint32_t,3> sPoseSelectTex_;

	bool resetFlag_ = false;

	const uint8_t betweenTheLines = 200;

public:

	void Initialize();

	void Update();

	void Draw();

	const bool GetPoseFlag();

	const bool GetResetFlag();

	void SetResetFlag(const bool flag);

	static void LoadAsset();

private:

	void OpenPose();

	void PoseSelect();
};