#pragma once
#include"BulletBase.h"
#include"DrawOversight.h"
#include"PlayerEngineSmokeParticleEmitter.h"
#include"EnemyDeathParticleEmitter.h"

class NormalBullet :public BulletBase
{
private:

	Camera* camera_ = nullptr;

	std::string name_ = "bullet";

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

	bool deathAnimationFlag_ = false;
	uint8_t animationTimer_ = 0;
	uint8_t maxAnimationTime_ = 60;

	std::unique_ptr<EnemyDeathParticleEmitter>deathParticleEmitter_;
	bool deathFlag_ = false;

public://BulletBase�ŕK�v�ȓz

	//�f�X�g���N�^
	~NormalBullet();

	//����������
	void Initialize();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();

	//�I�u�W�F�N�g�̖��O�擾����
	std::string GetName();

	const Transform& GetTransform();

	//�I�u�W�F�N�g�̓����蔻��擾����
	const CollisionData& GetCollisionData();

	//�I�u�W�F�N�g�̏Փ˔��菈��
	void OnCollision();

	void BulletDeathAnimation();

	const bool GetDeathFlag();

	//���S�t���O�̎擾
	const bool GetIsDead();

	//���S�A�j���[�V�����t���O�̎擾
	const bool GetDeathAnimationFlag();

	//���b�N�I��
	void LockOn();

	void CancelLockOn();

	const bool GetLockOnFlag();

	void SetCamera(Camera* camera);
	void SetPos(const myMath::Vector3& position);
	void SetDirectionVector(const myMath::Vector3& directionVector);
	void SetOwner(BulletOwner owner);
	void SetName(const std::string& name);
	void SetTargetPos(GameObject* lockOnEnemy);
	void SetControlPos(const myMath::Vector3& position);

private:

	void SmokeUpdate();
};