#include "DeathCube.h"

void DeathCube::Initialize(myMath::Vector3 position)
{
	cube = std::make_unique<DrawOversight>();
	cubeTex = Model::CreateObjModel("Resources/cube");
	cube->SetModel(cubeTex);
	cubeTrans.Initialize();
	cubeTrans.translation = position;
	frontVec = { static_cast<float>(myMath::GetRand(-1.0,1.0)),static_cast<float>(myMath::GetRand(-1.0,1.0)) ,static_cast<float>(myMath::GetRand(-1.0,1.0)) };
}

void DeathCube::Update(Camera* camera, myMath::Vector3 rotation)
{
	cubeTrans.translation += frontVec * speed;
	scale -= 1.0f / 100;
	cubeTrans.scale = { scale ,scale ,scale };
	cubeTrans.rotation = rotation;
	cubeTrans.TransUpdate(camera);

	if (cubeTrans.scale.x <= 0.0f || cubeTrans.scale.y <= 0.0f || cubeTrans.scale.z <= 0.0f)
	{
		isDead = true;
	}
}

void DeathCube::Draw(myMath::Vector4 color)
{
	cube->DrawModel(&cubeTrans, color);
}

bool DeathCube::GetIsDead()
{
	return isDead;
}