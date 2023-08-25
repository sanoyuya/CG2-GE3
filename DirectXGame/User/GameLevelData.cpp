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
	groundTex_= Model::CreateObjModel("Resources/ground");
	buildingTex_ = Model::CreateObjModel("Resources/building");
	convenienceStoreTex_= Model::CreateObjModel("Resources/convenienceStore");
	tex_ = Model::CreateObjModel("Resources/purpleDice");
}

void GameLevelData::Load()
{
	std::unique_ptr<LevelData> levelData_ = std::make_unique<LevelData>();
	levelData_.reset(LevelEditor::LoadLevelEditorFile(fileName_));

	//���x���f�[�^����I�u�W�F�N�g�𐶐��A�z�u
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
			//����_��o�^
			cameraData_.controlPoints.push_back(objectData.translation);
		}
		else if (objectData.fileName == "normalEnemy")
		{
			std::unique_ptr<Enemy>enemy = std::make_unique<NormalEnemy>();
			enemy->SetPosition(objectData.translation);
			//blender��ƍ��W�n���኱����Ă���̂Ŏ኱�C�����đ���
			enemy->SetRotation({ myMath::ChangeRadians(objectData.rotation.x), myMath::ChangeRadians(objectData.rotation.y) + myMath::AX_PIF / 2, myMath::ChangeRadians(objectData.rotation.z) - myMath::AX_PIF / 2 });
			//���a����������Ηǂ��̂�x�̒l�̂ݑ���
			enemy->SetColliderSize(objectData.collider.size.x);
			//blender���Őݒ肵�����Ԃ𑗂�
			enemy->SetSpawnTimer(objectData.timer.spawnTimer);
			enemy->SetDeathTimer(objectData.timer.deathTimer);
			//Enemy��o�^
			enemyData_.enemys.push_back(std::move(enemy));
		}
		else if (objectData.fileName == "moveEnemy")
		{
			std::unique_ptr<Enemy>enemy = std::make_unique<MoveEnemy>();
			enemy->SetPosition(objectData.translation);
			//blender��ƍ��W�n���኱����Ă���̂Ŏ኱�C�����đ���
			enemy->SetRotation({ myMath::ChangeRadians(objectData.rotation.x), myMath::ChangeRadians(objectData.rotation.y) + myMath::AX_PIF / 2, myMath::ChangeRadians(objectData.rotation.z) - myMath::AX_PIF / 2 });
			//���a����������Ηǂ��̂�x�̒l�̂ݑ���
			enemy->SetColliderSize(objectData.collider.size.x);
			//blender���Őݒ肵�����Ԃ𑗂�
			enemy->SetSpawnTimer(objectData.timer.spawnTimer);
			enemy->SetDeathTimer(objectData.timer.deathTimer);
			//Enemy��o�^
			enemyData_.enemys.push_back(std::move(enemy));
		}
		else if (objectData.fileName == "ground")
		{
			//�t�@�C��������o�^�ς݃��f��������
			std::unique_ptr<EditorObject> model = std::make_unique<EditorObject>();
			model->Initialize();

			//���W
			model->SetPos(objectData.translation);
			//�g�k
			model->SetScale({ objectData.scaling.y ,objectData.scaling.x ,objectData.scaling.z });
			//���O
			model->SetName(objectData.fileName);

			model->SetModel(groundTex_);
			model->SetShader(ShaderMode::Phong);

			objects_.push_back(std::move(model));
		}
		else if (objectData.fileName == "building")
		{
			//�t�@�C��������o�^�ς݃��f��������
			std::unique_ptr<EditorObject> model = std::make_unique<EditorObject>();
			model->Initialize();

			//���W
			model->SetPos(objectData.translation);
			//�g�k
			model->SetScale(objectData.scaling);
			//���O
			model->SetName(objectData.fileName);

			model->SetModel(buildingTex_);
			model->SetShader(ShaderMode::Phong);

			objects_.push_back(std::move(model));
		}
		else if (objectData.fileName == "convenienceStore")
		{
			//�t�@�C��������o�^�ς݃��f��������
			std::unique_ptr<EditorObject> model = std::make_unique<EditorObject>();
			model->Initialize();

			//���W
			model->SetPos(objectData.translation);
			//��]�p
			//blender�ŏo�͂��ꂽ�l��ϊ�����
			model->SetRot({ myMath::ChangeRadians(objectData.rotation.x),myMath::ChangeRadians(objectData.rotation.y - 90.0f),myMath::ChangeRadians(objectData.rotation.z - 90.0f) });
			//�g�k
			model->SetScale(objectData.scaling);
			//���O
			model->SetName(objectData.fileName);

			model->SetModel(convenienceStoreTex_);
			model->SetShader(ShaderMode::Phong);

			objects_.push_back(std::move(model));
		}
		else
		{
			//�t�@�C��������o�^�ς݃��f��������
			std::unique_ptr<EditorObject> model = std::make_unique<EditorObject>();
			model->Initialize();

			//���W
			model->SetPos(objectData.translation);
			//��]�p
			model->SetRot(objectData.rotation);
			//�g�k
			model->SetScale(objectData.scaling);
			//���O
			model->SetName(objectData.fileName);
			//�R���C�_�[�̒��S���W
			model->SetColliderCenter(objectData.collider.center);
			//�R���C�_�[�T�C�Y
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
	//�폜���čēǂݍ���
	models_.clear();
	objects_.clear();
	cameraData_.controlPoints.clear();
	enemyData_.enemys.clear();
	Load();
}