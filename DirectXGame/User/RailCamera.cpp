#include "RailCamera.h"
#include <algorithm>

void RailCamera::Initialize(const CameraData& cameraData)
{
	Load(cameraData);
	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	camera_->SetEye(position_);
}

void RailCamera::Update(Player* player)
{
	position_ = myMath::CatmullRomSpline(controlPoints_, time_);

	time_ += 0.00025f;
	if (time_ >= 1.0f)
	{
		time_ = 0.0f;
	}

	target_ = myMath::CatmullRomSpline(controlPoints_, time_);
	player = player;
	camera_->SetEye(position_);
	camera_->SetTarget(target_+ player->GetAddTargetPos());
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

const float RailCamera::GetTime()
{
	return time_;
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
	time_ = 0.0f;
}