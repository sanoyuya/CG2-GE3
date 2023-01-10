#include "Score.h"

void Score::Initialize()
{
	numberTex = number[0]->LoadTexture("Resources/number.png");
	for (int i = 0; i < 4; i++)
	{
		number[i] = std::make_unique<Sprite>();
		number[i]->Sprite2DInitialize(numberTex);
	}
}

void Score::Update()
{
	flameTimer++;
	if (flameTimer > 59)
	{
		nowTime++;
		flameTimer = 0;
	}

	if (nowTime >= 9999)
	{
		nowTime = 9999;
	}
}

void Score::Draw(myMath::Vector4 color, float shakeAdd)
{
	if (nowTime <= 9)nowTimeDigts = 1;
	else if (10 <= nowTime && nowTime < 100)nowTimeDigts = 2;
	else if (100 <= nowTime && nowTime < 1000)nowTimeDigts = 3;
	else nowTimeDigts = 4;

	timeDigts[0] = nowTime % 10;
	timeDigts[1] = nowTime / 10 % 10;
	timeDigts[2] = nowTime / 100 % 10;
	timeDigts[3] = nowTime / 1000;

	for (int i = 0; i < nowTimeDigts; i++)
	{
		number[i]->DrawAnimationSpriteX2D({ timePos.x - i * 32 + shakeAdd,timePos.y + shakeAdd }, 10, timeDigts[i], color);
	}
}

void Score::Reset()
{
	nowTime = 0;
	flameTimer = 0;
}

void Score::SetScorePos(const myMath::Vector2 scorePos)
{
	this->scorePos = scorePos;
}

void Score::SetTimePos(const myMath::Vector2 timePos)
{
	this->timePos = timePos;
}

Score* Score::GetInstance()
{
	static Score instance;
	return &instance;
}
