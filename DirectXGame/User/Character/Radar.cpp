#include "Radar.h"

Radar::Radar()
{
}

Radar::~Radar()
{
}

void Radar::Initialize(EnemyManager* enemys)
{
	radar_ = std::make_unique<Sprite>();
	radarTex_ = radar_->LoadTexture("Resources/radar.png");
	radar_->Sprite2DInitialize(radarTex_);

	player_ = std::make_unique<Sprite>();
	playerTex_ = radar_->LoadTexture("Resources/radarPlayer.png");
	player_->Sprite2DInitialize(playerTex_);

	enemyTex = radar_->LoadTexture("Resources/radarEnemy.png");
	for (uint8_t i = 0; i < enemys->GetEnemyList().size(); i++)
	{
		std::unique_ptr<Sprite>tmp = std::make_unique<Sprite>();
		tmp->Sprite2DInitialize(enemyTex);
		radarEnemys_.push_back(std::move(tmp));
	}
}

void Radar::Update()
{

}

void Radar::Draw(EnemyManager* enemys, Player * player)
{
	uint8_t count = 0;
	for (auto& enemy:enemys->GetEnemyList())
	{
		myMath::Vector2 difference = { -enemy->GetPosition().x + player->GetTransform().parentToTranslation.x,enemy->GetPosition().z - player->GetTransform().parentToTranslation.z };
		myMath::Vector2 length = { sqrt(difference.x * difference.x),sqrt(difference.y * difference.y) };

		if (radarSize >= length.x && radarSize >= length.y)
		{
			radarEnemys_[count]->DrawSprite2D({ center.x + difference.x,center.y + difference.y });
		}
		count++;
	}
	player_->DrawSprite2D(center,{1.0f,1.0f,1.0f,1.0f },{ 1.0f ,1.0f },player->GetTransform().rotation.y);
	radar_->DrawSprite2D(center);
}