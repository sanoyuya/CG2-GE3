#include "GameLevelData.h"

GameLevelData::GameLevelData()
{
}

GameLevelData::~GameLevelData()
{
}

void GameLevelData::Initialize()
{
	CreateModel();
	Load();
}

void GameLevelData::Update(Camera* camera)
{
	camera;
	/*for (auto& object : objects_)
	{
		object->Update(camera);
	}*/
}

void GameLevelData::Draw()
{
	/*for (auto& object : objects_)
	{
		object->Draw();
	}*/
}

void GameLevelData::CreateModel()
{
	
}

void GameLevelData::Load()
{
	std::unique_ptr<LevelData> levelData_ = std::make_unique<LevelData>();
	levelData_.reset(LevelEditor::LoadLevelEditorFile(fileName_));

	//レベルデータからオブジェクトを生成、配置
	for (auto& objectData : levelData_->objects_)
	{
		if (objectData.fileName == "GameManager")
		{
			gameTimer_->SetGameTime(static_cast<uint32_t>(objectData.timer.deathTimer));
		}
	}
}

void GameLevelData::ReLoad()
{
	//削除して再読み込み
	
	Load();
}

void GameLevelData::SetGameTimer(GameTimer* gameTimer)
{
	gameTimer_ = gameTimer;
}