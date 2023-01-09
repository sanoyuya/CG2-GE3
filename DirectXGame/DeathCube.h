#pragma once
#include"myMath.h"
#include"DrawOversight.h"
#include"Transform.h"
#include"Camera.h"

class DeathCube
{
private:

	std::unique_ptr<DrawOversight>cube;
	Transform cubeTrans;
	uint32_t cubeTex = 0;

	myMath::Vector3 frontVec = { 0.0f,0.0f ,0.0f };
	const float speed = 1.0f;
	float scale = 1.0f;

	bool isDead = false;

public:

	void Initialize(myMath::Vector3 position);
	void Update(Camera* camera, myMath::Vector3 rotation);
	void Draw(myMath::Vector4 color);
	bool GetIsDead();

};