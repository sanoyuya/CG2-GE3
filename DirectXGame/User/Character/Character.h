#pragma once
#include"Bullet.h"
#include"Camera.h"

class Character
{
protected:

	std::list<std::unique_ptr<Bullet>>bullets_;

public:

	void CreateBullet(myMath::Vector3 position, myMath::Vector3 frontVec,BulletOwner owner);
	void BulletUpdate(Camera* camera);
};