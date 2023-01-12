#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include<memory>
#include"Camera.h"
#include"DrawOversight.h"
#include"Transform.h"
#include"Sprite.h"
#include"Player.h"
#include"Enemy.h"
#include"BackDice.h"
#include"BaseScene.h"
#include"SceneManager.h"
#include"Score.h"
#include"OmnidirectionalBulletEnemy.h"

class GameScene :public BaseScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	SceneManager* sceneManager = nullptr;
	AudioManager* audioManager = nullptr;
	Score* score = nullptr;

	std::unique_ptr<Camera>camera;

	myMath::Vector3 cameraPos;
	float angleX = 0.0f;
	float angleY = 0.0f;
	const float length = 42.5f;
	float zoomLengthX = 0.0f;
	float zoomLengthY = 0.0f;
	float zoomLengthZ = 0.0f;

	//�V��
	std::unique_ptr<DrawOversight>model;
	Transform modelTrans;
	uint32_t modelTex = 0;

	//�w�i
	std::unique_ptr<Sprite>backSprite;
	Transform backSpriteTrans;
	uint32_t backSpriteTex = 0;

	std::unique_ptr<Sprite>backLeftSprite;
	Transform backLeftSpriteTrans;

	std::unique_ptr<Sprite>backRightSprite;
	Transform backRightSpriteTrans;
	
	float colorR = 0.0f;
	float colorG = 0.0f;
	float colorB = 0.0f;
	float colorTime = 0.0f;

	std::unique_ptr<Sprite>shadowSprite;
	Transform shadowSpriteTrans;
	uint32_t shadowSpriteTex = 0;

	std::list<std::unique_ptr<BackDice>>backDices;
	uint32_t backDiceTex;
	float backDiceCoolTime = 0.0f;

	uint8_t scene = 0;

	std::unique_ptr<Player>player;

	//�G���X�g
	std::list<std::unique_ptr<Enemy>> enemys;
	float coolTime = 0.0f;

	std::list<std::unique_ptr<OmnidirectionalBulletEnemy>> omnidirectionalBulletEnemys;
	float omnidirectionalBulletEnemyCoolTime = 0.0f;

	std::unique_ptr<Sprite>operation;
	uint32_t operationTex = 0;

	uint32_t gameBGM = 0;

public:

	//����������
	void Initialize()override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;

	//�I������
	void Destroy()override;

private:
	void Rotation();
	void CamMove();
	void BackDiceDead();
	void BackDiceUpdate();
	void BackDiceDraw();
	void EnemyDead();
	void EnemyUpdate();
	void EnemyDraw();
	void Reset();
};