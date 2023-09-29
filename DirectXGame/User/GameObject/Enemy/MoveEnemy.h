#pragma once
#include"Enemy.h"
#include"HitEffect.h"

enum class ActionPhase
{
	//�ړ�
	MOVE,
	//�ҋ@
	WAIT,
	//����
	ESCAPE
};

class MoveEnemy :public Enemy
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
	std::unique_ptr<Sprite>lockOnSprite_;
	Transform lockOnTrans_;
	uint32_t lockOnTex_ = 0;

	float time_ = 0.0f;
	float addY = 0.0f;

	CollisionData collisionData_;

	MoveEnemyProperty moveEnemyProperty_;

	ActionPhase phase = ActionPhase::MOVE;
	uint16_t actionTimer = 0;
	myMath::Vector3 waitFinishPos = {};
	myMath::Vector3 waitFinishRot = {};

	std::unique_ptr<LockOnAnimation>lockOnAnimation_;

	std::unique_ptr<HitEffect>hitEffect_;

public:

	MoveEnemy() = default;
	~MoveEnemy();

	void Initialize();

	void Update();

	void PhaseUpdate();

	void PhaseMove(const myMath::Vector3& startPosition, const myMath::Vector3& endPosition, const myMath::Vector3& startRotation, const myMath::Vector3& endRotation,const float maxTime);

	void Draw();

	std::string GetName();

	const Transform& GetTransform();

	//�I�u�W�F�N�g�̓����蔻��擾����
	const CollisionData& GetCollisionData();

	//�I�u�W�F�N�g�̏Փ˔��菈��
	void OnCollision();

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

	const bool GetIsDead();

	bool GetSpawnFlag();

	const Transform& GetTrans();

private:

	void BulletUpdate();

	void SpawnUpdate();

	void DeathUpdate();
};