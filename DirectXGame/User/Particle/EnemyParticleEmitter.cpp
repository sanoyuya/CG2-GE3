#include "EnemyParticleEmitter.h"

void EnemyParticleEmitter::Initialize()
{
	// �p�[�e�B�N������
	particleMan_ = std::make_unique<ParticleManager>();
	tex_ = particleMan_->LoadTexture("Resources/particle.png");
	particleMan_->Initialize(tex_);
}

void EnemyParticleEmitter::Create(const myMath::Vector3 center)
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

		//�d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_���ɕ��z
		myMath::Vector3 acc{};
		float yadd = 0.0245f;
		acc.y -= yadd;

		myMath::Vector4 col = { 1.0f,1.0f,1.0f,1.0f };

		//�ǉ�
		particleMan_->Add(60.0f, pos, vel, acc, 3.0f, 0.0f, col);
	}
}

void EnemyParticleEmitter::Update(Camera* camera)
{
	particleMan_->Update(camera);
}

void EnemyParticleEmitter::Draw()
{
	particleMan_->Draw();
}