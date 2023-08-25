#pragma once
#include"DrawOversight.h"
#include"Camera.h"
#include"InputManager.h"
#include"GameObject.h"

class Reticle:public GameObject
{
private:

	InputManager* input_ = nullptr;
	Camera* camera_ = nullptr;

	std::unique_ptr<Sprite>reticle_;
	Transform reticleTrans_;
	uint32_t reticleTex_ = 0;

	const float reticleSpeed_ = 1.5f;
	const float reticleLimit_ = 45.0f;

	Transform cameraTrans_;

	std::string name_ = "reticle";
	CollisionData collisionData;

public:

	Reticle() = default;
	~Reticle() = default;

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

	//���b�N�I���t���O�̎擾
	const bool GetLockOnFlag();

	void LockOn();

	void CancelLockOn();

	void Reset();

	const float GetReticleLimit();

	const Transform& GetTransform();

	void SetCamera(Camera* camera);

private:

	void Move();

	void ReticleLimit();
};