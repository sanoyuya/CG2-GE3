#include "EnemyDeathParticleEmitter.h"

void EnemyDeathParticleEmitter::Initialize()
{
	// �p�[�e�B�N������
	particleMan_ = std::make_unique<ParticleManager>();
	tex_ = particleMan_->LoadTexture("Resources/particle2.png");
	particleMan_->Initialize(tex_);
}

void EnemyDeathParticleEmitter::Create(const myMath::Vector3 center)
{
	//���F
	for (int i = 0; i < 5; i++)
	{
		//�������W(��������ꏊ�̒��S���W)
		myMath::Vector3 pos{};
		pos.x = center.x;
		pos.y = center.y;
		pos.z = center.z;

		//���x
		myMath::Vector3 vel = { static_cast<float>(myMath::GetRand(-0.05f,0.05f)),static_cast<float>(myMath::GetRand(-0.05f,0.05f)) ,static_cast<float>(myMath::GetRand(-0.05f,0.05f)) };

		//�d�͂̂悤�ȏ���
		myMath::Vector3 acc{};

		myMath::Vector4 col = { 0.0f,0.0f,0.0f,1.0f };

		//�ǉ�
		particleMan_->Add(60.0f, pos, vel, acc, 3.0f, 10.0f, col);
	}

	//�D�F
	for (int i = 0; i < 5; i++)
	{
		//�������W(��������ꏊ�̒��S���W)
		myMath::Vector3 pos{};
		pos.x = center.x;
		pos.y = center.y;
		pos.z = center.z;

		//���x
		myMath::Vector3 vel = { static_cast<float>(myMath::GetRand(-0.1f,0.1f)),static_cast<float>(myMath::GetRand(-0.1f,0.1f)) ,static_cast<float>(myMath::GetRand(-0.1f,0.1f)) };

		//�d�͂̂悤�ȏ���
		myMath::Vector3 acc{};

		myMath::Vector4 col = { 108.0f / 255.0f,103.0f / 255.0f ,110.0f / 255.0f,1.0f };

		//�ǉ�
		particleMan_->Add(60.0f, pos, vel, acc, 3.0f, 10.0f, col);
	}

	//�I�����W�F
	for (int i = 0; i < 5; i++)
	{
		//�������W(��������ꏊ�̒��S���W)
		myMath::Vector3 pos{};
		pos.x = center.x;
		pos.y = center.y;
		pos.z = center.z;

		//���x
		myMath::Vector3 vel = { static_cast<float>(myMath::GetRand(-0.01f,0.01f)),static_cast<float>(myMath::GetRand(-0.01f,0.01f)) ,static_cast<float>(myMath::GetRand(-0.01f,0.01f)) };

		//�d�͂̂悤�ȏ���
		myMath::Vector3 acc{};

		myMath::Vector4 col = { 245.0f / 255.0f,130.0f / 255.0f,32.0f / 255.0f,1.0f };

		//�ǉ�
		particleMan_->Add(60.0f, pos, vel, acc, 3.0f, 10.0f, col);
	}
}

void EnemyDeathParticleEmitter::Update(Camera* camera)
{
	particleMan_->Update(camera);
}

void EnemyDeathParticleEmitter::Draw()
{
	particleMan_->Draw();
}