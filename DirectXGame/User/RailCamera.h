#pragma once
#include"Camera.h"
#include<memory>
#include"Player.h"

struct CameraData
{
	myMath::Vector3 position;

	//êßå‰ì_
	std::vector<myMath::Vector3> controlPoints;
};

class RailCamera
{
private:

	std::unique_ptr<Camera>camera_;

	myMath::Vector3 position_;
	myMath::Vector3 target_;
	myMath::Vector3 up_;

	//êßå‰ì_
	std::vector<myMath::Vector3> controlPoints_;
	float time_ = 0.0f;

public:

	void Initialize(const CameraData& cameraData);

	void Update(Player* player);

	void ReLoad(const CameraData& cameraData);

	Camera* GetCameraPtr();

	const float GetTime();

private:

	void Load(const CameraData& cameraData);
	void Reset();
};