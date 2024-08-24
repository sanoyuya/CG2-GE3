#include "Player.h"
#include <algorithm>
#include <imgui.h>

void Player::Initialize()
{
	input_ = InputManager::GetInstance();
}

void Player::Update()
{
	BoardSelect();
}

void Player::Draw()
{
}

void Player::BoardSelect()
{
	if (input_->KeyboardTriggerPush(DIK_RIGHT))
	{
		heightNum_++;
	}
	else if (input_->KeyboardTriggerPush(DIK_LEFT))
	{
		heightNum_--;
	}
	if (input_->KeyboardTriggerPush(DIK_UP))
	{
		widthNum_--;
	}
	else if (input_->KeyboardTriggerPush(DIK_DOWN))
	{
		widthNum_++;
	}
	heightNum_ = std::clamp(heightNum_, cMinNum_, cMaxNum_);
	widthNum_ = std::clamp(widthNum_, cMinNum_, cMaxNum_);

	nowNum_ = heightNum_ + widthNum_ * 3 + 1;
}