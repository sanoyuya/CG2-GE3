#pragma once
#include"LevelEditor.h"
#include <map>
#include"EditorObject.h"
#include"Camera.h"
#include"Player.h"
#include"RailCamera.h"
#include"EnemyManager.h"
#include"BuildingManager.h"
#include"GameTimer.h"

/// <summary>
/// jsonファイルから読み取ったデータからオブジェクトを配置するクラス
/// </summary>
class GameLevelData
{
private:

	GameTimer* gameTimer_ = nullptr;
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
	uint32_t skydomeTex_ = 0;

	myMath::Vector2 groundTranslation_ = {};
	myMath::Vector2 groundSize_ = {};

	PlayerData playerData_;
	CameraData cameraData_;
	EnemyList enemyData_;
	BuildingList buildingData_;

public:

	GameLevelData();
	~GameLevelData();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

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

	/// <summary>
	/// ゲームタイマーのセット
	/// </summary>
	/// <param name="gameTimer">ゲームタイマーのポインタ</param>
	void SetGameTimer(GameTimer* gameTimer);

private:

	void CreateModel();
	void Load();
	void ConvertToString();

public:

	const PlayerData& GetPlayerData();
	const CameraData& GetCameraData();
	EnemyList& GetEnemyData();
	BuildingList& GetBuildingList();

	static bool NumericStringCompare(const ControlPoint& a, const ControlPoint& b);

	void SetFileName(const std::string& fileName);

	const myMath::Vector2 GetGroundSize();
	const myMath::Vector2 GetGroundTranslation();
};