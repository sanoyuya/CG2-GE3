#include "PlayerDamageEffect.h"
#include"PostEffect.h"

PlayerDamageEffect::PlayerDamageEffect()
{
}

PlayerDamageEffect::~PlayerDamageEffect()
{
}

void PlayerDamageEffect::Update(Player* player)
{
	if (player->GetDamageFlag())
	{
		damageFlag_ = true;
		PostEffect::SetEffectMode(EffectMode::GaussianBlur);
		power_ = 5.0f;
		player->SetDamageFlag(false);
	}

	if (damageFlag_ == true)
	{
		if (power_ <= 0.0f)
		{
			power_ = 0.0f;
			damageFlag_ = false;
			PostEffect::SetEffectMode(EffectMode::None);
		}
		power_ -= 0.5f;
	}
	else
	{
		power_ = 0.0f;
	}
	PostEffect::SetPower(power_);
}