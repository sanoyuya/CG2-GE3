#include "EnemyDeathParticleEmitter.h"

void EnemyDeathParticleEmitter::Initialize()
{
	// �p�[�e�B�N������
	particleMan_ = std::make_unique<ParticleManager>();
	tex_ = particleMan_->LoadTexture("Resources/particle.png");
	particleMan_->Initialize(tex_);
}

void EnemyDeathParticleEmitter::Create(const myMath::Vector3 center)
{
	for (int i = 0; i < 60; i++)
	{
		//�������W(��������ꏊ�̒��S���W)
		myMath::Vector3 pos{};
		pos.x = center.x;
		pos.y = center.y;
		pos.z = center.z;

		//���x
		myMath::Vector3 vel = { static_cast<float>(myMath::GetRand(-1.0f,1.0f)),static_cast<float>(myMath::GetRand(-1.0f,1.0f)) ,static_cast<float>(myMath::GetRand(-1.0f,1.0f)) };

		//�d�͂̂悤�ȏ���
		myMath::Vector3 acc{};
		const float gravity = 0.0245f;
		acc.y -= gravity;

		myMath::Vector4 col = { 1.0f,1.0f,1.0f,1.0f };

		//�ǉ�
		particleMan_->Add(60.0f, pos, vel, acc, 3.0f, 0.0f, col);
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