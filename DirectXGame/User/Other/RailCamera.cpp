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

	//レールの大元
	railTrans_.Initialize();

	//カメラの基準(中心)
	CameraCenter_.Initialize();
	CameraCenter_.parent = &railTrans_;//レールの子

	CameraFront_.Initialize();//カメラの基準の子
	CameraFront_.translation.z = 10.0f;
	CameraFront_.parent = &CameraCenter_;
	CameraBack_.Initialize();//カメラの基準の子
	CameraBack_.translation.z = -10.0f;
	CameraBack_.parent = &CameraCenter_;
	CameraLeft_.Initialize();//カメラの基準の子
	CameraLeft_.translation.x = 10.0f;
	CameraLeft_.parent = &CameraCenter_;
	CameraRight_.Initialize();//カメラの基準の子
	CameraRight_.translation.x = -10.0f;
	CameraRight_.parent = &CameraCenter_;
}

void RailCamera::Update()
{
	railTrans_.translation = myMath::CatmullRomSpline(controlPoints_, time_);

	//ここGameTimerで一括管理したい
	time_ += 0.00025f;
	if (time_ >= 1.0f)
	{
		time_ = 0.0f;
	}

	frontPos_ = myMath::CatmullRomSpline(controlPoints_, time_);

	//正面ベクトル
	frontVec_ = frontPos_ - railTrans_.translation;
	frontVec_.normalization();

	myMath::Vector3 baseVec = { 0.0f,0.0f,1.0f };

	myMath::Quaternion q(baseVec, frontVec_);
	
	//方向ベクトルの方向に向く
	//railTrans_.rotation = { q.GetEulerAngles().x,q.GetEulerAngles().y,0.0f };
	railTrans_.TransUpdate(camera_.get(),&q);

	switch (Player::GetCameraFlag())
	{
	case CameraFlag::Front:
		PhysicsMath::Complement(position_.x, CameraFront_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(position_.y, CameraFront_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(position_.z, CameraFront_.parentToTranslation.z, 20.0f);

		PhysicsMath::Complement(target_.x, CameraBack_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(target_.y, CameraBack_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(target_.z, CameraBack_.parentToTranslation.z, 20.0f);
		break;
	case CameraFlag::Back:
		PhysicsMath::Complement(position_.x, CameraBack_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(position_.y, CameraBack_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(position_.z, CameraBack_.parentToTranslation.z, 20.0f);

		PhysicsMath::Complement(target_.x, CameraFront_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(target_.y, CameraFront_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(target_.z, CameraFront_.parentToTranslation.z, 20.0f);
		break;
	case CameraFlag::Left:
		PhysicsMath::Complement(position_.x, CameraLeft_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(position_.y, CameraLeft_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(position_.z, CameraLeft_.parentToTranslation.z, 20.0f);

		PhysicsMath::Complement(target_.x, CameraRight_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(target_.y, CameraRight_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(target_.z, CameraRight_.parentToTranslation.z, 20.0f);
		break;
	case CameraFlag::Right:
		PhysicsMath::Complement(position_.x, CameraRight_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(position_.y, CameraRight_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(position_.z, CameraRight_.parentToTranslation.z, 20.0f);

		PhysicsMath::Complement(target_.x, CameraLeft_.parentToTranslation.x, 20.0f);
		PhysicsMath::Complement(target_.y, CameraLeft_.parentToTranslation.y, 20.0f);
		PhysicsMath::Complement(target_.z, CameraLeft_.parentToTranslation.z, 20.0f);
		break;
	default:
		break;
	}

	CameraCenter_.TransUpdate(GetCameraPtr());
	CameraFront_.TransUpdate(GetCameraPtr());
	CameraBack_.TransUpdate(GetCameraPtr());
	CameraLeft_.TransUpdate(GetCameraPtr());
	CameraRight_.TransUpdate(GetCameraPtr());

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

const Transform& RailCamera::GetRailTrans()
{
	return railTrans_;
}

void RailCamera::ImGuiUpdate()
{
	/*ImGui::Begin("CameraFlag");
	ImGui::Text("centerPos:%f,%f,%f", center_.parentToTranslation.x, center_.parentToTranslation.y, center_.parentToTranslation.z);
	ImGui::Text("frontPos:%f,%f,%f", front_.parentToTranslation.x, front_.parentToTranslation.y, front_.parentToTranslation.z);
	ImGui::Text("backPos:%f,%f,%f", back_.parentToTranslation.x, back_.parentToTranslation.y, back_.parentToTranslation.z);
	ImGui::Text("leftPos:%f,%f,%f", left_.parentToTranslation.x, left_.parentToTranslation.y, left_.parentToTranslation.z);
	ImGui::Text("rightPos:%f,%f,%f", CameraRight_.parentToTranslation.x, right_.parentToTranslation.y, right_.parentToTranslation.z);
	ImGui::Text("targetPos:%f,%f,%f", target_.x, target_.y, target_.z);
	ImGui::End();*/
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