#include "Radar.h"

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

void Radar::Update(Camera* camera)
{
	cameraFrontVec_ = camera->GetTarget() - camera->GetEye();
}

void Radar::Draw(EnemyManager* enemys, Player * player)
{
	uint8_t count = 0;
	for (auto& enemy:enemys->GetEnemyList())
	{
		myMath::Vector2 difference = { (enemy->GetTrans().translation.x + player->GetTransform().parentToTranslation.x*sinf(cameraFrontVec_.x- myMath::AX_PIF / 4)),
			(enemy->GetTrans().translation.z - player->GetTransform().parentToTranslation.z)*cosf(cameraFrontVec_.z- myMath::AX_PIF / 4)};
		float length = sqrt(difference.x * difference.x)+ sqrt(difference.y * difference.y);

		//ƒŒ[ƒ_[‚Ì“à‘¤‚Ì”ÍˆÍ“à‚É‚¢‚é‚È‚ç
		if (radarSize >= length)
		{
			radarEnemys_[count]->DrawSprite2D({ center_.x + difference.x,center_.y + difference.y },{1.0f,1.0f ,1.0f ,1.0f },{1.0f,1.0f}, enemy->GetTrans().rotation.y - myMath::AX_PIF);
		}
		count++;
	}
	player_->DrawSprite2D(center_,{1.0f,1.0f,1.0f,1.0f },{ 1.0f ,1.0f },player->GetTransform().rotation.y);
	radar_->DrawSprite2D(center_);
}