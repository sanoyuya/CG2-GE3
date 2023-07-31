#pragma once
#include"InputManager.h"
#include"AudioManager.h"
#include"Camera.h"
#include"DrawOversight.h"
#include"BaseScene.h"
#include"Collision.h"
#include"LightManager.h"
#include"PostEffect.h"
#include"GameLevelData.h"
#include"EnemyManager.h"
#include"PlayerDamageEffect.h"
#include"Radar.h"

class GameScene :public BaseScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input_ = nullptr;
	AudioManager* audioManager_ = nullptr;

	std::unique_ptr<RailCamera>camera_;
	std::unique_ptr<LightManager>lightManager_;
	myMath::Vector3 lightPos_ = { 0.0f,0.0f ,0.0f };
	myMath::Vector3 lightColor_ = { 0.0f,0.0f ,0.0f };
	myMath::Vector3 lightAtten_ = { 0.0f,0.0f ,0.0f };

	//�V��
	std::unique_ptr<Model>skyDome_;
	Transform skyDomeTrans_;
	uint32_t skyDomeTex_;

	std::unique_ptr<GameLevelData> gameLevelData_;

	std::unique_ptr<Player>player_;
	std::unique_ptr<PlayerDamageEffect>playerDamageEffect_;

	std::unique_ptr<EnemyManager>enemyManager_;

	std::unique_ptr<Radar>radar_;

	uint32_t bgm_ = 0;

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