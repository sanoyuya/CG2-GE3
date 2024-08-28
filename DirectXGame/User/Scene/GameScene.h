#pragma once
#include"DrawOversight.h"
#include"BaseScene.h"
#include"myMath.h"
#include"GameTimer.h"
#include"InputManager.h"

enum class Mode
{
	START,
	GAME,
	END,
	RESULT
};

struct Ranking
{
	int score;
	std::string name;
};

class GameScene:public BaseScene
{
private:

	//クラス読み込み
	InputManager* input_ = nullptr;

	std::unique_ptr<GameTimer>gameTimer_;

	Mode modeFlag_ = Mode::START;

	float alpha_ = 1.0f;

	uint32_t time_ = 0;
	std::array<std::unique_ptr<Sprite2D>, 3>timeSprite_;//整数用
	uint32_t numberTex_ = 0;
	uint8_t timeDig_ = 1;
	char timeStrNum[3];

	std::unique_ptr<Sprite2D>period;
	uint32_t periodTex_ = 0;

	std::array<std::unique_ptr<Sprite2D>, 7>time2Sprite_;//小数点以下用
	uint8_t maxDig_ = 6;
	char time2StrNum[6];

	std::array<std::unique_ptr<Sprite2D>, 7>scoreSprite_;//トータルスコア用

	uint8_t scoreDig_ = 1;
	int32_t score_ = 0;
	char scoreStrNum_[7];

	//通信関係
	bool isConect_ = false;
	bool isLogin_ = false;

	Ranking rank_[5];
	std::wstring token_;

public:

	//初期化処理
	void Initialize()override;

	//終了処理
	void Destroy()override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;

private:

	void DigitCalculation(uint32_t num, uint8_t& digit);
};