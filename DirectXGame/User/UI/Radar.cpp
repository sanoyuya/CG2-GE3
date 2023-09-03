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
	//�J�����̕����x�N�g�����쐬
	cameraFrontVec_ = camera->GetTarget() - camera->GetEye();
	//���K��
	cameraFrontVec_.normalization();
}

void Radar::Draw(EnemyManager* enemys, Player* player)
{
	uint8_t count = 0;
	//�J������angleY�̎擾(���ʃx�N�g������擾)
	float angle = -(atan2(cameraFrontVec_.z, cameraFrontVec_.x) + myMath::AX_PIF / 2);

	for (auto& enemy : enemys->GetEnemyList())
	{
		//���@�ƓG�Ƃ̈ʒu�̍�
		myMath::Vector2 difference = { player->GetTransform().parentToTranslation.x - enemy->GetTrans().translation.x,
			enemy->GetTrans().translation.z - player->GetTransform().parentToTranslation.z };
		//���@�ƓG�Ƃ̋����̎Z�o
		float length = sqrt(difference.x * difference.x) + sqrt(difference.y * difference.y);

		//�G���o�����Ă��邩���[�_�[�̓����͈͓̔��ɂ���Ȃ�
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