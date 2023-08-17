#pragma once

struct CollisionData
{
	myMath::Vector3 center = {};
	float radius = 0.0f;
};

//�I�u�W�F�N�g���N���X
class GameObject
{
public:

	//�f�X�g���N�^
	virtual ~GameObject() = default;

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
};