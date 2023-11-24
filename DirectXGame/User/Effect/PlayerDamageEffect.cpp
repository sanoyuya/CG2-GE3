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
	if (player->GetDamageFlag() && player->GetHp() > 1)
	{
		damageFlag_ = true;
		MultiTexturePostEffect::SetEffectMode(MultiTextureEffectMode::GaussianBlur);
		power_ = maxPower_;
		player->SetDamageFlag(false);
	}

	if (damageFlag_ == true)
	{
		if (power_ <= minPower_)
		{
			power_ = minPower_;
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