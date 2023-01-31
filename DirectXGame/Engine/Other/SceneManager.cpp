#include "SceneManager.h"
#include<cassert>

void SceneManager::Update()
{
	//次シーンの予約があるなら
	if (nextScene)
	{
		//旧シーン終了
		if (scene)
		{
			scene->Destroy();
			delete scene;
		}

		//シーン切り替え
		scene = nextScene;
		nextScene = nullptr;

		//次シーンを初期化する
		scene->Initialize();
	}

	scene->Update();
}

void SceneManager::Draw()
{
	scene->Draw();
}

void SceneManager::Destroy()
{
	scene->Destroy();
	delete scene;
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	assert(sceneFactory);
	assert(nextScene == nullptr);

	//次シーンを生成
	nextScene = sceneFactory->CreateScene(sceneName);
}

void SceneManager::SetSceneFactory(AbstractSceneFactory* sceneFactory_)
{
	sceneFactory = sceneFactory_;
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}