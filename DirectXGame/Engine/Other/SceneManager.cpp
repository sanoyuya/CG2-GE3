#include "SceneManager.h"
#include<cassert>

void SceneManager::Update()
{
	//���V�[���̗\�񂪂���Ȃ�
	if (nextScene_)
	{
		//���V�[���I��
		if (scene_)
		{
			scene_->Destroy();
			scene_.reset();
		}

		//�V�[���؂�ւ�
		scene_ = std::move(nextScene_);

		//���V�[��������������
		scene_->Initialize();

		//�V�[���̖��O��ύX
		sceneName_ = nextSceneName_;
	}

	scene_->Update();
}

void SceneManager::Draw()
{
	scene_->Draw();
}

void SceneManager::Destroy()
{
	scene_->Destroy();
	scene_.reset();
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	assert(sceneFactory_);
	assert(nextScene_ == nullptr);

	//���V�[���𐶐�
	nextScene_ = sceneFactory_->CreateScene(sceneName);
	nextSceneName_ = sceneName;
}

void SceneManager::SetSceneFactory(AbstractSceneFactory* sceneFactory)
{
	sceneFactory_ = sceneFactory;
}

std::string SceneManager::GetSceneName()
{
	return sceneName_;
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}