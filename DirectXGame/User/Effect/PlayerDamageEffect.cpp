#include "PlayerDamageEffect.h"
#include"MultiTexturePostEffect.h"

PlayerDamageEffect::PlayerDamageEffect()
{
}

PlayerDamageEffect::~PlayerDamageEffect()
{
}

void PlayerDamageEffect::Update(Player* player)
{
	if (damageFlag_ == false)
	{
		if (player->GetDamageFlag() && player->GetHp() > 1)
		{
			MultiTexturePostEffect::SetEffectMode(MultiTextureEffectMode::GaussianBlur);
			damageFlag_ = true;
			power_ = maxPower_;
		}
	}

	if (damageFlag_ == true)
	{
		if (power_ <= minPower_)
		{
			power_ = minPower_;
			player->SetDamageFlag(false);
			damageFlag_ = false;
			MultiTexturePostEffect::SetEffectMode(MultiTextureEffectMode::None);
		}
		power_ -= subPower_;
	}
	else
	{
		power_ = minPower_;
	}
	MultiTexturePostEffect::SetPower(power_);
}