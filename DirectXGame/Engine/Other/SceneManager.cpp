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
			scene_ = nullptr;
		}

		//�V�[���؂�ւ�
		scene_ = nextScene_;
		nextScene_ = nullptr;

		//���V�[��������������
		scene_->Initialize();
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
	scene_ = nullptr;
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	assert(sceneFactory_);
	assert(nextScene_ == nullptr);

	//���V�[���𐶐�
	nextScene_ = sceneFactory_->CreateScene(sceneName);
}

void SceneManager::SetSceneFactory(AbstractSceneFactory* sceneFactory)
{
	sceneFactory_ = sceneFactory;
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}