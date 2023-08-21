#include "Player.h"
#include"PhysicsMath.h"
#include"ColliderManager.h"
#include<imgui.h>

Player::~Player()
{
	ColliderManager::GetInstance()->SubCollision(this);
}

void Player::Initialize()
{
	input_ = InputManager::GetInstance();

	//レティクルの初期化
	reticle_ = std::make_unique<Reticle>();
	reticle_->Initialize();

	//プレイヤーの初期化
	player_ = std::make_unique<Model>();
	playerTex_ = player_->CreateObjModel("Resources/F-35E");
	player_->SetModel(playerTex_);
	playerTrans_.Initialize();
	playerTrans_.translation = { 0.0f,-reticle_->GetReticleLimit() / 9,10.0f };
	playerTrans_.scale = { 0.5f,0.5f,0.5f };
	cameraTrans_.Initialize();

	//HPバーの初期化
	hpBar_ = std::make_unique<HPBar>();
	hpBar_->Initialize(maxHp_, { 100.0f,100.0f });

	//パーティクルの初期化
	smokeEmitter_ = std::make_unique<PlayerEngineSmokeParticleEmitter>();
	smokeEmitter_->Initialize();
	smokeTrans_.Initialize();

	//死亡演出の初期化
	deathAnimation_ = std::make_unique<PlayerDeathAnimation>();
	deathAnimation_->Initialize();

	collisionData_.radius = 1.0f;

	ColliderManager::GetInstance()->AddCollision(this);
}

void Player::Update()
{
	//カメラを親にする為に行列をTransformのmatWorldに登録
	cameraTrans_.matWorld = camera_->GetMatView();
	//レティクルの親にカメラを設定
	playerTrans_.parent = &cameraTrans_;

	//HPバーの更新
	hpBar_->Update(hp_);

	if (hp_ <= 0)
	{
		//死亡演出の更新処理
		deathAnimation_->Update(playerTrans_.parentToTranslation);
	}
	else
	{
		reticle_->SetCamera(camera_);
		//レティクルの更新処理
		reticle_->Update();
		//自機の移動処理
		Move();
		//ロックオン攻撃
		LockOnAttack();
	}

	//Transformの更新処理
	playerTrans_.TransUpdate(camera_);

	collisionData_.center = playerTrans_.parentToTranslation;

	//ローカルの正面ベクトル
	directionVector_ = reticle_->GetTransform().translation - playerTrans_.translation;
	//正規化
	directionVector_.normalization();

	//ワールドの正面ベクトル
	parentToDirectionVector_ = reticle_->GetTransform().parentToTranslation - playerTrans_.parentToTranslation;
	//正規化
	parentToDirectionVector_.normalization();

	//自機の回転処理
	Rotation(camera_);

	//弾の更新処理
	BulletUpdate();
	//エンジンの煙の更新処理
	SmokeUpdate(camera_);
	//死亡演出のパーティクルの更新処理
	deathAnimation_->ParticleUpdate(camera_);
	//死亡演出で死亡させたときのフラグの値を貰う
	deathFlag_ = deathAnimation_->GetDeathFlag();
}

void Player::Draw()
{
	if (hp_ > 0)
	{
		//レティクルの描画
		reticle_->Draw();
		//プレイヤーのモデル描画
		player_->DrawModel(&playerTrans_);
		//機体のエンジンから火が出るパーティクルの描画
		smokeEmitter_->Draw();
		//HPバーの描画
		hpBar_->Draw();
	}

	//死亡演出の描画
	deathAnimation_->Draw();
}

std::string Player::GetName()
{
	return name_;
}

const CollisionData& Player::GetCollisionData()
{
	return collisionData_;
}

void Player::OnCollision()
{
	hp_--;
	hp_ = max(hp_, 0);
	damageFlag_ = true;
}

const bool Player::GetIsDead()
{
	return deathFlag_;
}

const bool Player::GetDeathAnimationFlag()
{
	return deathAnimation_.get();
}

void Player::LockOn()
{
}

const bool Player::GetLockOnFlag()
{
	return lockOnAttackFlag;
}

void Player::Reset()
{
	playerTrans_.translation = { 0.0f,-reticle_->GetReticleLimit() / 9,10.0f };
	hp_ = 10;
	//レティクルのリセット
	reticle_->Reset();
	lockOnAttackFlag = false;
}

const bool Player::GetDamageFlag()
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

void Player::SetDamageFlag(const bool damageFlag)
{
	damageFlag_ = damageFlag;
}

const myMath::Vector3& Player::GetAddTargetPos()
{
	return targetPos;
}

void Player::SetCamera(Camera* camera)
{
	camera_ = camera;
}

void Player::SetBulletManager(BulletManager* bulletManager)
{
	bulletManager_ = bulletManager;
}

void Player::Move()
{
	//先に補間先の座標を定義する
	float reticleX = reticle_->GetTransform().translation.x / 6;
	float reticleY = reticle_->GetTransform().translation.y / 6;
	//そのまま移動させると動きが硬いので補完する
	PhysicsMath::Complement(playerTrans_.translation.x, reticleX, 30.0f);
	PhysicsMath::Complement(playerTrans_.translation.y, reticleY, 30.0f);
}

void Player::Rotation(Camera* camera)
{
	//レティクルの方向に向くように回転
	playerTrans_.rotation.x = -std::atan2(directionVector_.y, directionVector_.z);
	playerTrans_.rotation.y = -std::atan2(directionVector_.z, directionVector_.x) + myMath::AX_PIF / 2;

	float angleZ = -(reticle_->GetTransform().translation.x / 6 - playerTrans_.translation.x) / 5.0f;
	//モデルのZ軸回転
	PhysicsMath::Complement(playerTrans_.rotation.z, angleZ, 15.0f);

	myMath::Vector3 cameraFrontVec = camera->GetTarget() - camera->GetEye();
	myMath::Vector3 cameraUp =
	{
		sinf(cameraFrontVec.y) * sinf(playerTrans_.rotation.z),
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

void Player::BulletUpdate()
{
	if (hp_ > 0)
	{
		if (input_->KeyboardTriggerPush(DIK_SPACE) || input_->ControllerButtonTriggerPush(A))
		{
			//弾の作成
			bulletManager_->CreateNormalBullet(playerTrans_.parentToTranslation, parentToDirectionVector_, BulletOwner::Player);
		}
	}
}

void Player::SmokeUpdate(Camera* camera)
{
	//エンジンの座標に合わせるため、モデルの中心座標から位置をずらせるように子を作成
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

void Player::LockOnAttack()
{
	if (input_->KeyboardKeepPush(DIK_SPACE) || input_->ControllerButtonKeepPush(A))
	{
		lockOnAttackFlag = true;
	}

	if (lockOnAttackFlag == true)
	{
		if (input_->KeyboardTriggerRelease(DIK_SPACE) || input_->ControllerButtonTriggerRelease(A))
		{
			for (auto& lockOnEnemy : ColliderManager::GetInstance()->GetLockOnEnemy())
			{
				myMath::Vector3 controlPoint = { static_cast<float>(myMath::GetRandPlusOrMinus() *myMath::GetRand(playerTrans_.parentToTranslation.x + 1.0f,playerTrans_.parentToTranslation.x + 2.0f)),
				static_cast<float>(myMath::GetRandPlusOrMinus() * myMath::GetRand(playerTrans_.parentToTranslation.x + 1.0f,playerTrans_.parentToTranslation.x + 2.0f)) ,
				static_cast<float>(myMath::GetRandPlusOrMinus() * myMath::GetRand(playerTrans_.parentToTranslation.x + 1.0f,playerTrans_.parentToTranslation.x + 2.0f)) };
				bulletManager_->CreateLockOnBullet(playerTrans_.parentToTranslation, lockOnEnemy->GetCollisionData().center, controlPoint);
			}
			ColliderManager::GetInstance()->ResetLockOnEnemy();
			lockOnAttackFlag = false;
		}
	}
}