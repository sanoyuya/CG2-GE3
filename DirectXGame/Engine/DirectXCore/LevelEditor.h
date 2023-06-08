#pragma once
#include"myMath.h"
#include <vector>
#include <string>
#include<json.hpp>

//レベルデータ
struct LevelData {

	struct Collider
	{
		myMath::Vector3 center_;
		myMath::Vector3 size_;
	};

	struct ObjectData {
		//ファイル名
		std::string fileName_;
		//平行移動
		myMath::Vector3 translation_;
		//回転角
		myMath::Vector3 rotation_;
		//スケーリング
		myMath::Vector3 scaling_;
		//当たり判定
		Collider collider_;
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