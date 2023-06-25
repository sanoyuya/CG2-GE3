#pragma once
#include"YFramework.h"
#include"AbstractSceneFactory.h"
#include"PostEffect.h"
#include"MultiRenderPostEffect.h"
#include"MultiTexturePostEffect.h"

//�Q�[���S��
class MyGame :public YFramework
{
private:

	//�V�[���t�@�N�g���[
	std::unique_ptr<AbstractSceneFactory>sceneFactory_;

	//�|�X�g�G�t�F�N�g
	std::unique_ptr<PostEffect>postEffect_;
	std::unique_ptr<MultiRenderPostEffect>multiRenderPostEffect_;
	std::unique_ptr<MultiTexturePostEffect>multiTexturePostEffect_;

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