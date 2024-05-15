#include "Enemy.h"
#include "bullet.h"
#include "DxLib.h"
#include "Padinput.h"
#include "GameMain.h"

Enemy::Enemy()
{
	E_Choice = 0;
}

Enemy::~Enemy()
{

}

void Enemy::E_Turn()
{
	if (GameMain::isPlayerTurn == FALSE) 
	{
		Timer::FPS = 1;
		E_AI();
		if (Timer::FPS == 400)
		{
			GameMain::isPlayerTurn = TRUE;
		}
	}
}

void Enemy::E_AI()
{
	E_Choice = GetRand(1);
	switch (E_Choice)
	{
	case(0):


		break;
	case(1):


		break;
	}
}

void Enemy::Update()
{

}

void Enemy::Draw() const
{

}



