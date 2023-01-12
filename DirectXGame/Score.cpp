#include "Score.h"

void Score::Initialize()
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

	killTex = kill->LoadTexture("Resources/kill.png");
	kill = std::make_unique<Sprite>();
	kill->Sprite2DInitialize(killTex);

	timeTex = time->LoadTexture("Resources/time.png");
	time = std::make_unique<Sprite>();
	time->Sprite2DInitialize(timeTex);
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
	time->DrawSprite2D({ timePos.x - 32 + shakeAdd,timePos.y - 80 + shakeAdd }, color);
}

void Score::EnemyKillNumDraw(myMath::Vector4 color, float shakeAdd)
{
	if (enemyKillNum <= 9)nowEnemyKillNumDigts = 1;
	else if (10 <= enemyKillNum && enemyKillNum < 100)nowEnemyKillNumDigts = 2;
	else if (100 <= enemyKillNum && enemyKillNum < 1000)nowEnemyKillNumDigts = 3;
	else nowEnemyKillNumDigts = 4;

	enemyKillNumDigts[0] = enemyKillNum % 10;
	enemyKillNumDigts[1] = enemyKillNum / 10 % 10;
	enemyKillNumDigts[2] = enemyKillNum / 100 % 10;
	enemyKillNumDigts[3] = enemyKillNum / 1000;

	for (int i = 0; i < nowEnemyKillNumDigts; i++)
	{
		enemyKillNumSprite[i]->DrawAnimationSpriteX2D({ enemyKillNumPos.x - i * 32 + shakeAdd,enemyKillNumPos.y + shakeAdd }, 10, enemyKillNumDigts[i], color);
	}
	kill->DrawSprite2D({ enemyKillNumPos.x - 32 + shakeAdd,enemyKillNumPos.y - 80 + shakeAdd }, color);
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