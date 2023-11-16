#include "Building.h"

Building::~Building()
{
}

void Building::Initialize()
{
	builing_ = std::make_unique<Model>();
	buildingTex_ = builing_->CreateObjModel("Resources/building2");
	builing_->SetModel(buildingTex_);
	buildingTrans_.Initialize();

	buildingBack_= std::make_unique<Model>();
	buildingBackTex_ = builing_->CreateObjModel("Resources/cube");
	buildingBack_->SetModel(buildingBackTex_);
	buildingBackTrans_.Initialize();
}

void Building::Update()
{
	buildingBackTrans_.translation = { buildingTrans_.translation.x,buildingTrans_.translation.y+20.0f,buildingTrans_.translation.z };
	buildingBackTrans_.scale = { buildingTrans_.scale.x * 10.0f-0.5f,buildingTrans_.scale.y * 20.0f - 0.5f,buildingTrans_.scale.z * 10.0f - 0.5f };
	buildingBackTrans_.rotation = buildingTrans_.rotation;

	buildingTrans_.TransUpdate(sCamera_);
	buildingBackTrans_.TransUpdate(sCamera_);
}

void Building::Draw()
{
	buildingBack_->DrawModel(&buildingBackTrans_, { 78.0f / 255.0f, 175.0f / 255.0f, 254.0f / 255.0f,1.0f });
	builing_->DrawModel(&buildingTrans_);
}

std::string Building::GetName()
{
	return name_;
}

const Transform& Building::GetTransform()
{
	return buildingTrans_;
}

const CollisionData& Building::GetCollisionData()
{
	return collisionData_;
}

void Building::OnCollision()
{
}

void Building::BulletDeathAnimation()
{
}

void Building::LockOn()
{
}

void Building::CancelLockOn()
{
}

void Building::SetPosition(const myMath::Vector3& position)
{
	buildingTrans_.translation = position;
}

void Building::SetRotation(const myMath::Vector3& rotation)
{
	buildingTrans_.rotation = rotation;
}

void Building::SetScale(const myMath::Vector3& scale)
{
	buildingTrans_.scale = scale;
}

void Building::SetColliderSize(const float size)
{
	collisionData_.radius = size;
}