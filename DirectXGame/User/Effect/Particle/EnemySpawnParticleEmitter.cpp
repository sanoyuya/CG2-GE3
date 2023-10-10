#include "EnemySpawnParticleEmitter.h"

void EnemySpawnParticleEmitter::Initialize()
{
	// パーティクル生成
	particleMan_ = std::make_unique<ParticleManager>();
	tex_ = particleMan_->LoadTexture("Resources/particle.png");
	particleMan_->Initialize(tex_);
}

void EnemySpawnParticleEmitter::Create(const myMath::Vector3 center)
{
	for (int i = 0; i < 5; i++)
	{
		//初期座標(生成する場所の中心座標)
		myMath::Vector3 pos{};
		pos.x = center.x;
		pos.y = center.y - 3.0f;
		pos.z = center.z;

		//速度
		myMath::Vector3 vel = { -0.02f,0.2f ,0.0f };

		//重力のような処理
		myMath::Vector3 acc{};

		myMath::Vector4 col = { 115.0f / 255.0f,78.0f / 255.0f,149.0f / 255.0f,1.0f };

		//追加
		particleMan_->Add(30.0f, pos, vel, acc, 3.0f, 0.0f, col);
	}

	for (int i = 0; i < 5; i++)
	{
		//初期座標(生成する場所の中心座標)
		myMath::Vector3 pos{};
		pos.x = center.x;
		pos.y = center.y - 3.0f;
		pos.z = center.z;

		//速度
		myMath::Vector3 vel = { -0.02f,0.2f ,0.0f };

		//重力のような処理
		myMath::Vector3 acc{};

		myMath::Vector4 col = { 0.0f / 255.0f,0.0f / 255.0f,0.0f / 255.0f,1.0f };

		//追加
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