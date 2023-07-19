#pragma once
#include"Collision.h"
#include <string>

class GameObject
{
public:

	std::string objectName_ = {};
	Sphere collision_;

	GameObject(std::string objectName, myMath::Vector3 center,float radius);
};

