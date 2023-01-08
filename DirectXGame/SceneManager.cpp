#include "SceneManager.h"

void SceneManager::Update()
{
	//���V�[���̗\�񂪂���Ȃ�
	if (nextScene)
	{
		//���V�[���I��
		if (scene)
		{
			scene->Destroy();
			delete scene;
		}

		//�V�[���؂�ւ�
		scene = nextScene;
		nextScene = nullptr;

		//���V�[��������������
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