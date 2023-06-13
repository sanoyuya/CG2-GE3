#pragma once
#include"BaseScene.h"
#include"AbstractSceneFactory.h"

//シーン管理
class SceneManager
{
private:

	//現在のシーン
	std::unique_ptr<BaseScene> scene_;
	std::unique_ptr<BaseScene> nextScene_;

	//シーンファクトリー
	AbstractSceneFactory* sceneFactory_ = nullptr;

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