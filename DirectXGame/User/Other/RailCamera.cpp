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

	camera2_ = std::make_unique<Camera>();
	camera2_->Initialize(true);
	camera2_->SetEye(position_);

	//レールの大元
	railTrans_.Initialize();
	cameraTrans_.Initialize();
	railTrans_.parent = &cameraTrans_;

	//カメラの基準(中心)
	cameraCenter_.Initialize();
	cameraCenter_.parent = &railTrans_;//レールの子

	cameraFront_.Initialize();//カメラの基準の子
	cameraFront_.translation.z = 10.0f;
	cameraFront_.parent = &cameraCenter_;
	cameraBack_.Initialize();//カメラの基準の子
	cameraBack_.translation.z = -10.0f;
	cameraBack_.parent = &cameraCenter_;
	cameraLeft_.Initialize();//カメラの基準の子
	cameraLeft_.translation.x = 10.0f;
	cameraLeft_.parent = &cameraCenter_;
	cameraRight_.Initialize();//カメラの基準の子
	cameraRight_.translation.x = -10.0f;
	cameraRight_.parent = &cameraCenter_;
}

void RailCamera::BeginUpdate(GameTimer* gameTimer)
{
	camera2_->SetEye(myMath::CatmullRomSpline(controlPoints_, gameTimer->GetFlameCount() / gameTimer->GetGameTime()));
}

void RailCamera::Update(GameTimer* gameTimer)
{
	frontPos_ = myMath::CatmullRomSpline(controlPoints_, gameTimer->GetFlameCount() / gameTimer->GetGameTime());
	//敵の弾を動き続けている自機に当てるために、20f先の予測地点を算出しておく
	predictionPoint_ = myMath::CatmullRomSpline(controlPoints_, (gameTimer->GetFlameCount() + 20.0f) / gameTimer->GetGameTime());

	camera2_->SetTarget(frontPos_);
	camera2_->Update(true);
	cameraTrans_.matWorld = camera2_->GetMatView();
	railTrans_.parent = &cameraTrans_;

	//正面ベクトル
	frontVec_ = frontPos_ - railTrans_.translation;
	frontVec_.normalization();

	railTrans_.TransUpdate(GetCameraPtr());
	cameraCenter_.TransUpdate(GetCameraPtr());
	cameraCenter_.rotation = { Reticle::GetAddTargetAngle().y,Reticle::GetAddTargetAngle().x,0.0f };
	cameraFront_.TransUpdate(GetCameraPtr());
	cameraBack_.TransUpdate(GetCameraPtr());
	cameraLeft_.TransUpdate(GetCameraPtr());
	cameraRight_.TransUpdate(GetCameraPtr());

	switch (Player::GetCameraFlag())
	{
	case CameraFlag::Front:
		PhysicsMath::Complement(position_.x, cameraFront_.parentToTranslation.x, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(position_.y, cameraFront_.parentToTranslation.y, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(position_.z, cameraFront_.parentToTranslation.z, 20.0f / gameTimer->GetTimeSpeed());

		PhysicsMath::Complement(target_.x, cameraBack_.parentToTranslation.x, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(target_.y, cameraBack_.parentToTranslation.y, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(target_.z, cameraBack_.parentToTranslation.z, 20.0f / gameTimer->GetTimeSpeed());
		break;
	case CameraFlag::Back:
		PhysicsMath::Complement(position_.x, cameraBack_.parentToTranslation.x, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(position_.y, cameraBack_.parentToTranslation.y, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(position_.z, cameraBack_.parentToTranslation.z, 20.0f / gameTimer->GetTimeSpeed());

		PhysicsMath::Complement(target_.x, cameraFront_.parentToTranslation.x, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(target_.y, cameraFront_.parentToTranslation.y, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(target_.z, cameraFront_.parentToTranslation.z, 20.0f / gameTimer->GetTimeSpeed());
		break;
	case CameraFlag::Left:
		PhysicsMath::Complement(position_.x, cameraLeft_.parentToTranslation.x, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(position_.y, cameraLeft_.parentToTranslation.y, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(position_.z, cameraLeft_.parentToTranslation.z, 20.0f / gameTimer->GetTimeSpeed());

		PhysicsMath::Complement(target_.x, cameraRight_.parentToTranslation.x, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(target_.y, cameraRight_.parentToTranslation.y, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(target_.z, cameraRight_.parentToTranslation.z, 20.0f / gameTimer->GetTimeSpeed());
		break;
	case CameraFlag::Right:
		PhysicsMath::Complement(position_.x, cameraRight_.parentToTranslation.x, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(position_.y, cameraRight_.parentToTranslation.y, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(position_.z, cameraRight_.parentToTranslation.z, 20.0f / gameTimer->GetTimeSpeed());

		PhysicsMath::Complement(target_.x, cameraLeft_.parentToTranslation.x, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(target_.y, cameraLeft_.parentToTranslation.y, 20.0f / gameTimer->GetTimeSpeed());
		PhysicsMath::Complement(target_.z, cameraLeft_.parentToTranslation.z, 20.0f / gameTimer->GetTimeSpeed());
		break;
	default:
		break;
	}

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

const Transform& RailCamera::GetRailTrans()
{
	return cameraTrans_;
}

const myMath::Quaternion& RailCamera::GetQuaternion()
{
	return q_;
}

const myMath::Vector3& RailCamera::GetPredictionPoint()
{
	return predictionPoint_;
}

void RailCamera::ImGuiUpdate()
{
	ImGui::Begin("RailCamera");
	ImGui::Text("centerPos:%f,%f,%f", cameraCenter_.parentToTranslation.x, cameraCenter_.parentToTranslation.y, cameraCenter_.parentToTranslation.z);
	ImGui::Text("frontPos:%f,%f,%f", cameraFront_.parentToTranslation.x, cameraFront_.parentToTranslation.y, cameraFront_.parentToTranslation.z);
	ImGui::Text("backPos:%f,%f,%f", cameraBack_.parentToTranslation.x, cameraBack_.parentToTranslation.y, cameraBack_.parentToTranslation.z);
	ImGui::Text("leftPos:%f,%f,%f", cameraLeft_.parentToTranslation.x, cameraLeft_.parentToTranslation.y, cameraLeft_.parentToTranslation.z);
	ImGui::Text("rightPos:%f,%f,%f", cameraRight_.parentToTranslation.x, cameraRight_.parentToTranslation.y, cameraRight_.parentToTranslation.z);
	ImGui::Text("targetPos:%f,%f,%f", target_.x, target_.y, target_.z);
	ImGui::End();
}

void RailCamera::Load(const CameraData& cameraData)
{
	for (auto it = cameraData.controlPoints.begin(); it != cameraData.controlPoints.end(); ++it)
	{
		controlPoints_.push_back(it->position);
	}
}

void RailCamera::Reset()
{
	controlPoints_.clear();
}