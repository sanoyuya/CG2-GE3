#pragma once
#include"myMath.h"
#include"DrawOversight.h"
#include"Transform.h"
#include"Camera.h"
#include"InputManager.h"

class Player
{
private:

	//クラス読み込み
	InputManager* input = nullptr;

	std::unique_ptr<DrawOversight>model;
	Transform playerPos;

	std::unique_ptr<Sprite>attackRangeCircle;
	Transform attackRangeCircleTrans;

	std::unique_ptr<Sprite>directionTriangle;
	Transform directionTriangleTrans;

	std::array<std::unique_ptr<Sprite>, 3>hert;
	std::array<Transform, 3>hertTrans;

	uint32_t minDiceTex;
	uint32_t maxDiceTex;
	uint32_t attackRangeTex;
	uint32_t directionTex;
	uint32_t hertTex;

	bool jumpFlag = false;
	float gravity = 0.0f;
	uint16_t attackPower = 0;
	float radius = 0.0f;
	int hp = 0;
	float angle = 0.0f;
	bool stickFlag = false;

	bool shakeFlag = false;
	const float shakePower = 0.5f;
	float shakeAdd = 0.0f;
	float shakeTimer = 0.0f;

	const float directionTriangleDistance = 3.0f;

	bool attackFlag = false;

public:

	Player();
	~Player();

	void Initialize();
	void Update(Camera* camera);
	void Movelimit();
	void Draw(Camera* camera);
	void AttackRangeDraw(Camera* camera);
	void Reset();

	//ゲッター
	const Transform& GetTransform();
	const float& GetRadius();
	const int& GetHp();
	const bool& GetJumpFlag();
	const float& GetShakeAdd();
	const bool& GetAttackFlag();

	//セッター
	void SetHp(const int hp);

private:

	void Move();
	void Attack();
	void Rotation();

};