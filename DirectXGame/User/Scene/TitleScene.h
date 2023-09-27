#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"DrawOversight.h"
#include"Camera.h"
#include"AudioManager.h"
#include"LightManager.h"
#include"PlayerEngineSmokeParticleEmitter.h"

//�^�C�g���V�[��
class TitleScene :public BaseScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input_ = nullptr;
	AudioManager* audioManager_ = nullptr;
	std::unique_ptr<LightManager>lightManager_;

	std::unique_ptr<Camera>camera_;

	//�V��
	std::unique_ptr<Model>skyDome_;
	Transform skyDomeTrans_;
	uint32_t skyDomeTex_;

	myMath::Vector3 cameraPos_;

	uint32_t bgm_ = 0;

	uint32_t titleTex_ = 0;
	std::unique_ptr<Sprite>title_;

	uint32_t pressButtonTex_ = 0;
	std::unique_ptr<Sprite>pressButton_;

	float time_ = 0.0f;
	myMath::Vector2 position_ = { 640.0f,0.0f };

	std::unique_ptr<Model>player_;
	Transform playerTrans_;
	uint32_t playerTex_;

	std::unique_ptr<PlayerEngineSmokeParticleEmitter>smokeEmitter_;
	Transform smokeTrans_;

	bool animationFlag_ = false;
	uint8_t animationTime_ = 0;

	uint32_t animationBoxTex_ = 0;
	std::array<std::unique_ptr<Sprite>,2>animationBox_;
	float animationBoxScale_ = 0.0f;

	std::array<std::unique_ptr<Model>, 5>cloud_;
	std::array<Transform, 5>cloudTrans_;
	uint32_t cloudTex_ = 0;

public:

	//����������
	void Initialize()override;

	//�I������
	void Destroy()override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;

private:

	void SmokeUpdate();

	void PlayerUpdate();
};