#include "RailCamera.h"
#include <algorithm>
#include"Player.h"
#include"PhysicsMath.h"
#include<imgui.h>

void RailCamera::Initialize(const CameraData& cameraData)
{
	Load(cameraData);
	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	camera_->SetEye(position_);

	center_.Initialize();

	front_.Initialize();
	front_.translation.z = 10.0f;
	front_.parent = &center_;
	back_.Initialize();
	back_.translation.z = -10.0f;
	back_.parent = &center_;
	left_.Initialize();
	left_.translation.x = 10.0f;
	left_.parent = &center_;
	right_.Initialize();
	right_.translation.x = -10.0f;
	right_.parent = &center_;
}

void RailCamera::Update()
{
	center_.translation = myMath::CatmullRomSpline(controlPoints_, time_);

	time_ += 0.00025f;
	if (time_ >= 1.0f)
	{
		time_ = 0.0f;
	}

	frontPos_ = myMath::CatmullRomSpline(controlPoints_, time_);

	frontVec_ = frontPos_ - center_.translation;
	frontVec_.normalization();

	/*center_.rotation.x = -std::atan2(frontVec_.y, frontVec_.z);
	center_.rotation.y = -std::atan2(frontVec_.z, frontVec_.x) + myMath::AX_PIF / 2;*/

	switch (Player::GetCameraFlag())
	{
	case CameraFlag::Front:
		PhysicsMath::Complement(position_.x, front_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(position_.y, front_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(position_.z, front_.parentToTranslation.z, 20.0f);

		PhysicsMath::Complement(target_.x, back_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(target_.y, back_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(target_.z, back_.parentToTranslation.z, 20.0f);
		break;
	case CameraFlag::Back:
		PhysicsMath::Complement(position_.x, back_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(position_.y, back_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(position_.z, back_.parentToTranslation.z, 20.0f);

		PhysicsMath::Complement(target_.x, front_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(target_.y, front_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(target_.z, front_.parentToTranslation.z, 20.0f);
		break;
	case CameraFlag::Left:
		PhysicsMath::Complement(position_.x, left_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(position_.y, left_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(position_.z, left_.parentToTranslation.z, 20.0f);

		PhysicsMath::Complement(target_.x, right_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(target_.y, right_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(target_.z, right_.parentToTranslation.z, 20.0f);
		break;
	case CameraFlag::Right:
		PhysicsMath::Complement(position_.x, right_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(position_.y, right_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(position_.z, right_.parentToTranslation.z, 20.0f);

		PhysicsMath::Complement(target_.x, left_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(target_.y, left_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(target_.z, left_.parentToTranslation.z, 20.0f);
		break;
	default:
		break;
	}

	center_.TransUpdate(GetCameraPtr());
	front_.TransUpdate(GetCameraPtr());
	back_.TransUpdate(GetCameraPtr());
	left_.TransUpdate(GetCameraPtr());
	right_.TransUpdate(GetCameraPtr());

	camera_->SetEye(position_);
	camera_->SetTarget(target_+ Player::GetAddTargetPos());
	camera_->Update(true);

	ImGuiUpdate();
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

const Transform& RailCamera::GetCenterTrans()
{
	return center_;
}

void RailCamera::ImGuiUpdate()
{
	ImGui::Begin("CameraFlag");
	ImGui::Text("centerPos:%f,%f,%f", center_.parentToTranslation.x, center_.parentToTranslation.y, center_.parentToTranslation.z);
	ImGui::Text("frontPos:%f,%f,%f", front_.parentToTranslation.x, front_.parentToTranslation.y, front_.parentToTranslation.z);
	ImGui::Text("backPos:%f,%f,%f", back_.parentToTranslation.x, back_.parentToTranslation.y, back_.parentToTranslation.z);
	ImGui::Text("leftPos:%f,%f,%f", left_.parentToTranslation.x, left_.parentToTranslation.y, left_.parentToTranslation.z);
	ImGui::Text("rightPos:%f,%f,%f", right_.parentToTranslation.x, right_.parentToTranslation.y, right_.parentToTranslation.z);
	ImGui::Text("targetPos:%f,%f,%f", target_.x, target_.y, target_.z);
	ImGui::End();
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