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
			objectData.fileName = object["file_name"];
		}

		//トランスフォームのパラメータ読み込み
		nlohmann::json& transform = object["transform"];

		//平行移動
		objectData.translation.x = static_cast<float>(transform["translation"][1]);
		objectData.translation.y = static_cast<float>(transform["translation"][2]);
		objectData.translation.z = -static_cast<float>(transform["translation"][0]);
		//回転角
		objectData.rotation.x = -static_cast<float>(transform["rotation"][1]);
		objectData.rotation.y = -static_cast<float>(transform["rotation"][2]);
		objectData.rotation.z = static_cast<float>(transform["rotation"][0]);
		//スケーリング
		objectData.scaling.x = static_cast<float>(transform["scaling"][1]);
		objectData.scaling.y = static_cast<float>(transform["scaling"][2]);
		objectData.scaling.z = static_cast<float>(transform["scaling"][0]);

		//コライダーのパラメータ読み込み
		nlohmann::json& collider = object["collider"];
		if (collider != nullptr)
		{
			//中心点
			objectData.collider.center.x = static_cast<float>(collider["center"][1]);
			objectData.collider.center.y = static_cast<float>(collider["center"][2]);
			objectData.collider.center.z = static_cast<float>(collider["center"][0]);
			//大きさ
			objectData.collider.size.x = static_cast<float>(collider["size"][1]);
			objectData.collider.size.y = static_cast<float>(collider["size"][2]);
			objectData.collider.size.z = static_cast<float>(collider["size"][0]);
		}

		//タイマーのパラメータ読み込み
		nlohmann::json& timer = object["timer"];
		if (timer != nullptr)
		{
			//出現時間
			objectData.timer.spawnTimer = static_cast<float>(timer["spawn"]);
			//死亡時間
			objectData.timer.deathTimer = static_cast<float>(timer["death"]);
		}

		//敵情報のパラメータ読み込み
		nlohmann::json& enemyProperty = object["enemy_move_properties"];
		if (enemyProperty != nullptr)
		{
			//出現地点
			objectData.enemyProperty.spawnPos.x = static_cast<float>(enemyProperty["spawnPosition"][1]);
			objectData.enemyProperty.spawnPos.y = static_cast<float>(enemyProperty["spawnPosition"][2]);
			objectData.enemyProperty.spawnPos.z = -static_cast<float>(enemyProperty["spawnPosition"][0]);
			objectData.enemyProperty.spawnPosRotation.x = static_cast<float>(enemyProperty["spawnPositionRotation"][1]);
			objectData.enemyProperty.spawnPosRotation.y = -static_cast<float>(enemyProperty["spawnPositionRotation"][2]);
			objectData.enemyProperty.spawnPosRotation.z = static_cast<float>(enemyProperty["spawnPositionRotation"][0]);

			//移動地点に向かうまでの時間
			objectData.enemyProperty.toMovePosTime = static_cast<float>(enemyProperty["toMovePositionTime"]);

			//移動地点の座標
			objectData.enemyProperty.movePos.x = static_cast<float>(enemyProperty["movePosition"][1]);
			objectData.enemyProperty.movePos.y = static_cast<float>(enemyProperty["movePosition"][2]);
			objectData.enemyProperty.movePos.z = -static_cast<float>(enemyProperty["movePosition"][0]);
			objectData.enemyProperty.movePosRotation.x = static_cast<float>(enemyProperty["movePositionRotation"][1]);
			objectData.enemyProperty.movePosRotation.y = -static_cast<float>(enemyProperty["movePositionRotation"][2]);
			objectData.enemyProperty.movePosRotation.z = static_cast<float>(enemyProperty["movePositionRotation"][0]);

			//移動地点での待機時間
			objectData.enemyProperty.waitTime = static_cast<float>(enemyProperty["waitTime"]);

			//逃走地点に向かうまでの時間
			objectData.enemyProperty.toEscapePosTime= static_cast<float>(enemyProperty["toEscapePositionTime"]);

			//逃走地点
			objectData.enemyProperty.escapePos.x = static_cast<float>(enemyProperty["escapePosition"][1]);
			objectData.enemyProperty.escapePos.y = static_cast<float>(enemyProperty["escapePosition"][2]);
			objectData.enemyProperty.escapePos.z = -static_cast<float>(enemyProperty["escapePosition"][0]);
			objectData.enemyProperty.escapePosRotation.x = static_cast<float>(enemyProperty["escapePositionRotation"][1]);
			objectData.enemyProperty.escapePosRotation.y = -static_cast<float>(enemyProperty["escapePositionRotation"][2]);
			objectData.enemyProperty.escapePosRotation.z = static_cast<float>(enemyProperty["escapePositionRotation"][0]);
		}
	}
	else if (type.compare("CAMERA") == 0)
	{
		//要素追加
		levelData->objects_.emplace_back(LevelData::ObjectData{});
		//今追加した要素の参照を得る
		LevelData::ObjectData& objectData = levelData->objects_.back();

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
		//回転角
		objectData.rotation.x = -static_cast<float>(transform["rotation"][1]);
		objectData.rotation.y = -static_cast<float>(transform["rotation"][2]);
		objectData.rotation.z = static_cast<float>(transform["rotation"][0]);
		//スケーリング
		objectData.scaling.x = static_cast<float>(transform["scaling"][1]);
		objectData.scaling.y = static_cast<float>(transform["scaling"][2]);
		objectData.scaling.z = static_cast<float>(transform["scaling"][0]);

		//コライダーのパラメータ読み込み
		nlohmann::json& collider = object["collider"];
		if (collider != nullptr)
		{
			//中心点
			objectData.collider.center.x = static_cast<float>(collider["center"][1]);
			objectData.collider.center.y = static_cast<float>(collider["center"][2]);
			objectData.collider.center.z = static_cast<float>(collider["center"][0]);
			//大きさ
			objectData.collider.size.x = static_cast<float>(collider["size"][1]);
			objectData.collider.size.y = static_cast<float>(collider["size"][2]);
			objectData.collider.size.z = static_cast<float>(collider["size"][0]);
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