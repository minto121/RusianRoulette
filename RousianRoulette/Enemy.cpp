#include "Enemy.h"
#include "bullet.h"
#include "DxLib.h"
#include "Padinput.h"
#include "GameMain.h"
#include "Timer.h"
#include <math.h>

Enemy::Enemy()
{
	E_Choice = 0;
	E_Shot_P = FALSE;
	E_Shot_Self = FALSE;
	E_WaitFlg = TRUE;

	for (int a = 0; a <= 1; a++) {
		E_UI[a] = FALSE;
	}
	
}

Enemy::~Enemy()
{

}

void Enemy::E_Turn()
{
	if (GameMain::isPlayerTurn == FALSE)
	{
		
		if (E_WaitFlg == FALSE)
		{
			Timer::FPS = 1;
			E_WaitFlg = TRUE;
		}
		
			E_AI();
		
		
	}
}

void Enemy::E_AI()
{
	if (Timer::FPS == 200)
	{
		E_Choice = GetRand(1);
		switch (E_Choice)
		{
		case(0):
			E_UI[0] = TRUE;
			break;
		case(1):
			E_UI[1] = TRUE;
			break;
		}
	}
	
	if (Timer::FPS == 700)
	{

		switch (E_Choice)
		{
		case(0):

			E_Shot_P = TRUE;

			if (bullet::Cylinder[bullet::FireC] == 1)
			{
				GameMain::bh2_flg = TRUE;
				GameMain::P_life--;
				bullet::Cylinder[bullet::FireC] = 0;
				bullet::FireC++;
				
			}

			else if (bullet::Cylinder[bullet::FireC] == 0)
			{
				bullet::FireC++;

			}

			E_Shot_P = FALSE;

			break;



		case(1):
			
			E_Shot_Self = TRUE;
			
			if (bullet::Cylinder[bullet::FireC] == 1)
			{
				
				GameMain::bh_flg = TRUE;
				GameMain::E_life--;
				bullet::Cylinder[bullet::FireC] = 0;
				bullet::FireC++;
				E_UI[1] = FALSE;
			}

			else if (bullet::Cylinder[bullet::FireC] == 0)
			{
				for (int a = 0; a <= 1; a++) {
					E_UI[a] = FALSE;
				}
				bullet::FireC++;
				
				E_UI_TIME();
				
			}

			E_Shot_Self = FALSE;
			
			break;

		}
	}
	

}

void Enemy::E_UI_TIME()
{
	E_WaitFlg = FALSE;
}

void Enemy::Update()
{
	
	if (Timer::FPS == 790&&GameMain::isPlayerTurn == FALSE)
	{
		for (int a = 0; a <= 1; a++) {
			E_UI[a] = FALSE;
		}
		GameMain::isPlayerTurn = TRUE;

	}

	E_Turn();
}

void Enemy::Draw() const
{
	if (E_UI[0] == TRUE) 
	{
		DrawString(50, 180, "ENEMY: SHOT PLAYER", 0xffffff, TRUE);
	}

	if (E_UI[1] == TRUE)
	{
		DrawString(50, 180, "ENEMY: SHOT SELF", 0xffffff, TRUE);
	}
	
}



