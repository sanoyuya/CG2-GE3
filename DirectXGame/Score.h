#pragma once
#include"DrawOversight.h"

class Score
{
private:

	uint16_t flameTimer = 0;
	uint16_t nowTime = 0;

	uint32_t numberTex = 0;
	std::array<std::unique_ptr<Sprite>, 4>number;

	std::array<uint16_t, 4> timeDigts = { 0 };//4桁
	int nowTimeDigts = 0;
	myMath::Vector2 scorePos = { 0.0f,0.0f };
	myMath::Vector2 timePos = { 0.0f,0.0f };

public:

	void Initialize();
	void Update();
	void Draw(myMath::Vector4 color,float shakeAdd);
	void Reset();

	//ゲッター

	//セッター
	void SetScorePos(const myMath::Vector2 scorePos);
	void SetTimePos(const myMath::Vector2 timePos);

	//シングルトン
	static Score* GetInstance();

private:

	Score() = default;
	~Score() = default;

	//コピーコンストラクタ・代入演算子削除
	Score& operator=(const Score&) = delete;
	Score(const Score&) = delete;
};