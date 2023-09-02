#pragma once
#include"DrawOversight.h"
#include<list>
#include"Player.h"
#include"EnemyDeathParticleEmitter.h"
#include"GameTimer.h"
#include"Transform.h"
#include"LockOnAnimation.h"

struct MoveEnemyProperty
{
	myMath::Vector3 spawnPos;
	myMath::Vector3 spawnPosRotation;
	float toMovePosTime;
	myMath::Vector3 movePos;
	myMath::Vector3 movePosRotation;
	float waitTime;
	float toEscapePosTime;
	myMath::Vector3 escapePos;
	myMath::Vector3 escapePosRotation;
};

class Enemy :public GameObject
{
protected:

	Camera* camera_ = nullptr;
	Player* player_ = nullptr;
	GameTimer* gameTimer_ = nullptr;
	BulletManager* bulletManager_ = nullptr;

public:

	virtual ~Enemy() = default;

	//����������
	virtual void Initialize() = 0;

	//�X�V����
	virtual void Update() = 0;

	//�`�揈��
	virtual void Draw() = 0;

	//�I�u�W�F�N�g�̖��O�擾����
	virtual std::string GetName() = 0;

	//�I�u�W�F�N�g�̓����蔻��擾����
	virtual const CollisionData& GetCollisionData() = 0;

	//�I�u�W�F�N�g�̏Փ˔��菈��
	virtual void OnCollision() = 0;

	//���S�t���O�̎擾
	virtual const bool GetIsDead() = 0;

	//���S�A�j���[�V�����t���O�̎擾
	virtual const bool GetDeathAnimationFlag() = 0;

	virtual void LockOn() = 0;

	virtual void CancelLockOn() = 0;

	virtual const bool GetLockOnFlag() = 0;

	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ��ɏ������W���Z�b�g����֐�
	virtual void SetPosition(const myMath::Vector3& position) = 0;
	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ��ɏ����p�x���Z�b�g����֐�
	virtual void SetRotation(const myMath::Vector3& rotation) = 0;
	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ��ɓ����蔻��̑傫�����Z�b�g����֐�
	virtual void SetColliderSize(const float size) = 0;
	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ��ɃX�|�[���^�C�}�[���Z�b�g����֐�
	virtual void SetSpawnTimer(const float timer) = 0;
	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ��Ɏ��S�^�C�}�[���Z�b�g����֐�
	virtual void SetDeathTimer(const float timer) = 0;
	//blender�ŏo�͂����f�[�^��ǂݍ��ނƂ���MoveEnemy�̏����Z�b�g����֐�
	virtual void SetMoveEnemyProperty(const MoveEnemyProperty& moveEnemyProperty) = 0;

	void SetCamera(Camera* camera);

	void SetPlayer(Player* player);

	void SetGameTimer(GameTimer* gameTimer);

	void SetBulletManager(BulletManager* bulletManager);

	virtual bool GetSpawnFlag() = 0;

	virtual const Transform& GetTrans() = 0;
};