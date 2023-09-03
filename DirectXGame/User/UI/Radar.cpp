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
		if (enemy->GetSpawnFlag() == true && radarSize >= length)
		{
			radarEnemys_[count]->DrawSprite2D({ center_.x + difference.x * cosf(angle) + difference.y * sinf(angle),
				center_.y + difference.y * cosf(angle) - difference.x * sinf(angle) }, { 1.0f,1.0f ,1.0f ,1.0f }, { 1.0f,1.0f }, enemy->GetTrans().rotation.y - myMath::AX_PIF / 2 - angle);
		}
		count++;
	}
	player_->DrawSprite2D(center_, { 1.0f,1.0f,1.0f,1.0f }, { 1.0f ,1.0f }, 0.0f);
	radar_->DrawSprite2D(center_);
}