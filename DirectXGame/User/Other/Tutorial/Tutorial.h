#pragma once
#include"Text.h"
#include"TutorialSkip.h"
#include"GameTimer.h"

/// <summary>
/// チュートリアルを管理するクラス
/// </summary>
class Tutorial
{
private:

	GameTimer* gameTimer_ = nullptr;

	const uint8_t textMaxNum_ = 6;
	std::array<std::unique_ptr<Text>, 6>text_;

	std::unique_ptr<TutorialSkip>tutorialSkip_;

public:

	//初期化処理
	void Initialize(GameTimer* gameTimer);
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//リセット
	void Rest();

private:

	void TextInitialize();

	void TextUpdate();
};