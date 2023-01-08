#pragma once
#include"BaseScene.h"

//�V�[���Ǘ�
class SceneManager
{
private:

	//���݂̃V�[��
	BaseScene* scene = nullptr;
	BaseScene* nextScene = nullptr;

public:

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();

	//�I������
	void Destroy();

	//���V�[���\��
	void SetNextScene(BaseScene* nextScene);

	//�V���O���g��
	static SceneManager* GetInstance();

private:

	SceneManager() = default;
	~SceneManager() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(const SceneManager&) = delete;
};