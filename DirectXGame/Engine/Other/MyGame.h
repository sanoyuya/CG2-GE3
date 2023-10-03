#pragma once
#include"YFramework.h"
#include"AbstractSceneFactory.h"
#include"MultiTexturePostEffect.h"

//�Q�[���S��
class MyGame :public YFramework
{
private:

	//�V�[���t�@�N�g���[
	std::unique_ptr<AbstractSceneFactory>sceneFactory_;

	//�|�X�g�G�t�F�N�g
	std::unique_ptr<MultiTexturePostEffect>postEffect_;

public:

	//����������
	void Initialize()override;

	//�I������
	void Destroy()override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void SceneDraw()override;
	void PostEffectDraw()override;
};