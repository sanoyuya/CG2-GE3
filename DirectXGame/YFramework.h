#pragma once
#include"SceneManager.h"
#include"AbstractSceneFactory.h"
#include<memory>

//�Q�[���S��
class YFramework
{
private:

	SceneManager* sceneManager = nullptr;
	//�V�[���t�@�N�g���[
	std::unique_ptr<AbstractSceneFactory>sceneFactory;

public:

	virtual ~YFramework() = default;

	//����������
	virtual void Initialize();

	//�I������
	virtual void Destroy();

	//�X�V����
	virtual void Update();

	//�`�揈��
	virtual void Draw() = 0;

	//���s����
	void Run();
};