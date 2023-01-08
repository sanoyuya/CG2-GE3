#pragma once
#include"DrawOversight.h"
#include"Transform.h"
#include"Camera.h"

class BackDice
{
private:

	std::unique_ptr<Sprite>backDice;
	Transform backDiceTrans;
	static uint32_t backDiceTex;

	float angle = 0.0f;
	bool isDead = false;
	float speed = 0.0f;
	float rotSpeed = 0.0f;
	uint16_t diceNum = 0;

public:

	static const void LoadTexture(uint32_t& texture);

	void Initialize(const myMath::Vector3 position, const uint16_t num);
	void Update(Camera* camera);
	void Draw(Camera* camera, myMath::Vector4 color);

	bool GetIsDead();
};