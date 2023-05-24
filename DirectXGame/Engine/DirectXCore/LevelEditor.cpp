#include "LevelEditor.h"
#include<json.hpp>
#include<fstream>

const std::string LevelEditor::defaultBaseDirectory = "Resources/levels/";
const std::string LevelEditor::extension = ".json";

LevelData* LevelEditor::LoadLevelEditorFile(const std::string& fileName)
{
	const std::string fullpath = defaultBaseDirectory + fileName + extension;

	// ファイルストリーム
	std::ifstream file;

	// ファイルを開く
	file.open(fullpath);
	// ファイルオープン失敗をチェック
	if (file.fail())
	{
		assert(0);
	}

	//json文字列から解凍したデータ
	nlohmann::json deserialized;

	//解凍
	file >> deserialized;

	//正しいレベルデータファイルかチェック
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());
	//"name"を文字列として取得
	std::string name = deserialized["name"].get<std::string>();
	//正しいレベルデータファイルかチェック
	assert(name.compare("scene") == 0);

	//レベルデータ格納用インスタンスを生成
	LevelData* levelData = new LevelData();

	//"objects"の全オブジェクトを走査
	for (nlohmann::json& object : deserialized["objects"])
	{
		assert(object.contains("type"));

		//種別を取得
		std::string type = object["type"].get<std::string>();

		//mesh
		if (type.compare("MESH") == 0) {

			//要素追加
			levelData->objects.emplace_back(LevelData::ObjectData{});
			//今追加した要素の参照を得る
			LevelData::ObjectData& objectData = levelData->objects.back();

			if (object.contains("file_name"))
			{
				// ファイル名
				objectData.fileName = object["file_name"];
			}

			//トランスフォームのパラメータ読み込み
			nlohmann::json& transform = object["transform"];

			//平行移動
			objectData.translation.x = static_cast<float>(transform["translation"][1]);
			objectData.translation.y = static_cast<float>(transform["translation"][2]);
			objectData.translation.z = -static_cast<float>(transform["translation"][0]);
			// 回転角
			objectData.rotation.x = -static_cast<float>(transform["rotation"][1]);
			objectData.rotation.y = -static_cast<float>(transform["rotation"][2]);
			objectData.rotation.z = static_cast<float>(transform["rotation"][0]);
			// スケーリング
			objectData.scaling.x = static_cast<float>(transform["scaling"][1]);
			objectData.scaling.y = static_cast<float>(transform["scaling"][2]);
			objectData.scaling.z = static_cast<float>(transform["scaling"][0]);

			//TODO: コライダーのパラメータ読み込み
		}

		// TODO: オブジェクト走査を再帰関数にまとめ、再帰呼出で枝を走査する
		if (object.contains("children")) {

		}
	}

	return levelData;
}