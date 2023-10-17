#include "Player.h"
#include"PhysicsMath.h"
#include"ColliderManager.h"
#include<imgui.h>
myMath::Vector3 Player::targetPos_;
CameraFlag Player::cameraFlag_;

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
	playerTrans_.translation = { 0.0f,-reticle_->GetReticleLimit() / 9,0.0f };
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

	controlTrans_.Initialize();
	controlTrans_.translation.z = 10.0f;

	collisionData_.radius = 1.0f;

	//マネージャーに当たり判定を渡す
	ColliderManager::GetInstance()->AddCollision(this);
}

void Player::Update()
{
	//レティクルの親にカメラを設定
	playerTrans_.parent = &camera_->GetRailTrans();

	//HPバーの更新
	hpBar_->Update(hp_);

	if (hp_ <= 0)
	{
		//死亡演出の更新処理
		deathAnimation_->Update(playerTrans_.parentToTranslation);
	}
	else
	{
		//カメラのセット
		reticle_->SetCamera(camera_->GetCameraPtr());
		//レティクルの更新処理
		reticle_->Update();
		//自機の移動処理
		Move();
		CameraRotation();
		if (isBulletAttack_ == false)
		{
			//弾の更新処理
			NormalBulletAttack();
			//ロックオン攻撃
			LockOnAttack();
		}
		else
		{
			coolTime_++;
			if (coolTime_ >= maxCoolTime_)
			{
				coolTime_ = 0;
				isBulletAttack_ = false;
			}
		}
	}

	//Transformの更新処理
	playerTrans_.TransUpdate(camera_->GetCameraPtr());

	controlTrans_.parent = &playerTrans_;
	controlTrans_.TransUpdate(camera_->GetCameraPtr());

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
	Rotation(camera_->GetCameraPtr());

	//エンジンの煙の更新処理
	SmokeUpdate(camera_->GetCameraPtr());
	//死亡演出のパーティクルの更新処理
	deathAnimation_->ParticleUpdate(camera_->GetCameraPtr());
	//死亡演出で死亡させたときのフラグの値を貰う
	deathFlag_ = deathAnimation_->GetDeathFlag();

#ifdef _DEBUG
	ImGuiUpdate();
#endif _DEBUG
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
	hp_--;//hp減少
	hp_ = max(hp_, 0);//0を下回らない処理
	damageFlag_ = true;//ダメージエフェクトを表示
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

void Player::CancelLockOn()
{
}

const bool Player::GetLockOnFlag()
{
	return lockOnAttackFlag_;
}

void Player::Reset()
{
	playerTrans_.translation = { 0.0f,-reticle_->GetReticleLimit() / 9,0.0f };
	hp_ = 10;
	//レティクルのリセット
	reticle_->Reset();
	lockOnAttackFlag_ = false;
	//マネージャーに当たり判定を渡す
	ColliderManager::GetInstance()->AddCollision(this);
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
	return targetPos_;
}

void Player::SetCamera(RailCamera* camera)
{
	camera_ = camera;
}

void Player::SetBulletManager(BulletManager* bulletManager)
{
	bulletManager_ = bulletManager;
}

const bool Player::GetIsBulletAttack()
{
	return isBulletAttack_;
}

void Player::Move()
{
	//先に補間先の座標を定義する
	float reticleX = -reticle_->GetTransform().translation.x / 6;
	float reticleY = reticle_->GetTransform().translation.y / 6;
	//そのまま移動させると動きが硬いので補完する
	PhysicsMath::Complement(playerTrans_.translation.x, reticleX, 30.0f);
	PhysicsMath::Complement(playerTrans_.translation.y, reticleY, 30.0f);
}

const CameraFlag& Player::GetCameraFlag()
{
	return cameraFlag_;
}

void Player::Rotation(Camera* camera)
{
	//レティクルの方向に向くように回転
	playerTrans_.rotation.x = -std::atan2(directionVector_.y, directionVector_.z);
	playerTrans_.rotation.y = -std::atan2(directionVector_.z, directionVector_.x) + myMath::AX_PIF / 2;

	//float angleZ = reticle_->GetTransform().translation.x / 6 - playerTrans_.translation.x / 5.0f;
	////モデルのZ軸回転
	//PhysicsMath::Complement(playerTrans_.rotation.z, angleZ, 15.0f);

	camera;

	/*myMath::Vector3 cameraFrontVec = camera->GetTarget() - camera->GetEye();
	myMath::Vector3 cameraUp =
	{
		sinf(cameraFrontVec.y) * sinf(playerTrans_.rotation.z),
		cosf(cameraFrontVec.y) * cosf(playerTrans_.rotation.z),
		0.0f
	};
	camera->SetUp(cameraUp);*/

	//プレイヤーの横向きの回転をワールド座標に変換し、後でカメラに足せるように変数に格納
	//targetPos_ = (playerTrans_.matWorld.Transform(playerTrans_.matWorld, { 0,0,1 }) - playerTrans_.matWorld.Transform(playerTrans_.matWorld, { 0,0,0 })) * 0.1f;
}

void Player::NormalBulletAttack()
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
	smokeEmitter_->SetSize(0.5f);
	//パーティクルの更新
	smokeEmitter_->Update(camera);
}

void Player::LockOnAttack()
{
	if (input_->KeyboardKeepPush(DIK_SPACE) || input_->ControllerButtonKeepPush(A))
	{
		lockOnTimer_++;
		if (lockOnTimer_ >= 30.0f)
		{
			lockOnAttackFlag_ = true;
		}
	}
	else
	{
		lockOnTimer_ = 0;
	}

	if (lockOnAttackFlag_ == true)
	{
		if (input_->KeyboardTriggerRelease(DIK_SPACE) || input_->ControllerButtonTriggerRelease(A))
		{
			for (auto& lockOnEnemy : ColliderManager::GetInstance()->GetLockOnEnemy())
			{
				//制御点を設定
				myMath::Vector3 controlPoint = { static_cast<float>(myMath::GetRandPlusOrMinus() * myMath::GetRand(controlTrans_.parentToTranslation.x + 0.1f,controlTrans_.parentToTranslation.x + 0.2f)),
				static_cast<float>(myMath::GetRandPlusOrMinus() * myMath::GetRand(controlTrans_.parentToTranslation.y + 0.1f,controlTrans_.parentToTranslation.y + 0.2f)) ,
				static_cast<float>(myMath::GetRandPlusOrMinus() * myMath::GetRand(controlTrans_.parentToTranslation.z + 0.1f,controlTrans_.parentToTranslation.z + 0.2f)) };

				//弾を生成
				bulletManager_->CreateLockOnBullet(playerTrans_.parentToTranslation, lockOnEnemy, controlPoint);
			}

			//ロックオン攻撃をしたらオーバーヒートするように
			if (ColliderManager::GetInstance()->GetLockOnEnemy().size() > 0)
			{
				isBulletAttack_ = true;
				//ロックオン敵listをリセット
				ColliderManager::GetInstance()->ResetLockOnEnemy();
			}
			lockOnAttackFlag_ = false;
		}
	}
}

void Player::CameraRotation()
{
	if (input_->KeyboardTriggerPush(DIK_K))
	{
		cameraFlagNum_++;
		if (cameraFlagNum_ > 3)
		{
			cameraFlagNum_ = 0;
		}
	}
	else if (input_->KeyboardTriggerPush(DIK_H))
	{
		cameraFlagNum_--;
		if (cameraFlagNum_ < 0)
		{
			cameraFlagNum_ = 3;
		}
	}

	cameraFlag_ = static_cast<CameraFlag>(cameraFlagNum_);
}

void Player::ImGuiUpdate()
{
	ImGui::Begin("HP");
	int maxHp = static_cast<int>(maxHp_);
	ImGui::InputInt("playerMaxHP", &maxHp);
	maxHp_ = static_cast<int8_t>(maxHp);
	int hp = static_cast<int>(hp_);
	ImGui::InputInt("playerHP", &hp);
	hp_ = static_cast<int8_t>(hp);
	ImGui::End();
}