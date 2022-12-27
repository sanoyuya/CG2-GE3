#pragma once
#include"myMath.h"
#include"DrawOversight.h"
#include"Transform.h"
#include"Camera.h"
#include"InputManager.h"

struct PlayerTexData
{
	uint32_t minDice;
	uint32_t maxDice;
	uint32_t direction;
};


class Player
{
private:

	//クラス読み込み
	InputManager* input = nullptr;

	std::unique_ptr<DrawOversight>model;
	Transform playerPos;
	static uint32_t minDiceTex;
	static uint32_t maxDiceTex;
	static uint32_t directionTex;

	bool jumpFlag = false;
	float gravity = 0.0f;
	uint8_t attackPower = 0;
	float radius = 0.0f;
	uint8_t hp = 0;

public:

	Player();
	~Player();

	static const void LoadTexture(PlayerTexData& texture);
	void Initialize();
	void Update(Camera* camera);
	void Movelimit();
	void Draw();

	//ゲッター
	const Transform& GetTransform();
	const float& GetRadius();
	const uint8_t& GetHp();
	const bool& GetJumpFlag();

	//セッター
	void SetHp(const uint8_t hp);

private:

	void Move();
	void Attack();

};