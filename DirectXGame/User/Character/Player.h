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

public:

	Player();
	~Player();

	void Initialize(const PlayerData& playerData);

	void Update(Camera* camera);

	void Draw();

	void ReLoad(const PlayerData& playerData);

private:

	void Load(const PlayerData& playerData);
	void Reset();
};