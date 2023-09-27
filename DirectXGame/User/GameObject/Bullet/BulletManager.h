#pragma once
#include"NormalBullet.h"
#include"Camera.h"

class BulletManager
{
private:

	std::list<std::unique_ptr<BulletBase>>bullets_;

	uint32_t sound_ = 0;

public:

	void Initialize();

	void Update(Camera* camera);

	void Draw();

	void CreateNormalBullet(myMath::Vector3 position, myMath::Vector3 frontVec, BulletOwner owner);

	void CreateLockOnBullet(myMath::Vector3 startPos, GameObject* lockOnEnemy, myMath::Vector3 controlPos);

	void Reset();
};