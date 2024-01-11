#include "Building.h"

void Building::Initialize()
{
	builing_ = std::make_unique<Model>();
	builing_->SetModel(sBuildingTex_);
	buildingTrans_.Initialize();

	collisionData_.center = { buildingTrans_.translation.x,buildingTrans_.translation.y - buildingSize_.y,buildingTrans_.translation.z };
}

void Building::Update()
{
	buildingTrans_.TransUpdate(sCamera_);
}

void Building::Draw()
{
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

void Building::SetColliderSize(const myMath::Vector3 size)
{
	collisionData_.scale = size;
}