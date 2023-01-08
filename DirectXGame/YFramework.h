#pragma once
#include"SceneManager.h"

//�Q�[���S��
class YFramework
{
private:

	SceneManager* sceneManager = nullptr;

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