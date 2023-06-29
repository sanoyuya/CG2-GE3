#pragma once
#include"Camera.h"
#include<memory>

struct CameraData
{
	myMath::Vector3 position;
};

class RailCamera
{
private:

	std::unique_ptr<Camera>camera_;

	myMath::Vector3 position_;
	myMath::Vector3 target_;
	myMath::Vector3 up_;

public:

	void Initialize(const CameraData& cameraData);

	void Update();

	void ReLoad(const CameraData& cameraData);

	Camera* GetCameraPtr();

private:

	void Load(const CameraData& cameraData);
	void Reset();
};