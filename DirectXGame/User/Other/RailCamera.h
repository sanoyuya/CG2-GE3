#pragma once
#include"Camera.h"
#include<memory>
#include"Transform.h"
#include"GameTimer.h"

struct ControlPoint
{
	std::string name;
	myMath::Vector3 position;
};

enum class CameraFlag
{
	Back,
	Left,
	Front,
	Right,
};

struct CameraData
{
	myMath::Vector3 position;

	//制御点
	std::vector<ControlPoint> controlPoints;
};

class RailCamera
{
private:

	//制御点
	std::vector<myMath::Vector3> controlPoints_;

	std::unique_ptr<Camera>camera_;
	std::unique_ptr<Camera>camera2_;
	Transform cameraTrans_;

	myMath::Vector3 position_;
	myMath::Vector3 target_;
	myMath::Vector3 up_;

	Transform railTrans_;
	myMath::Quaternion q_;

	CameraFlag flag_ = CameraFlag::Back;
	Transform cameraCenter_;
	Transform cameraFront_;
	Transform cameraBack_;
	Transform cameraRight_;
	Transform cameraLeft_;

	myMath::Vector3 frontVec_ = {};
	myMath::Vector3 frontPos_ = {};

public:

	void Initialize(const CameraData& cameraData);

	void BeginUpdate(GameTimer* gameTimer);

	void Update(GameTimer* gameTimer);

	void ReLoad(const CameraData& cameraData);

	Camera* GetCameraPtr();

	const Transform& GetRailTrans();

	myMath::Quaternion& GetQuaternion();

	void ImGuiUpdate();

private:

	void Load(const CameraData& cameraData);
	void Reset();
};