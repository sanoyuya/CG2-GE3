#include "Radar.h"
uint32_t Radar::sRadarTex_;
uint32_t Radar::sPlayerTex_;
uint32_t Radar::sEnemyTex_;

void Radar::Initialize(EnemyManager* enemys)
{
	radar_ = std::make_unique<Sprite>();
	radar_->Sprite2DInitialize(sRadarTex_);

	player_ = std::make_unique<Sprite>();
	player_->Sprite2DInitialize(sPlayerTex_);

	for (uint8_t i = 0; i < enemys->GetEnemyList().size(); i++)
	{
		std::unique_ptr<Sprite>tmp = std::make_unique<Sprite>();
		tmp->Sprite2DInitialize(sEnemyTex_);
		radarEnemys_.push_back(std::move(tmp));
	}
}

void Radar::Update(Camera* camera)
{
	//カメラの方向ベクトルを作成
	cameraFrontVec_ = camera->GetTarget() - camera->GetEye();
	//正規化
	cameraFrontVec_.normalization();
}

void Radar::Draw(EnemyManager* enemys, Player* player)
{
	uint8_t count = 0;
	//カメラのangleYの取得(正面ベクトルから取得)
	float angle = -(atan2(cameraFrontVec_.z, cameraFrontVec_.x) + myMath::AX_PIF / 2);

	for (auto& enemy : enemys->GetEnemyList())
	{
		//自機と敵との位置の差
		myMath::Vector2 difference = { player->GetTransform().parentToTranslation.x - enemy->GetTrans().translation.x,
			enemy->GetTrans().translation.z - player->GetTransform().parentToTranslation.z };
		//自機と敵との距離の算出
		float length = sqrt(difference.x * difference.x) + sqrt(difference.y * difference.y);

		//敵が出現しているかつレーダーの内側の範囲内にいるなら
		if ((enemy->GetSpawnFlag() == true && radarSize >= length) && enemy->GetDeathAnimationFlag() == false)
		{
			radarEnemys_[count]->DrawSprite2D({ center_.x + difference.x * cosf(angle) + difference.y * sinf(angle),
				center_.y + difference.y * cosf(angle) - difference.x * sinf(angle) }, { 1.0f,1.0f ,1.0f ,1.0f }, { 1.0f,1.0f }, enemy->GetTrans().rotation.y - myMath::AX_PIF / 2 - angle);
		}
		count++;
	}
	player_->DrawSprite2D(center_, { 1.0f,1.0f,1.0f,1.0f }, { 1.0f ,1.0f }, 0.0f);
	radar_->DrawSprite2D(center_);
}

void Radar::LoadAsset()
{
	sRadarTex_ = TextureManager::GetInstance()->LoadTexture("Resources/radar.png");
	sPlayerTex_ = TextureManager::GetInstance()->LoadTexture("Resources/radarPlayer.png");
	sEnemyTex_ = TextureManager::GetInstance()->LoadTexture("Resources/radarEnemy.png");
}