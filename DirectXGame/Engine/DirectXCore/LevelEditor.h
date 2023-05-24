#pragma once
#include"myMath.h"
#include <vector>
#include <string>

//レベルデータ
struct LevelData {

	struct ObjectData {
		// ファイル名
		std::string fileName;
		// 平行移動
		myMath::Vector3 translation;
		// 回転角
		myMath::Vector3 rotation;
		// スケーリング
		myMath::Vector3 scaling;
	};

	// オブジェクト配列
	std::vector<ObjectData> objects;
};

class LevelEditor
{
public:
	//デフォルトの読み込みディレクトリ
	static const std::string defaultBaseDirectory;
	//ファイル拡張子
	static const std::string extension;

public:

	/// <summary>
	/// jsonファイルの読み込み
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	/// <returns></returns>
	static LevelData* LoadLevelEditorFile(const std::string& fileName);
};