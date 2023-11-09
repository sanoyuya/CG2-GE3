#pragma once
#include"myMath.h"
#include <vector>
#include <string>
#include<json.hpp>
#include"Enemy.h"

//レベルデータ
struct LevelData {

	struct Collider
	{
		myMath::Vector3 center;
		myMath::Vector3 size;
	};

	struct Timer
	{
		float spawnTimer;
		float deathTimer;
	};

	struct ObjectData {
		//ファイル名
		std::string fileName;
		//オブジェクト名
		std::string objectName;
		//平行移動
		myMath::Vector3 translation;
		//回転角
		myMath::Vector3 rotation;
		//スケーリング
		myMath::Vector3 scaling;
		//当たり判定
		Collider collider;
		//タイマー
		Timer timer;
		//敵のプロパティ
		MoveEnemyProperty enemyProperty;
	};

	// オブジェクト配列
	std::vector<ObjectData> objects_;
};

class LevelEditor
{
public:
	//デフォルトの読み込みディレクトリ
	static const std::string sDefaultBaseDirectory_;
	//ファイル拡張子
	static const std::string sExtension_;

public:

	/// <summary>
	/// jsonファイルの読み込み
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	/// <returns></returns>
	static LevelData* LoadLevelEditorFile(const std::string& fileName);

private:

	static void ObjectDataLoad(LevelData* levelData, nlohmann::json& object);
};