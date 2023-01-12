#include "Score.h"

void Score::Initialize()
{
	if (initializeFlag == false)
	{
		numberTex = timeSprite[0]->LoadTexture("Resources/number.png");
		for (int i = 0; i < 4; i++)
		{
			timeSprite[i] = std::make_unique<Sprite>();
			timeSprite[i]->Sprite2DInitialize(numberTex);
		}

		for (int i = 0; i < 6; i++)
		{
			enemyKillNumSprite[i] = std::make_unique<Sprite>();
			enemyKillNumSprite[i]->Sprite2DInitialize(numberTex);
		}

		initializeFlag = true;
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

void Score::TimeDraw(myMath::Vector4 color, float shakeAdd)
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
		timeSprite[i]->DrawAnimationSpriteX2D({ timePos.x - i * 32 + shakeAdd,timePos.y + shakeAdd }, 10, timeDigts[i], color);
	}
}

void Score::EnemyKillNumDraw(myMath::Vector4 color, float shakeAdd)
{
	if (enemyKillNum <= 9)nowEnemyKillNumDigts = 1;
	else if (10 <= enemyKillNum && enemyKillNum < 100)nowEnemyKillNumDigts = 2;
	else if (100 <= enemyKillNum && enemyKillNum < 1000)nowEnemyKillNumDigts = 3;
	else if (1000 <= enemyKillNum && enemyKillNum < 10000)nowEnemyKillNumDigts = 4;
	else if (10000 <= enemyKillNum && enemyKillNum < 100000)nowEnemyKillNumDigts = 5;
	else nowEnemyKillNumDigts = 6;

	enemyKillNumDigts[0] = enemyKillNum % 10;
	enemyKillNumDigts[1] = enemyKillNum / 10 % 10;
	enemyKillNumDigts[2] = enemyKillNum / 100 % 10;
	enemyKillNumDigts[3] = enemyKillNum / 1000 % 10;
	enemyKillNumDigts[4] = enemyKillNum / 10000 % 10;
	enemyKillNumDigts[5] = enemyKillNum / 100000;

	for (int i = 0; i < nowEnemyKillNumDigts; i++)
	{
		enemyKillNumSprite[i]->DrawAnimationSpriteX2D({ enemyKillNumPos.x - i * 32 + shakeAdd,enemyKillNumPos.y + shakeAdd }, 10, enemyKillNumDigts[i], color);
	}
}

void Score::EnemyKillAdd()
{
	enemyKillNum++;
}

void Score::Reset()
{
	nowTime = 0;
	flameTimer = 0;
	enemyKillNum = 0;
}

void Score::SetTimePos(const myMath::Vector2 timePos)
{
	this->timePos = timePos;
}

void Score::SetEnemyKillNumSpritePos(const myMath::Vector2 enemyKillNumSpritePos)
{
	this->enemyKillNumPos = enemyKillNumSpritePos;
}

Score* Score::GetInstance()
{
	static Score instance;
	return &instance;
}