#pragma once
#include"GameObject.h"
#include"Camera.h"

enum class BulletOwner
{
	Player,
	Enemy
};

class BulletBase :public GameObject
{
public://GameObject�ŕK�v�ȓz

	//�f�X�g���N�^
	virtual ~BulletBase() = default;

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

	//���b�N�I��
	virtual void LockOn() = 0;

	virtual const bool GetLockOnFlag() = 0;

public://Bullet�ŕK�v�ȓz
	virtual void SetCamera(Camera* camera) = 0;
	virtual void SetPos(const myMath::Vector3& position) = 0;
	virtual void SetDirectionVector(const myMath::Vector3& directionVector) = 0;
	virtual void SetOwner(BulletOwner owner) = 0;
	virtual void SetName(const std::string& name) = 0;
	virtual void SetTargetPos(const myMath::Vector3& position) = 0;
	virtual void SetControlPos(const myMath::Vector3& position) = 0;
};