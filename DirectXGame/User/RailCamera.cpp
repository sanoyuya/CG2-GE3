#include "RailCamera.h"

void RailCamera::Initialize(const CameraData& cameraData)
{
	Load(cameraData);
	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	camera_->SetEye(position_);
}

void RailCamera::Update()
{
	camera_->Update(true);
	camera_->SetEye(position_);
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
}

void RailCamera::Reset()
{
}