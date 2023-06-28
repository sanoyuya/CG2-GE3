#include "GameLevelData.h"

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
		if (object->GetName() == "player")
		{
			object->SetPos(pos_);
		}
		if (object->GetName() == "child")
		{
			object->SetPos({ pos_.x,object->GetPos().y,pos_.z });
		}
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

		if (objectData.fileName == "player")
		{
			model->SetModel(playerTex_);
			pos_ = model->GetPos();
		}
		else if (objectData.fileName == "sphere")
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

void GameLevelData::ReLoad()
{
	//削除して再読み込み
	models_.clear();
	objects_.clear();
	Load();
}