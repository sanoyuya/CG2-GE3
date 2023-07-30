#include "Player.h"
#include <algorithm>
#include"PhysicsMath.h"
#include"ColliderManager.h"
#include<imgui.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	input_ = InputManager::GetInstance();

	player_ = std::make_unique<Model>();
	playerTex_ = player_->CreateObjModel("Resources/F-35E");
	player_->SetModel(playerTex_);
	playerTrans_.Initialize();
	playerTrans_.translation = { 0.0f,-reticleLimit_ / 3,10.0f };
	playerTrans_.scale = { 0.5f,0.5f,0.5f };
	cameraTrans_.Initialize();

	reticle_ = std::make_unique<Sprite>();
	reticleTex_ = reticle_->LoadTexture("Resources/reticle.png");
	reticle_->Sprite3DInitialize(reticleTex_);
	reticleTrans_.Initialize();
	reticleTrans_.translation = { 0.0f,-reticleLimit_,30.0f };
	reticleTrans_.scale = { 0.125f,0.125f,1.0f };

	hpBar_ = std::make_unique<Sprite>();
	hpBarTex_ = reticle_->LoadTexture("Resources/white1x1.png");
	hpBar_->Sprite2DInitialize(hpBarTex_);

	// パーティクル生成
	smokeEmitter_ = std::make_unique<PlayerEngineSmokeParticleEmitter>();
	smokeEmitter_->Initialize();
	smokeTrans_.Initialize();
}

void Player::Update(Camera* camera)
{
	cameraTrans_.matWorld = camera->GetMatView();
	playerTrans_.parent = &cameraTrans_;
	reticleTrans_.parent = &cameraTrans_;

	MoveLimit();
	ReticleMove();
	Move();
	ReticleLimit();

	playerTrans_.TransUpdate(camera);
	reticleTrans_.TransUpdate(camera);

	directionVector_ = reticleTrans_.translation - playerTrans_.translation;//ローカルの正面ベクトル
	directionVector_.normalization();//正規化

	parentToDirectionVector_ = reticleTrans_.parentToTranslation - playerTrans_.parentToTranslation;//ワールドの正面ベクトル
	parentToDirectionVector_.normalization();//正規化

	Rotation(camera);

	BulletUpdate(camera);

	SmokeUpdate(camera);
}

void Player::Draw(Camera* camera)
{
	reticle_->DrawSprite3D(camera, reticleTrans_);
	BulletDraw();
	player_->DrawModel(&playerTrans_);
	smokeEmitter_->Draw();
	myMath::Vector4 hpColor = {};
	if (hp_ > maxHp_ / 2)
	{
		hpColor = { 130.0f/ 255.0f,174.0f/ 255.0f,70.0f/ 255.0f,1.0f };
	}
	else if (hp_ > maxHp_ / 4 && hp_ <= maxHp_ / 2)
	{
		hpColor = { 255.0f / 255.0f,217.0f / 255.0f,0.0f / 255.0f,1.0f };
	}
	else
	{
		hpColor= { 255.0f / 255.0f,0.0f / 255.0f,0.0f / 255.0f,1.0f };
	}
	hpBar_->DrawSprite2D({ 100,100 }, hpColor, { 20.0f * hp_,20.0f }, 0.0f, { 0.0f,0.0f });
}

void Player::Reset()
{
	playerTrans_.translation = { 0.0f,-reticleLimit_ / 3,10.0f };
	reticleTrans_.translation = { 0.0f,-reticleLimit_,30.0f };
	hp_ = 10;
}

void Player::HpSub()
{
	hp_--;
	hp_ = max(hp_, 0);
	damageFlag_ = true;
}

const bool& Player::GetDamageFlag()
{
	return damageFlag_;
}

const Transform& Player::GetTransform()
{
	return playerTrans_;
}

const uint8_t Player::GetHp()
{
	return hp_;
}

void Player::SetDamageFlag(const bool& damageFlag)
{
	damageFlag_ = damageFlag;
}

const myMath::Vector3& Player::GetAddTargetPos()
{
	return targetPos;
}

void Player::Move()
{
	//先に補間先の座標を定義する
	float reticleX = reticleTrans_.translation.x / 2;
	float reticleY = reticleTrans_.translation.y / 2;
	//そのまま移動させると動きが硬いので補完する
	PhysicsMath::Complement(playerTrans_.translation.x, reticleX, 30.0f);
	PhysicsMath::Complement(playerTrans_.translation.y, reticleY, 30.0f);
}

void Player::Rotation(Camera* camera)
{
	//レティクルの方向に向くように回転
	playerTrans_.rotation.x = -std::atan2(directionVector_.y, directionVector_.z);
	playerTrans_.rotation.y = -std::atan2(directionVector_.z, directionVector_.x) + myMath::AX_PIF / 2;

	float angleZ = -(reticleTrans_.translation.x / 2 - playerTrans_.translation.x) / 5.0f;
	//モデルのZ軸回転
	PhysicsMath::Complement(playerTrans_.rotation.z, angleZ, 15.0f);

	myMath::Vector3 cameraFrontVec = camera->GetTarget() - camera->GetEye();
	myMath::Vector3 cameraUp =
	{
		sinf(cameraFrontVec.y)* sinf(playerTrans_.rotation.z),
		cosf(cameraFrontVec.y) * cosf(playerTrans_.rotation.z),
		0.0f
	};
	camera->SetUp(cameraUp);

	//プレイヤーの横向きの回転をワールド座標に変換し、後でカメラに足せるように変数に格納
	targetPos = (playerTrans_.matWorld.Transform(playerTrans_.matWorld, { 0,0,1 }) - playerTrans_.matWorld.Transform(playerTrans_.matWorld, { 0,0,0 })) * 0.1f;

	ImGui::Begin("rot");
	ImGui::InputFloat3("playerRot", &playerTrans_.rotation.x);
	ImGui::InputFloat3("cameraFrontVec", &cameraFrontVec.x);
	myMath::Vector3 cameraTarget = camera->GetTarget();
	ImGui::InputFloat3("cameraTarget", &cameraTarget.x);
	myMath::Vector3 cameraPos = camera->GetEye();
	ImGui::InputFloat3("cameraPos", &cameraPos.x);
	ImGui::End();
}

void Player::ReticleMove()
{
#pragma region キーボード
	if (input_->KeyboardKeepPush(DIK_UP))
	{
		reticleTrans_.translation += {0.0f, reticleSpeed_, 0.0f};
	}
	if (input_->KeyboardKeepPush(DIK_LEFT))
	{
		reticleTrans_.translation += {-reticleSpeed_, 0.0f, 0.0f};
	}
	if (input_->KeyboardKeepPush(DIK_DOWN))
	{
		reticleTrans_.translation += {0.0f, -reticleSpeed_, 0.0f};
	}
	if (input_->KeyboardKeepPush(DIK_RIGHT))
	{
		reticleTrans_.translation += {reticleSpeed_, 0.0f, 0.0f};
	}
#pragma endregion キーボード

#pragma region コントローラー

	//Lスティックを傾けることで移動できるようにする
	reticleTrans_.translation += {reticleSpeed_* input_->GetLeftStickVec().x, -reticleSpeed_ * input_->GetLeftStickVec().y, 0.0f};

#pragma endregion コントローラー
}

void Player::MoveLimit()
{
	/*playerTrans_.translation.x = std::clamp(playerTrans_.translation.x, -moveLimit, moveLimit);
	playerTrans_.translation.y = std::clamp(playerTrans_.translation.y, -moveLimit / 16 * 9, moveLimit / 16 * 9);*/
}

void Player::ReticleLimit()
{
	reticleTrans_.translation.x = std::clamp(reticleTrans_.translation.x, -reticleLimit_, reticleLimit_);
	//画面比率に合わせた制限処理(x:y,16:9)
	reticleTrans_.translation.y = std::clamp(reticleTrans_.translation.y, -reticleLimit_ / 16 * 9, reticleLimit_ / 16 * 9);
}

void Player::BulletUpdate(Camera* camera)
{
	if (input_->KeyboardTriggerPush(DIK_SPACE) || input_->ControllerButtonTriggerPush(A))
	{
		//弾の作成
		CreateBullet(playerTrans_.parentToTranslation, parentToDirectionVector_, BulletOwner::Player);
	}

	//弾の更新処理
	Character::BulletUpdate(camera);
}

void Player::BulletDraw()
{
	for (const std::unique_ptr<Bullet>& bullet : bullets_)
	{
		bullet->Draw();//弾の描画
	}
}

void Player::SmokeUpdate(Camera* camera)
{
	//モーター(?)の座標に合わせるため、モデルの中心座標から位置をずらせるように子を作成
	smokeTrans_.parent = &playerTrans_;
	//モデルの中心座標から位置をずらす
	smokeTrans_.translation = { 0.0f,-0.3f,-4.0f };
	//子の更新処理
	smokeTrans_.TransUpdate(camera);
	//パーティクルを毎フレーム作成
	smokeEmitter_->Create(smokeTrans_.parentToTranslation);
	//パーティクルの更新
	smokeEmitter_->Update(camera);
}