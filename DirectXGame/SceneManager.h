#pragma once
#include"BaseScene.h"
#include"AbstractSceneFactory.h"
#include"SceneChangeAnimation.h"
#include"Score.h"

//�V�[���Ǘ�
class SceneManager
{
private:

	//���݂̃V�[��
	BaseScene* scene = nullptr;
	BaseScene* nextScene = nullptr;

	//�V�[���t�@�N�g���[
	AbstractSceneFactory* sceneFactory = nullptr;

public:

	//����������
	void Initialize();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();

	//�I������
	void Destroy();

	//���V�[���\��
	void SetNextScene(BaseScene* nextScene);

	void SetSceneFactory(AbstractSceneFactory* sceneFactory);

	//�V���O���g��
	static SceneManager* GetInstance();

private:

	SceneManager() = default;
	~SceneManager() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(const SceneManager&) = delete;
};