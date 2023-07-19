#include "GameObject.h"
#include"ColliderManager.h"

GameObject::GameObject(std::string objectName, myMath::Vector3 center, float radius)
{
	objectName_ = objectName;
	collision_.center = { center.x,center.y,center.z,1.0f };
	collision_.radius = radius;

	ColliderManager::GetInstance()->AddCollision(this);
}