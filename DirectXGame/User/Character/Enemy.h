#pragma once
#include"DrawOversight.h"
#include<list>
#include"Player.h"
#include"EnemyDeathParticleEmitter.h"

class Enemy :public Character
{
private:

	std::unique_ptr<Model>enemy_;
	uint32_t enemyTex_ = 0;
	Transform enemyTrans_;
	float colliderSize_ = 0.0f;
	bool isDead_ = false;

	float bulletTimer = 0.0f;
	const float maxBulletTime = 60.0f;

	bool deathAnimationFlag_ = false;
	uint8_t deathAnimationTimer_ = 0;
	const uint8_t maxDeathAnimationTime_ = 60;

	std::unique_ptr<EnemyDeathParticleEmitter>emitter_;

public:

	Enemy();
	~Enemy();

	void Initialize();

	void Update(Camera* camera, Player*player);

	void Draw();

public://�Z�b�^�[

	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ��ɏ������W���Z�b�g����֐�
	void SetPosition(const myMath::Vector3& position);
	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ��ɏ����p�x���Z�b�g����֐�
	void SetRotation(const myMath::Vector3& rotation);
	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ��ɓ����蔻��̑傫�����Z�b�g����֐�
	void SetColliderSize(const float size);

public://�Q�b�^�[

	const myMath::Vector3& GetPosition();

	const float& GetColliderSize();

	bool GetIsDead();

	bool GetDeathAnimationFlag();

	void OnCollision();

private:

	void BulletUpdate(Camera* camera, Player* player);

	void BulletDraw();
};