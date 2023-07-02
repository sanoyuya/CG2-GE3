#include "RailCamera.h"
#include <algorithm>

void RailCamera::Initialize(const CameraData& cameraData)
{
	Load(cameraData);
	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	camera_->SetEye(position_);
}

void RailCamera::Update()
{
	position_ = myMath::CatmullRomSpline(controlPoints_, time);

	time += 0.0005f;
	if (time >= 1.0f)
	{
		time = 0.0f;
	}

	target_ = myMath::CatmullRomSpline(controlPoints_, time);

	camera_->SetEye(position_);
	camera_->SetTarget(target_);
	camera_->Update(true);
}

void RailCamera::ReLoad(const CameraData& cameraData)
{
	Reset();
	Load(cameraData);
}

Camera* RailCamera::GetCameraPtr()
{
	return camera_.get();
}

void RailCamera::Load(const CameraData& cameraData)
{
	position_ = cameraData.position;

	controlPoints_ = cameraData.controlPoints;
	myMath::Vector3 startPoint = controlPoints_.front();
	controlPoints_.push_back(startPoint);
}

void RailCamera::Reset()
{
	controlPoints_.clear();
	time = 0.0f;
}