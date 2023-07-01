#pragma once
#include"DrawOversight.h"
#include"Camera.h"
#include"InputManager.h"
#include"myMath.h"

struct PlayerData
{
	myMath::Vector3 pos;
	myMath::Vector3 rotation;
	myMath::Vector3 scale;
};

class Player
{
private:

	std::unique_ptr<Model>player_;
	Transform playerTrans_;
	uint32_t playerTex_ = 0;

	Transform cameraTrans_;

	std::unique_ptr<Sprite>reticle_;
	Transform reticleTrans_;
	uint32_t reticleTex_ = 0;

public:

	Player();
	~Player();

	void Initialize();

	void Update(Camera* camera);

	void Draw(Camera* camera);

private:

	void Reset();
};