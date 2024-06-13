#pragma once
#include"LevelEditor.h"
#include <map>
#include"EditorObject.h"
#include"Camera.h"
#include"GameTimer.h"

/// <summary>
/// jsonファイルから読み取ったデータからオブジェクトを配置するクラス
/// </summary>
class GameLevelData
{
private:

	GameTimer* gameTimer_ = nullptr;
	std::string fileName_ = {};

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
};