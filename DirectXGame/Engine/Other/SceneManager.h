#pragma once
#include"BaseScene.h"
#include"AbstractSceneFactory.h"

//�V�[���Ǘ�
class SceneManager
{
private:

	//���݂̃V�[��
	std::unique_ptr<BaseScene> scene_;
	std::unique_ptr<BaseScene> nextScene_;

	//�V�[���t�@�N�g���[
	AbstractSceneFactory* sceneFactory_ = nullptr;

	//�V�[���̖��O
	std::string sceneName_;
	std::string nextSceneName_;

public:

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();

	//�I������
	void Destroy();

	//���V�[���\��
	void ChangeScene(const std::string& sceneName);

	void SetSceneFactory(AbstractSceneFactory* sceneFactory);

	std::string GetSceneName();

	//�V���O���g��
	static SceneManager* GetInstance();

private:

	SceneManager() = default;
	~SceneManager() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(const SceneManager&) = delete;
};