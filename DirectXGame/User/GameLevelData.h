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
	uint32_t tex_ = 0;

	PlayerData playerData_;
	CameraData cameraData_;
	EnemyData enemyData_;

public:

	GameLevelData();
	~GameLevelData();

	/// <summary>
	/// ‰Šú‰»ˆ—
	/// </summary>
	void Initialize(const std::string& fileName);

	/// <summary>
	/// XVˆ—
	/// </summary>
	/// <param name="camera"></param>
	void Update(Camera* camera);

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw();

	/// <summary>
	/// Ä“Ç‚İ‚İ
	/// </summary>
	void ReLoad();

private:

	void CreateModel();
	void Load();

public:

	const PlayerData& GetPlayerData();
	const CameraData& GetCameraData();
	EnemyData& GetEnemyData();
};