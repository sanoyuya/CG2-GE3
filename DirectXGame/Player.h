#pragma once
#include"myMath.h"
#include"DrawOversight.h"
#include"Transform.h"
#include"Camera.h"
#include"InputManager.h"

class Player
{
private:

	//ÉNÉâÉXì«Ç›çûÇ›
	InputManager* input = nullptr;

	std::unique_ptr<DrawOversight>model;
	Transform playerPos;
	uint32_t minDiceTex;
	uint32_t maxDiceTex;

	bool jumpFlag = false;
	float gravity = 0.0f;
	uint8_t attackPower = 0;

public:

	Player();
	~Player();

	void Initialize();
	void Update(Camera* camera);
	void Draw(Camera* camera);

private:

	void Move();
	void Attack();

};