#include "BackDice.h"

void BackDice::Initialize(const myMath::Vector3 position, const uint16_t num)
{
    backDice = std::make_unique<Sprite>();
    backDiceTex = backDice->LoadTexture("Resources/backDice.png");
    backDice->Sprite3DInitialize(backDiceTex);
    backDiceTrans.Initialize();
    backDiceTrans.translation = position;
    backDiceTrans.scale = { 1.0f / 50.0f ,1.0f / 50.0f ,1.0f };
    backDiceTrans.rotation.x = myMath::AX_PI / 2;
    speed = static_cast<float>(myMath::GetRand(0.1f, 0.25f));
    rotSpeed = static_cast<float>(myMath::GetRand(-0.02f, 0.02f));
    diceNum = num;
}

void BackDice::Update(Camera* camera)
{
    backDiceTrans.translation.z -= speed;
    backDiceTrans.rotation.y += rotSpeed;

    backDiceTrans.TransUpdate(camera);

    if (backDiceTrans.translation.z <= -25)
    {
        isDead = true;
    }
}

void BackDice::Draw(Camera* camera, myMath::Vector4 color)
{
    backDice->DrawAnimationSpriteX3D(camera, backDiceTrans, 6, diceNum, BillboardFlag::NonBillboard, color);
}

bool BackDice::GetIsDead()
{
    return isDead;
}