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

class GameScene
{
private:

	//クラス読み込み
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Camera>camera;

	myMath::Vector3 cameraPos;
	float angleX = 0.0f;
	float angleY = 0.0f;
	const float length = 42.5f;

	//天球
	std::unique_ptr<DrawOversight>model;
	Transform modelTrans;
	uint32_t modelTex;

	//背景
	std::unique_ptr<Sprite>backSprite;
	Transform backSpriteTrans;
	uint32_t backSpriteTex;

	std::unique_ptr<Sprite>backLeftSprite;
	Transform backLeftSpriteTrans;
	uint32_t backLeftSpriteTex;

	std::unique_ptr<Sprite>backRightSprite;
	Transform backRightSpriteTrans;
	uint32_t backRightSpriteTex;
	float colorR = 0.0f;
	float colorG = 0.0f;
	float colorB = 0.0f;
	float colorTime = 0.0f;

	std::unique_ptr<Sprite>shadowSprite;
	Transform shadowSpriteTrans;
	uint32_t shadowSpriteTex;

	std::list<std::unique_ptr<BackDice>>backDices;
	uint32_t backDiceTex;
	float backDiceCoolTime = 0.0f;

	uint8_t scene = 0;

	std::unique_ptr<Player>player;

	uint32_t enemyTex;
	//敵リスト
	std::list<std::unique_ptr<Enemy>> enemys;
	float coolTime = 0.0f;

public:
	GameScene();
	~GameScene();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

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