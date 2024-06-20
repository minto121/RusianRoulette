#include "Enemy.h"
#include "bullet.h"
#include "DxLib.h"
#include "Padinput.h"
#include "GameMain.h"
#include "Timer.h"
#include <math.h>

int Enemy::E_WaitFlg;
//int Enemy::E_UI[];


Enemy::Enemy()
{
	E_INIT();
	
}


void Enemy::E_INIT()
{
	E_Choice = 0;
	E_Timer = 0;
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
		
		/*if (E_Timer ==1)
		{*/
			E_Timer++;
			
		/*}*/
		
			E_AI();
		
		
	}
}

void Enemy::E_AI()
{
	if (E_Timer == 100)
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
	
	if (E_Timer == 200)
	{
		for (int a = 0; a <= 1; a++) {
			E_UI[a] = FALSE;
		}
	
		switch (E_Choice)
		{
		case(0):

			E_Shot_P = TRUE;

			if (bullet::Cylinder[bullet::FireC] == 1)
			{
				GameMain::bh2_flg = TRUE;
				GameMain::P_life--;
				bullet::Last_Bullet--;
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
				bullet::Last_Bullet--;
				bullet::Cylinder[bullet::FireC] = 0;
				bullet::FireC++;
				
			}

			/*else if (bullet::Cylinder[bullet::FireC] == 0)
			{
				
				bullet::FireC++;
				
			    E_UI_TIME();
				
			}*/

			
			
			break;

		}
	}
	

}

void Enemy::E_UI_TIME()
{

	if (bullet::Cylinder[bullet::FireC] == 0 && E_Shot_Self == TRUE&&E_Timer ==300)
	{

		bullet::FireC++;
		E_Timer = 0;
		E_Shot_Self = FALSE;

	}
	
}

void Enemy::Update()
{
	
	if (E_Timer == 301/*&&GameMain::isPlayerTurn == FALSE*/)
	{
		GameMain::bh_flg = FALSE;
		GameMain::bh2_flg = FALSE;
		for (int a = 0; a <= 1; a++) {
			E_UI[a] = FALSE;
		}
		GameMain::isPlayerTurn = TRUE;
		E_Timer = 0;
	}

	E_Turn();
}

void Enemy::Draw() const
{
	SetFontSize(36);
	if (E_UI[0] == TRUE) 
	{
		DrawString(450, 40, "ENEMY", 0xfa2000, TRUE);
		DrawString(560, 40, ": SHOT PLAYER!!", 0xffffff, TRUE);
	}

	if (E_UI[1] == TRUE)
	{
		DrawString(460, 40, "ENEMY", 0xfa2000, TRUE);
		DrawString(570, 40, ": SHOT SELF!!", 0xffffff, TRUE);
	}
	DrawFormatString(20, 10, 0xffffff, "ET%d", E_Timer);
}




