#include "Camera.h"

float Camera::sWidth_;
float Camera::sHeight;

void Camera::StaticInitialize(WindowsApp* windowsApp)
{
	sWidth_ = windowsApp->GetWidth();
	sHeight = windowsApp->GetHeight();
}

void Camera::Initialize(bool projectionFlag)
{
	eye_ = { 0,0,-distance_ };//視点座標
	target_ = { 0,0,0 };//注視点座標
	up_ = { 0,1,0 };//上方向ベクトル
	aspect_ = sWidth_ / sHeight;
	nearClip_ = 0.1f;
	farClip_ = 1000.0f;

	UpdateMatView();
	UpdateMatProjection(projectionFlag);
}

void Camera::Update(bool projectionFlag)
{
	UpdateMatView();
	UpdateMatProjection(projectionFlag);
}

void Camera::UpdateMatView()
{
	myMath::MakeLookL(eye_, target_, up_, matView_);
	matViewInverse_ = myMath::MakeInverse(matView_);
}

void Camera::UpdateMatProjection(bool projectionFlag)
{
	if (projectionFlag == false)
	{
		//平行投影
		myMath::MakeOrthogonalL(0.0f, sWidth_, sHeight,0.0f , nearClip_, farClip_, matProjection_);
	}
	else
	{
		//透視投影
		myMath::MakePerspectiveL(myMath::ChangeRadians(60.0f), aspect_, nearClip_, farClip_, matProjection_);
	}
}

const myMath::Matrix4& Camera::GetMatView()
{
	return matView_;
}

const myMath::Matrix4& Camera::GetMatViewInverse()
{
	return matViewInverse_;
}

const myMath::Matrix4& Camera::GetMatProjection()
{
	return matProjection_;
}

const myMath::Vector3& Camera::GetEye()
{
	return eye_;
}

const myMath::Vector3& Camera::GetTarget()
{
	return target_;
}

const myMath::Vector3& Camera::GetUp()
{
	return up_;
}

void Camera::SetEye(const myMath::Vector3& eye)
{
	eye_ = eye;
}

void Camera::SetTarget(const myMath::Vector3& target)
{
	target_ = target;
}

void Camera::SetUp(const myMath::Vector3& up)
{
	up_ = up;
}

void Camera::SetNearClip(const float& nearClip)
{
	nearClip_ = nearClip;
}

void Camera::SetFarClip(const float& farClip)
{
	farClip_ = farClip;
}