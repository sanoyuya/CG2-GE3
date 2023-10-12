#pragma once
#include"Camera.h"
#include<memory>
#include"Transform.h"

enum class CameraFlag
{
	Back,
	Left,
	Front,
	Right,
};

struct CameraData
{
	myMath::Vector3 position;

	//制御点
	std::vector<myMath::Vector3> controlPoints;
};

class RailCamera
{
private:

	std::unique_ptr<Camera>camera_;

	myMath::Vector3 position_;
	myMath::Vector3 target_;
	myMath::Vector3 up_;

	CameraFlag flag_ = CameraFlag::Back;

	Transform center_;
	Transform front_;
	Transform back_;
	Transform right_;
	Transform left_;

	myMath::Vector3 frontVec_ = {};
	myMath::Vector3 frontPos_ = {};

	//制御点
	std::vector<myMath::Vector3> controlPoints_;
	float time_ = 0.0f;

public:

	void Initialize(const CameraData& cameraData);

	void Update();

	void ReLoad(const CameraData& cameraData);

	Camera* GetCameraPtr();

	const float GetTime();

	const Transform& GetCenterTrans();

private:

	void ImGuiUpdate();
	void Load(const CameraData& cameraData);
	void Reset();
};