#include "SceneManager.h"

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

void SceneManager::SetNextScene(BaseScene* nextScene)
{
	this->nextScene = nextScene;
}

void SceneManager::SetSceneFactory(AbstractSceneFactory* sceneFactory)
{
	this->sceneFactory = sceneFactory;
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}