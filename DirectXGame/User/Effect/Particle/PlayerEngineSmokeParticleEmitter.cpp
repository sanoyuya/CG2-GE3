#include "PlayerEngineSmokeParticleEmitter.h"

void PlayerEngineSmokeParticleEmitter::Initialize()
{
	// パーティクル生成
	particleMan_ = std::make_unique<ParticleManager>();
	tex_ = particleMan_->LoadTexture("Resources/Texture/particle.png");
	particleMan_->Initialize(tex_);
}

void PlayerEngineSmokeParticleEmitter::Create(const myMath::Vector3 center)
{
	for (int i = 0; i < 5; i++)
	{
		const float lifeTime = 15.0f;
		const float radius = 0.125f;
		//初期座標(生成する場所の中心座標)
		myMath::Vector3 pos{};
		//中心点から半径1mの円の中にランダムに設定
		pos.x = center.x + static_cast<float>(myMath::GetRand(-radius, radius));
		pos.y = center.y + static_cast<float>(myMath::GetRand(-radius, radius));
		pos.z = center.z;

		//生成した座標から中心座標に向かう処理
		myMath::Vector3 particleFrontVec = center - pos;
		//正面ベクトルを正規化
		particleFrontVec.normalization();
		
		const float speed = radius * 2 / lifeTime;
		//正面ベクトルの方向にspeed分進む
		myMath::Vector3 vel = particleFrontVec * speed;

		myMath::Vector3 acc{};

		//追加
		particleMan_->Add(lifeTime, pos, vel, acc, size_, 0.0f, color_);
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

void PlayerEngineSmokeParticleEmitter::SetSize(const float size)
{
	size_ = size;
}

void PlayerEngineSmokeParticleEmitter::SetColor(myMath::Vector4 color)
{
	color_ = color;
}