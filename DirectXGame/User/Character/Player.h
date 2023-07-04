#pragma once
#include"DrawOversight.h"
#include"Camera.h"
#include"InputManager.h"
#include"myMath.h"
#include"Bullet.h"

struct PlayerData
{
	myMath::Vector3 pos;
	myMath::Vector3 rotation;
	myMath::Vector3 scale;
};

class Player
{
private:

	InputManager* input_ = nullptr;

	std::unique_ptr<Model>player_;
	Transform playerTrans_;
	uint32_t playerTex_ = 0;

	Transform cameraTrans_;

	std::unique_ptr<Sprite>reticle_;
	Transform reticleTrans_;
	uint32_t reticleTex_ = 0;

	myMath::Vector3 directionVector_;//方向ベクトル(ローカル)
	myMath::Vector3 parentToDirectionVector_;//親子を反映させた方向ベクトル

	std::list<std::unique_ptr<Bullet>>bullets_;

	const float moveSpeed_ = 0.125f;
	const float reticleSpeed_ = 0.5f;
	const float moveLimit = 6.0f;

public:

	Player();
	~Player();

	void Initialize();

	void Update(Camera* camera);

	void Draw(Camera* camera);

private:

	void Reset();

	void Move();

	void Rotation();

	void ReticleMove();

	void MoveLimit();

	void ReticleLimit();

	void BulletUpdate(Camera* camera);

	void BulletDraw();
};