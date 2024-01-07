#include "EnemyLocationSprite.h"
#include"GameHeader.h"
uint32_t EnemyLocationSprite::spriteTex_;

void EnemyLocationSprite::LoadAsset()
{
	spriteTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/attention.png");
}

void EnemyLocationSprite::Load(EnemyManager* enemys)
{
	enemyCount_ = static_cast<uint8_t>(enemys->GetEnemyList().size());
	Initialize();
}

void EnemyLocationSprite::ReLoad(EnemyManager* enemys)
{
	sprite_.clear();
	Load(enemys);
}

void EnemyLocationSprite::Initialize()
{
	for (uint8_t i = 0; i < enemyCount_; i++)
	{
		std::unique_ptr<Sprite2D> tmp = std::make_unique<Sprite2D>();
		tmp->Sprite2DInitialize(spriteTex_);
		sprite_.push_back(std::move(tmp));
	}
}

void EnemyLocationSprite::Update()
{

}

void EnemyLocationSprite::Draw(EnemyManager* enemys, Camera* camera)
{
	uint8_t count = 0;

	for (auto& enemy : enemys->GetEnemyList())
	{
		if (enemy->GetSpawnFlag() == true && enemy->GetDeathAnimationFlag() == false)
		{
			//画面内に収める処理
			myMath::Vector2 pos = { myMath::ScreenCoordinateTransformation(camera,enemy->GetTransform().parentToTranslation).x,myMath::ScreenCoordinateTransformation(camera,enemy->GetTransform().parentToTranslation).y };
			bool isDraw = false;
			if (0.0f > pos.x || pos.x > GameHeader::windowsSize_.x || 0.0f > pos.y || pos.y > GameHeader::windowsSize_.y)
			{
				isDraw = true;
			}

			if (isDraw == true)
			{
				pos.x = std::clamp(pos.x, texSize_.x, GameHeader::windowsSize_.x - texSize_.x);
				pos.y = std::clamp(pos.y, texSize_.y, GameHeader::windowsSize_.x - texSize_.y);

				//後ろにいる敵は下に描画されるようにする
				if (myMath::ScreenCoordinateTransformation(camera, enemy->GetTransform().parentToTranslation).z < 0.0f)
				{
					pos.y = GameHeader::windowsSize_.y - texSize_.y;
				}

				sprite_[count]->DrawSprite2D(pos, { 1.0f,1.0f,1.0f,0.5f });
			}
		}
		count++;
	}
}