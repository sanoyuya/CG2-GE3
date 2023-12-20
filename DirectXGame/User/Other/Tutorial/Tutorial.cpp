#include "Tutorial.h"
#include"Retention.h"

void Tutorial::Initialize(GameTimer* gameTimer)
{
	if (Retention::GetInstance()->GetStageNum() == 0)
	{
		gameTimer_ = gameTimer;

		TextInitialize();

		tutorialSkip_ = std::make_unique<TutorialSkip>();
		tutorialSkip_->Initialize(gameTimer_);
		tutorialSkip_->SetGameStartTime(78);
	}
}

void Tutorial::Update()
{
	if (Retention::GetInstance()->GetStageNum() == 0)
	{
		TextUpdate();

		tutorialSkip_->Update();
	}
}

void Tutorial::Draw()
{
	if (Retention::GetInstance()->GetStageNum() == 0)
	{
		for (uint8_t i = 0; i < textMaxNum_; i++)
		{
			text_[i]->Draw();
		}

		tutorialSkip_->Draw();
	}
}

void Tutorial::Rest()
{
	if (Retention::GetInstance()->GetStageNum() == 0)
	{
		tutorialSkip_->Reset();
	}
}

void Tutorial::TextInitialize()
{
	for (uint8_t i = 0; i < textMaxNum_; i++)
	{
		text_[i] = std::make_unique<Text>();
	}
	text_[static_cast<uint8_t>(TextName::MOVE)]->Initialize(TextName::MOVE);
	text_[static_cast<uint8_t>(TextName::ATTACK)]->Initialize(TextName::ATTACK);
	text_[static_cast<uint8_t>(TextName::CAMERAMOVE)]->Initialize(TextName::CAMERAMOVE);
	text_[static_cast<uint8_t>(TextName::CHARGEATTACK)]->Initialize(TextName::CHARGEATTACK);
	text_[static_cast<uint8_t>(TextName::READY)]->Initialize(TextName::READY);
	text_[static_cast<uint8_t>(TextName::GO)]->Initialize(TextName::GO);
}

void Tutorial::TextUpdate()
{
	text_[static_cast<uint8_t>(TextName::MOVE)]->Update(gameTimer_, 3, 7);//Blender上で設定できるようにしたい
	text_[static_cast<uint8_t>(TextName::ATTACK)]->Update(gameTimer_, 9, 13);
	text_[static_cast<uint8_t>(TextName::CAMERAMOVE)]->Update(gameTimer_, 20, 25);
	text_[static_cast<uint8_t>(TextName::CHARGEATTACK)]->Update(gameTimer_, 50, 55);
	text_[static_cast<uint8_t>(TextName::READY)]->Update(gameTimer_, 81, 84);
	text_[static_cast<uint8_t>(TextName::GO)]->Update(gameTimer_, 84, 86);
}