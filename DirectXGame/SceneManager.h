#pragma once
#include"BaseScene.h"
#include"AbstractSceneFactory.h"

//シーン管理
class SceneManager
{
private:

	//現在のシーン
	BaseScene* scene = nullptr;
	BaseScene* nextScene = nullptr;

	//シーンファクトリー
	AbstractSceneFactory* sceneFactory = nullptr;

public:

	//更新処理
	void Update();

	//描画処理
	void Draw();

	//終了処理
	void Destroy();

	//次シーン予約
	void ChangeScene(const std::string& sceneName);

	void SetSceneFactory(AbstractSceneFactory* sceneFactory);

	//シングルトン
	static SceneManager* GetInstance();

private:

	SceneManager() = default;
	~SceneManager() = default;

	//コピーコンストラクタ・代入演算子削除
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(const SceneManager&) = delete;
};