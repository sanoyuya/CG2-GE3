#include "TripleBullet.h"

TripleBullet::~TripleBullet()
{
}

void TripleBullet::Initialize()
{
}

void TripleBullet::Update()
{
}

void TripleBullet::Draw()
{
}

std::string TripleBullet::GetName()
{
	return name_;
}

const CollisionData& TripleBullet::GetCollisionData()
{
	
}

const bool TripleBullet::GetIsDead()
{
	return false;
}

void TripleBullet::SetPos(const myMath::Vector3& position)
{
}

void TripleBullet::SetDirectionVector(const myMath::Vector3& directionVector)
{
}

void TripleBullet::SetOwner(BulletOwner owner)
{
}

void TripleBullet::SetName(const std::string& name)
{
}
