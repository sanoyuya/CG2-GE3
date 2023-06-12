#pragma once
#include"YFramework.h"
#include"AbstractSceneFactory.h"

//�Q�[���S��
class MyGame :public YFramework
{
private:

	//�V�[���t�@�N�g���[
	std::unique_ptr<AbstractSceneFactory>sceneFactory_;

public:

	//����������
	void Initialize()override;

	//�I������
	void Destroy()override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;
};