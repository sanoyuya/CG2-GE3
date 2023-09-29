#include "EnemySpawnParticleEmitter.h"

void EnemySpawnParticleEmitter::Initialize()
{
	// �p�[�e�B�N������
	particleMan_ = std::make_unique<ParticleManager>();
	tex_ = particleMan_->LoadTexture("Resources/particle.png");
	particleMan_->Initialize(tex_);
}

void EnemySpawnParticleEmitter::Create(const myMath::Vector3 center)
{
	for (int i = 0; i < 5; i++)
	{
		//�������W(��������ꏊ�̒��S���W)
		myMath::Vector3 pos{};
		pos.x = center.x;
		pos.y = center.y - 3.0f;
		pos.z = center.z;

		//���x
		myMath::Vector3 vel = { -0.02f,0.2f ,0.0f };

		//�d�͂̂悤�ȏ���
		myMath::Vector3 acc{};

		myMath::Vector4 col = { 115.0f / 255.0f,78.0f / 255.0f,149.0f / 255.0f,1.0f };

		//�ǉ�
		particleMan_->Add(30.0f, pos, vel, acc, 3.0f, 0.0f, col);
	}

	for (int i = 0; i < 5; i++)
	{
		//�������W(��������ꏊ�̒��S���W)
		myMath::Vector3 pos{};
		pos.x = center.x;
		pos.y = center.y - 3.0f;
		pos.z = center.z;

		//���x
		myMath::Vector3 vel = { -0.02f,0.2f ,0.0f };

		//�d�͂̂悤�ȏ���
		myMath::Vector3 acc{};

		myMath::Vector4 col = { 0.0f / 255.0f,0.0f / 255.0f,0.0f / 255.0f,1.0f };

		//�ǉ�
		particleMan_->Add(30.0f, pos, vel, acc, 3.0f, 0.0f, col);
	}
}

void EnemySpawnParticleEmitter::Update(Camera* camera)
{
	particleMan_->RandomXMoveUpdate(camera,-0.1f, 0.1f);
}

void EnemySpawnParticleEmitter::Draw()
{
	particleMan_->Draw();
}