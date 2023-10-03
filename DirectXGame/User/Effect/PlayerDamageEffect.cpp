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
		power_ = 10.0f;
		player->SetDamageFlag(false);
	}

	if (damageFlag_ == true)
	{
		if (power_ <= 0.0f)
		{
			power_ = 0.0f;
			damageFlag_ = false;
			MultiTexturePostEffect::SetEffectMode(MultiTextureEffectMode::None);
		}
		power_ -= 0.5f;
	}
	else
	{
		power_ = 0.0f;
	}
	MultiTexturePostEffect::SetPower(power_);
}