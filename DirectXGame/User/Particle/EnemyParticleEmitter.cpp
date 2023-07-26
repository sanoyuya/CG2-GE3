#include "EnemyParticleEmitter.h"

void EnemyParticleEmitter::Initialize()
{
	// パーティクル生成
	particleMan_ = std::make_unique<ParticleManager>();
	tex_ = particleMan_->LoadTexture("Resources/particle.png");
	particleMan_->Initialize(tex_);
}

void EnemyParticleEmitter::Create(const myMath::Vector3 center)
{
	for (int i = 0; i < 60; i++)
	{
		//初期座標(生成する場所の中心座標)
		myMath::Vector3 pos{};
		pos.x = center.x;
		pos.y = center.y;
		pos.z = center.z;

		//速度
		myMath::Vector3 vel = { static_cast<float>(myMath::GetRand(-1.0f,1.0f)),static_cast<float>(myMath::GetRand(-1.0f,1.0f)) ,static_cast<float>(myMath::GetRand(-1.0f,1.0f)) };

		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
		myMath::Vector3 acc{};
		float yadd = 0.0245f;
		acc.y -= yadd;

		myMath::Vector4 col = { 1.0f,1.0f,1.0f,1.0f };

		//追加
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