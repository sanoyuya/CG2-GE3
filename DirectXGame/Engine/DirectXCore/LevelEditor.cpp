#include"LevelEditor.h"
#include<fstream>

const std::string LevelEditor::sDefaultBaseDirectory_ = "Resources/levels/";
const std::string LevelEditor::sExtension_ = ".json";

LevelData* LevelEditor::LoadLevelEditorFile(const std::string& fileName)
{
	const std::string fullpath = sDefaultBaseDirectory_ + fileName + sExtension_;

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
		ObjectDataLoad(levelData, object);
	}

	return levelData;
}

void LevelEditor::ObjectDataLoad(LevelData* levelData, nlohmann::json& object)
{
	assert(object.contains("type"));

	//種別を取得
	std::string type = object["type"].get<std::string>();

	//mesh
	if (type.compare("MESH") == 0) {

		//要素追加
		levelData->objects_.emplace_back(LevelData::ObjectData{});
		//今追加した要素の参照を得る
		LevelData::ObjectData& objectData = levelData->objects_.back();

		if (object.contains("file_name"))
		{
			// ファイル名
			objectData.fileName_ = object["file_name"];
		}

		//トランスフォームのパラメータ読み込み
		nlohmann::json& transform = object["transform"];

		//平行移動
		objectData.translation_.x = static_cast<float>(transform["translation"][1]);
		objectData.translation_.y = static_cast<float>(transform["translation"][2]);
		objectData.translation_.z = -static_cast<float>(transform["translation"][0]);
		//回転角
		objectData.rotation_.x = -static_cast<float>(transform["rotation"][1]);
		objectData.rotation_.y = -static_cast<float>(transform["rotation"][2]);
		objectData.rotation_.z = static_cast<float>(transform["rotation"][0]);
		//スケーリング
		objectData.scaling_.x = static_cast<float>(transform["scaling"][1]);
		objectData.scaling_.y = static_cast<float>(transform["scaling"][2]);
		objectData.scaling_.z = static_cast<float>(transform["scaling"][0]);

		//コライダーのパラメータ読み込み
		nlohmann::json& collider = object["collider"];
		if (collider != nullptr)
		{
			//中心点
			objectData.collider_.center_.x = static_cast<float>(collider["center"][1]);
			objectData.collider_.center_.y = static_cast<float>(collider["center"][2]);
			objectData.collider_.center_.z = static_cast<float>(collider["center"][0]);
			//大きさ
			objectData.collider_.size_.x = static_cast<float>(collider["size"][1]);
			objectData.collider_.size_.y = static_cast<float>(collider["size"][2]);
			objectData.collider_.size_.z = static_cast<float>(collider["size"][0]);
		}
	}

	//オブジェクト走査を再帰関数にまとめ、再帰呼出で枝を走査する
	if (object.contains("children"))
	{
		for (nlohmann::json& object_ : object["children"])
		{
			ObjectDataLoad(levelData, object_);
		}
	}
}