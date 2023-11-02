#pragma once
#include"LevelEditor.h"
#include <map>
#include"EditorObject.h"
#include"Camera.h"
#include"Player.h"
#include"RailCamera.h"
#include"EnemyManager.h"

class GameLevelData
{
private:

	std::string fileName_ = {};

	std::map<std::string, EditorObject*>models_;
	std::vector<std::unique_ptr<EditorObject>>objects_;

	myMath::Vector3 pos_;

	uint32_t playerTex_ = 0;
	uint32_t sphereTex_ = 0;
	uint32_t groundTex_ = 0;
	uint32_t groundTex2_ = 0;
	uint32_t buildingTex_ = 0;
	uint32_t convenienceStoreTex_ = 0;
	uint32_t tex_ = 0;

	PlayerData playerData_;
	CameraData cameraData_;
	EnemyList enemyData_;

public:

	GameLevelData();
	~GameLevelData();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(const std::string& fileName);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="camera"></param>
	void Update(Camera* camera);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 再読み込み
	/// </summary>
	void ReLoad();

private:

	void CreateModel();
	void Load();

public:

	const PlayerData& GetPlayerData();
	const CameraData& GetCameraData();
	EnemyList& GetEnemyData();

	void SetFileName(const std::string& fileName);
};