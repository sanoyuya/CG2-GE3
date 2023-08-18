#pragma once
#include"BulletBase.h"
#include"DrawOversight.h"
#include"PlayerEngineSmokeParticleEmitter.h"

class LockOnBullet :public BulletBase
{
private:

	Camera* camera_ = nullptr;

	std::string name_ = "playerBullet";

	bool isDead_ = false;
	uint8_t deathTimer_ = 0;
	const uint8_t maxDeathTime_ = 60;

	myMath::Vector3 directionVector_;//�����x�N�g��
	const float speed_ = 1.5f;

	std::unique_ptr<Model>bullet_;
	uint32_t bulletTex_ = 0;
	Transform bulletTrans_;

	BulletOwner owner_ = BulletOwner::Player;

	std::unique_ptr<PlayerEngineSmokeParticleEmitter>smokeEmitter_;
	Transform smokeTrans_;

	CollisionData collisionData_;

	myMath::Vector3 startPos_ = {};
	myMath::Vector3 targetPos_ = {};
	myMath::Vector3 controlPos_ = {};

	float beziersTime_ = 0.0f;

public://BulletBase�ŕK�v�ȓz

	//�f�X�g���N�^
	~LockOnBullet();

	//����������
	void Initialize();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();

	//�I�u�W�F�N�g�̖��O�擾����
	std::string GetName();

	//�I�u�W�F�N�g�̓����蔻��擾����
	const CollisionData& GetCollisionData();

	//�I�u�W�F�N�g�̏Փ˔��菈��
	void OnCollision();

	//���S�t���O�̎擾
	const bool GetIsDead();

	//���S�A�j���[�V�����t���O�̎擾
	const bool GetDeathAnimationFlag();

	void SetCamera(Camera* camera);
	void SetPos(const myMath::Vector3& position);
	void SetDirectionVector(const myMath::Vector3& directionVector);
	void SetOwner(BulletOwner owner);
	void SetName(const std::string& name);
	void SetTargetPos(const myMath::Vector3& position);
	void SetControlPos(const myMath::Vector3& position);

private:

	void SmokeUpdate();

	void BulletMove();
};