#pragma once
#include"DrawOversight.h"

class Score
{
private:

	uint32_t numberTex = 0;

	uint16_t flameTimer = 0;
	uint16_t nowTime = 0;
	std::array<std::unique_ptr<Sprite>, 4>timeSprite;
	std::array<uint16_t, 4> timeDigts = { 0 };//4桁
	int nowTimeDigts = 0;
	myMath::Vector2 timePos = { 0.0f,0.0f };

	uint16_t enemyKillNum = 0;
	int nowEnemyKillNumDigts = 0;
	std::array<std::unique_ptr<Sprite>, 6>enemyKillNumSprite;//6桁
	std::array<uint16_t, 6> enemyKillNumDigts = { 0 };//6桁
	myMath::Vector2 enemyKillNumPos = { 0.0f,0.0f };

	std::unique_ptr<Sprite>kill;
	uint16_t killTex = 0;

	std::unique_ptr<Sprite>time;
	uint16_t timeTex = 0;

	uint16_t score = 0;

public:

	void Initialize();
	void Update();
	void TimeDraw(myMath::Vector4 color, float shakeAdd);
	void EnemyKillNumDraw(myMath::Vector4 color, float shakeAdd);
	void EnemyKillAdd();
	void Reset();

	//ゲッター

	//セッター
	void SetTimePos(const myMath::Vector2 timePos);
	void SetEnemyKillNumSpritePos(const myMath::Vector2 scorePos);

	//シングルトン
	static Score* GetInstance();

private:

	Score() = default;
	~Score() = default;

	//コピーコンストラクタ・代入演算子削除
	Score& operator=(const Score&) = delete;
	Score(const Score&) = delete;
};