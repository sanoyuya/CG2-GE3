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

public:

	Player();
	~Player();

	void Initialize();

	void Update(Camera* camera);

	void Draw();

private:

	void Reset();
};