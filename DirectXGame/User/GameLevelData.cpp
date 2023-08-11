#include "GameLevelData.h"
#include"ColliderManager.h"

GameLevelData::GameLevelData()
{
}

GameLevelData::~GameLevelData()
{
}

void GameLevelData::Initialize(const std::string& fileName)
{
	fileName_ = fileName;
	CreateModel();
	Load();
}

void GameLevelData::Update(Camera* camera)
{
	for (auto& object : objects_)
	{
		object->Update(camera);
	}
}

void GameLevelData::Draw()
{
	for (auto& object : objects_)
	{
		object->Draw();
	}
}

void GameLevelData::CreateModel()
{
	playerTex_ = Model::CreateObjModel("Resources/greenDice");
	sphereTex_ = Model::CreateObjModel("Resources/sphere");
	tex_ = Model::CreateObjModel("Resources/purpleDice");
}

void GameLevelData::Load()
{
	std::unique_ptr<LevelData> levelData_ = std::make_unique<LevelData>();
	levelData_.reset(LevelEditor::LoadLevelEditorFile(fileName_));

	//レベルデータからオブジェクトを生成、配置
	for (auto& objectData : levelData_->objects_)
	{
		if (objectData.fileName == "player")
		{
			continue;
		}
		else if (objectData.fileName == "camera")
		{
			cameraData_.position = objectData.translation;
		}
		else if (objectData.fileName == "cameraPoint")
		{
			//制御点を登録
			cameraData_.controlPoints.push_back(objectData.translation);
		}
		else if (objectData.fileName == "normalEnemy")
		{
			std::unique_ptr<Enemy>enemy = std::make_unique<NormalEnemy>();
			enemy->SetPosition(objectData.translation);
			//blender上と座標系が若干ずれているので若干修正して送る
			enemy->SetRotation({ myMath::ChangeRadians(objectData.rotation.x), myMath::ChangeRadians(objectData.rotation.y) + myMath::AX_PIF / 2, myMath::ChangeRadians(objectData.rotation.z) - myMath::AX_PIF / 2 });
			//半径さえ分かれば良いのでxの値のみ送る
			enemy->SetColliderSize(objectData.collider.size.x);
			//blender側で設定した時間を送る
			enemy->SetSpawnTimer(objectData.timer.spawnTimer);
			enemy->SetDeathTimer(objectData.timer.deathTimer);
			//Enemyを登録
			enemyData_.enemys.push_back(std::move(enemy));
		}
		else
		{
			//ファイル名から登録済みモデルを検索
			std::unique_ptr<EditorObject> model = std::make_unique<EditorObject>();
			model->Initialize();

			//座標
			model->SetPos(objectData.translation);
			//回転角
			model->SetRot(objectData.rotation);
			//拡縮
			model->SetScale(objectData.scaling);
			//名前
			model->SetName(objectData.fileName);
			//コライダーの中心座標
			model->SetColliderCenter(objectData.collider.center);
			//コライダーサイズ
			model->SetColliderSize(objectData.collider.size);

			if (objectData.fileName == "sphere")
			{
				model->SetModel(sphereTex_);
			}
			else
			{
				model->SetModel(tex_);
			}
			model->SetShader(ShaderMode::Phong);

			objects_.push_back(std::move(model));
		}
	}
}

const PlayerData& GameLevelData::GetPlayerData()
{
	return playerData_;
}

const CameraData& GameLevelData::GetCameraData()
{
	return cameraData_;
}

EnemyData& GameLevelData::GetEnemyData()
{
	return enemyData_;
}

void GameLevelData::ReLoad()
{
	//削除して再読み込み
	models_.clear();
	objects_.clear();
	cameraData_.controlPoints.clear();
	enemyData_.enemys.clear();
	Load();
}