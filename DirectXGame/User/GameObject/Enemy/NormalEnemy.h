#pragma once
#include"Enemy.h"
#include"HitEffect.h"

class NormalEnemy:public Enemy
{
private:

	std::string name_ = "enemy";

	std::unique_ptr<Model>enemy_;
	uint32_t enemyTex_ = 0;
	Transform enemyTrans_;
	float spawnTime_ = 0.0f;
	float deathTime_ = 0.0f;

	bool spawnFlag_ = false;
	bool isDead_ = false;

	float bulletTimer = 0.0f;
	const float maxBulletTime = 60.0f;

	bool spawnAnimationFlag_ = false;
	uint8_t spawnAnimationTimer_ = 0;
	const uint8_t maxSpawnAnimationTime_ = 60;

	bool deathAnimationFlag_ = false;
	uint8_t deathAnimationTimer_ = 0;
	const uint8_t maxDeathAnimationTime_ = 60;

	std::unique_ptr<EnemyDeathParticleEmitter>emitter_;
	std::unique_ptr<EnemySpawnParticleEmitter>spawnEmitter_;

	bool lockOnFlag = false;

	CollisionData collisionData_;

	std::unique_ptr<LockOnAnimation>lockOnAnimation_;

	std::unique_ptr<HitEffect>hitEffect_;

public:

	NormalEnemy()=default;
	~NormalEnemy();

	void Initialize();

	void Update();

	void Draw();

	std::string GetName();

	const Transform& GetTransform();

	//�I�u�W�F�N�g�̓����蔻��擾����
	const CollisionData& GetCollisionData();

	//�I�u�W�F�N�g�̏Փ˔��菈��
	void OnCollision();

	const bool GetIsDead();

	//���S�A�j���[�V�����t���O�̎擾
	const bool GetDeathAnimationFlag();

	void LockOn();

	void CancelLockOn();

	const bool GetLockOnFlag();

public://�Z�b�^�[

	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ��ɏ������W���Z�b�g����֐�
	void SetPosition(const myMath::Vector3& position);
	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ��ɏ����p�x���Z�b�g����֐�
	void SetRotation(const myMath::Vector3& rotation);
	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ��ɓ����蔻��̑傫�����Z�b�g����֐�
	void SetColliderSize(const float size);
	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ��ɃX�|�[���^�C�}�[���Z�b�g����֐�
	void SetSpawnTimer(const float timer);
	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ��Ɏ��S�^�C�}�[���Z�b�g����֐�
	void SetDeathTimer(const float timer);

	void SetMoveEnemyProperty(const MoveEnemyProperty& moveEnemyProperty);

public://�Q�b�^�[

	bool GetSpawnFlag();

	const Transform& GetTrans();

private:

	void BulletUpdate();

	void SpawnUpdate();

	void DeathUpdate();
};