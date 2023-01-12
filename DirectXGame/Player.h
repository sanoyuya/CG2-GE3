#pragma once
#include"myMath.h"
#include"DrawOversight.h"
#include"Transform.h"
#include"Camera.h"
#include"InputManager.h"
#include"DeathCube.h"
#include"AudioManager.h"

class Player
{
private:

	//クラス読み込み
	InputManager* input = nullptr;
	bool controllerFlag = false;

	std::unique_ptr<DrawOversight>model;
	Transform playerPos;

	std::unique_ptr<Sprite>attackRangeCircle;
	Transform attackRangeCircleTrans;

	std::unique_ptr<Sprite>directionTriangle;
	Transform directionTriangleTrans;

	std::array<std::unique_ptr<Sprite>, 3>hert;

	uint32_t minDiceTex = 0;
	uint32_t maxDiceTex = 0;
	uint32_t attackRangeTex = 0;
	uint32_t directionTex = 0;
	uint32_t hertTex = 0;

	bool jumpFlag = false;
	float gravity = 0.0f;
	uint16_t attackPower = 0;
	float radius = 0.0f;
	int hp = 0;
	bool damageFlag = false;
	float damageCoolTime = 0.0f;
	bool drawFlag = true;
	float angle = 0.0f;

	bool shakeFlag = false;
	const float shakePower = 0.5f;
	float shakeAdd = 0.0f;
	float shakeTimer = 0.0f;

	const float directionTriangleDistance = 3.0f;

	bool attackFlag = false;

	bool deathAnimationFlag = false;
	float deathAnimationCoolTime = 0.0f;
	bool deathFlag = false;

	std::list<std::unique_ptr<DeathCube>> deathCubes;
	bool generationFlag = false;

	AudioManager* audioManager = nullptr;
	uint32_t landing = 0;

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
	const bool& GetDamageFlag();
	const bool& GetDeathFlag();
	const bool& GetDeathAnimationFlag();

	//セッター
	void SetHp(const int hp);
	void SetDamageFlag(const bool damageFlag);

private:

	void Move();
	void Attack();
	void Rotation();
	void DeathAnimation(Camera* camera);

};