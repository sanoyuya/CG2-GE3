#include "Camera.h"
#include"WindowsApp.h"

void Camera::Initialize(bool projectionFlag)
{
	eye = { 0,0,-distance };//視点座標
	target = { 0,0,0 };//注視点座標
	up = { 0,1,0 };//上方向ベクトル
	aspect = static_cast<float>(WindowsApp::GetInstance()->GetWidth() / WindowsApp::GetInstance()->GetHeight());
	nearClip = 0.1f;
	farClip = 1000.0f;

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
	myMath::MakeLookL(eye, target, up, matView);
	matViewInverse = myMath::MakeInverse(matView);
}

void Camera::UpdateMatProjection(bool projectionFlag)
{
	if (projectionFlag == false)
	{
		//平行投影
		myMath::MakeOrthogonalL(0.0f, (float)WindowsApp::GetInstance()->GetWidth(), (float)WindowsApp::GetInstance()->GetHeight(),0.0f , nearClip, farClip, matProjection);
	}
	else
	{
		//透視投影
		myMath::MakePerspectiveL(myMath::ChangeRadians(60.0f), aspect, nearClip, farClip, matProjection);
	}
}

const myMath::Matrix4& Camera::GetMatView()
{
	return matView;
}

const myMath::Matrix4& Camera::GetMatViewInverse()
{
	return matViewInverse;
}

const myMath::Matrix4& Camera::GetMatProjection()
{
	return matProjection;
}

const myMath::Vector3& Camera::GetEye()
{
	return eye;
}

const myMath::Vector3& Camera::GetTarget()
{
	return target;
}

const myMath::Vector3& Camera::GetUp()
{
	return up;
}

void Camera::SetEye(const myMath::Vector3& eye_)
{
	eye = eye_;
}

void Camera::SetTarget(const myMath::Vector3& target_)
{
	target = target_;
}

void Camera::SetUp(const myMath::Vector3& up_)
{
	up = up_;
}

void Camera::SetNearClip(const float& nearClip_)
{
	nearClip = nearClip_;
}

void Camera::SetFarClip(const float& farClip_)
{
	farClip = farClip_;
}