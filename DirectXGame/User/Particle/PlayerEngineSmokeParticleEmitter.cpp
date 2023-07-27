#include "PlayerEngineSmokeParticleEmitter.h"

void PlayerEngineSmokeParticleEmitter::Initialize()
{
	// �p�[�e�B�N������
	particleMan_ = std::make_unique<ParticleManager>();
	tex_ = particleMan_->LoadTexture("Resources/particle.png");
	particleMan_->Initialize(tex_);
}

void PlayerEngineSmokeParticleEmitter::Create(const myMath::Vector3 center)
{
	for (int i = 0; i < 5; i++)
	{
		const float lifeTime = 15.0f;
		//�������W(��������ꏊ�̒��S���W)
		myMath::Vector3 pos{};
		//���S�_���甼�a1m�̉~�̒��Ƀ����_���ɐݒ�
		pos.x = center.x + static_cast<float>(myMath::GetRand(-0.125f, 0.125f));
		pos.y = center.y + static_cast<float>(myMath::GetRand(-0.125f, 0.125f));
		pos.z = center.z;

		//�����������W���璆�S���W�Ɍ���������
		myMath::Vector3 particleFrontVec = center - pos;
		//���ʃx�N�g���𐳋K��
		particleFrontVec.normalization();
		
		const float speed = 0.25f / lifeTime;
		//���ʃx�N�g���̕�����speed���i��
		myMath::Vector3 vel = particleFrontVec * speed;

		//�i�X�������ɂȂ�悤�ȏ���
		myMath::Vector3 acc{};

		myMath::Vector4 col = { 1.0f,1.0f,1.0f,1.0f };

		//�ǉ�
		particleMan_->Add(lifeTime, pos, vel, acc, 0.5f, 0.0f, col);
	}
}

void PlayerEngineSmokeParticleEmitter::Update(Camera* camera)
{
	particleMan_->Update(camera);
}

void PlayerEngineSmokeParticleEmitter::Draw()
{
	particleMan_->Draw();
}