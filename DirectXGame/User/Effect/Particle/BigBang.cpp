#include "BigBang.h"

void BigBang::Initialize()
{
	// パーティクル生成
	particleMan_ = std::make_unique<ParticleManager>();
	tex_ = particleMan_->LoadTexture("Resources/Texture/particle2.png");
	particleMan_->Initialize(tex_);
}

void BigBang::Create(const myMath::Vector3 center)
{
	//黒色
	for (uint8_t i = 0; i < 50; i++)
	{
		//初期座標(生成する場所の中心座標)
		myMath::Vector3 pos{};
		pos.x = center.x;
		pos.y = center.y;
		pos.z = center.z;

		//速度
		myMath::Vector3 vel = { static_cast<float>(myMath::GetRand(-0.1f,0.1f)),static_cast<float>(myMath::GetRand(-0.1f,0.1f)) ,static_cast<float>(myMath::GetRand(-0.1f,0.1f)) };

		//重力のような処理
		myMath::Vector3 acc{};

		myMath::Vector4 col = { 0 / 255.0f,0 / 255.0f,0 / 255.0f,1.0f };

		//追加
		particleMan_->Add(dethTime_, pos, vel, acc, startScale_, endScale_, col);
	}

	//灰色
	for (uint8_t i = 0; i < 50; i++)
	{
		//初期座標(生成する場所の中心座標)
		myMath::Vector3 pos{};
		pos.x = center.x;
		pos.y = center.y;
		pos.z = center.z;

		//速度
		myMath::Vector3 vel = { static_cast<float>(myMath::GetRand(-0.2f,0.2f)),static_cast<float>(myMath::GetRand(-0.2f,0.2f)) ,static_cast<float>(myMath::GetRand(-0.2f,0.2f)) };

		//重力のような処理
		myMath::Vector3 acc{};

		myMath::Vector4 col = { 108.0f / 255.0f,103.0f / 255.0f ,110.0f / 255.0f,1.0f };

		//追加
		particleMan_->Add(dethTime_, pos, vel, acc, startScale_, endScale_, col);
	}

	//オレンジ色
	for (uint8_t i = 0; i < 50; i++)
	{
		//初期座標(生成する場所の中心座標)
		myMath::Vector3 pos{};
		pos.x = center.x;
		pos.y = center.y;
		pos.z = center.z;

		//速度
		myMath::Vector3 vel = { static_cast<float>(myMath::GetRand(-0.02f,0.02f)),static_cast<float>(myMath::GetRand(-0.02f,0.02f)) ,static_cast<float>(myMath::GetRand(-0.02f,0.02f)) };

		//重力のような処理
		myMath::Vector3 acc{};

		myMath::Vector4 col = { 245.0f / 255.0f,130.0f / 255.0f,32.0f / 255.0f,1.0f };

		//追加
		particleMan_->Add(dethTime_, pos, vel, acc, startScale_, endScale_, col);
	}
}

void BigBang::Update(Camera* camera)
{
	particleMan_->Update(camera);
}

void BigBang::Draw()
{
	particleMan_->Draw();
}