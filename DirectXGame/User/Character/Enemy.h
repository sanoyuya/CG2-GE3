#pragma once
#include"DrawOversight.h"
#include<list>
#include"Player.h"
#include"EnemyDeathParticleEmitter.h"
#include"GameTimer.h"

class Enemy :public GameObject
{
protected:

	Camera* camera_ = nullptr;
	Player* player_ = nullptr;
	GameTimer* gameTimer_ = nullptr;

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

	virtual bool GetIsDead() = 0;

public:

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

	void SetCamera(Camera* camera);

	void SetPlayer(Player* player);

	void SetGameTimer(GameTimer* gameTimer);

	virtual const Transform& GetTrans() = 0;

	virtual const float& GetColliderSize() = 0;

	virtual bool GetSpawnFlag() = 0;

	virtual bool GetDeathAnimationFlag() = 0;

	virtual void OnCollision() = 0;
};