#include "ParticleEmitter.h"

void ParticleEmitter::Initialize()
{
	// �p�[�e�B�N������
	particleMan_ = std::make_unique<ParticleManager>();
	tex_ = particleMan_->LoadTexture("Resources/reticle.png");
	particleMan_->Initialize(tex_);
}

void ParticleEmitter::Create(const myMath::Vector3 center)
{
	for (int i = 0; i < 10; i++)
	{
		//X,Y,Z�S��[-10.0f,+10.0f]�Ń����_���ɕ��z
		const float rnd_pos = 20.0f;
		const float rnd_col = 255.0f;
		myMath::Vector3 pos{};
		pos.x = center.x + (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = center.y + (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = center.z + (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		//X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
		const float rnd_vel = 0.1f;
		myMath::Vector3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//�d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_���ɕ��z
		myMath::Vector3 acc{};
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		myMath::Vector4 col{};
		col.x = (float)rand() / RAND_MAX * rnd_col;
		col.y = (float)rand() / RAND_MAX * rnd_col;
		col.z = (float)rand() / RAND_MAX * rnd_col;
		col.w = 255.0f;

		//�ǉ�
		particleMan_->Add(60.0f, pos, vel, acc, 10.0f, 0.0f, col);
	}
}

void ParticleEmitter::Update(Camera* camera)
{
	particleMan_->Update(camera);
}

void ParticleEmitter::Draw()
{
	particleMan_->Draw();
}