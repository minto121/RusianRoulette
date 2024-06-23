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
	E_Choice = 3;
	E_Timer = 0;
	E_Shot_P = FALSE;
	E_Shot_Self = FALSE;
	E_WaitFlg = TRUE;

	ESP_hit_flg = FALSE;
    ESP_miss_flg = FALSE;
    ESE_hit_flg = FALSE;
    ESE_miss_flg = FALSE;
	OneMore = FALSE;
	ShotSE = LoadSoundMem("Resources/sounds/Gunshot.mp3");

	for (int a = 0; a <= 1; a++) {
		E_UI[a] = FALSE;
	}

	NohitImg = LoadGraph("Resources/images/ESP_MISS.png");
	OneMoreImg = LoadGraph("Resources/images/1more_Enemy.png");
	NshotSE = LoadSoundMem("Resources/sounds/not shot.mp3");
	EnemyUISE = LoadSoundMem("Resources/SE/PUI[1]SE.mp3");
	/*Hitdamage = LoadGraph("resouce/image/Damage.png");*/

	Nohit_UI = FALSE;
	Hit_UI = FALSE;
	NT = 0;
	YT = 0;
}


Enemy::~Enemy()
{

}


void Enemy::E_Turn()
{
	if (GameMain::isPlayerTurn == TRUE||E_Timer ==0)
	{
		Nohit_UI = FALSE;
		ESP_hit_flg = FALSE;
		ESP_miss_flg = FALSE;
		ESE_hit_flg = FALSE;
		ESE_miss_flg = FALSE;
		E_Choice = 3;
		E_Timer = 0;
		OneMore = FALSE;
	}
	if (GameMain::isPlayerTurn == FALSE&&GameMain::E_life>0&&GameMain::TurnTime==120)
	{
		
		/*if (E_Timer ==1)
		{*/


		ChangeVolumeSoundMem(55, GameMain::GMBgm);


			E_Timer++;
			

			if (E_Timer == 1)
			{
				PlaySoundMem(EnemyUISE, DX_PLAYTYPE_BACK);
			}
		/*}*/
		
			E_AI();
			E_PChoice();
			E_EChoice();
		
	}
}


void Enemy::E_AI()
{
	if (E_Timer ==2)
	{
		if (6 - bullet::FireC == bullet::Last_Bullet 
			|| 6 - bullet::FireC - bullet::Last_Bullet < bullet::Last_Bullet)
		{
			E_Choice = 0;
			E_UI[0] = TRUE;
		}



		else if (6 - bullet::FireC - bullet::Last_Bullet > bullet::Last_Bullet)
		{
			E_Choice = 1;
			E_UI[1] = TRUE;
		}





		else if (6 - bullet::FireC - bullet::Last_Bullet == bullet::Last_Bullet)
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


void Enemy::E_PChoice()
{

	if (E_Timer == 121 && E_Choice == 0)
	{
		if (bullet::Cylinder[bullet::FireC] == 1)
		{
			bullet::Last_Bullet -= 1;
			ESP_hit_flg = TRUE;
			GameMain::bh2_flg = TRUE;
			PlaySoundMem(ShotSE, DX_PLAYTYPE_BACK);
		}
		else if(bullet::Cylinder[bullet::FireC] == 0)
		{
			PlaySoundMem(NshotSE, DX_PLAYTYPE_BACK);
			ESP_miss_flg = TRUE;
			Nohit_UI = TRUE;
		}

		E_UI[0] = FALSE;
	}


	if (E_Timer == 241 && E_Choice == 0)
	{

		if (ESP_hit_flg == TRUE)
		{
			GameMain::P_life -=1;
			bullet::Cylinder[bullet::FireC] = 0;
			bullet::FireC++;
			GameMain::bh2_flg = FALSE;
			E_Timer = 301;
		}
		else if (ESP_miss_flg == TRUE)
		{
			bullet::Cylinder[bullet::FireC] = 0;
			bullet::FireC++;
			Nohit_UI = FALSE;
			E_Timer = 301;
		}
		
	}
	if (E_Timer == 301 && E_Choice == 0)
	{
		GameMain::TurnTime = 0;
		GameMain::isPlayerTurn = TRUE;
	}

}



void Enemy::E_EChoice()
{
	if (E_Timer == 121 && E_Choice == 1)
	{
		if (bullet::Cylinder[bullet::FireC] == 1)
		{
			bullet::Last_Bullet -= 1;
			ESE_hit_flg = TRUE;
			PlaySoundMem(ShotSE, DX_PLAYTYPE_BACK);
			GameMain::bh_flg = TRUE;
		}
		else if (bullet::Cylinder[bullet::FireC] == 0)
		{
			PlaySoundMem(NshotSE, DX_PLAYTYPE_BACK);
			ESE_miss_flg = TRUE;
			OneMore = TRUE;
		}

		E_UI[1] = FALSE;
	}

	if (E_Timer == 241 && E_Choice == 1)
	{

		if (ESE_hit_flg == TRUE)
		{
			GameMain::E_life -= 1;

			bullet::Cylinder[bullet::FireC] = 0;
			bullet::FireC++;

			GameMain::bh_flg = FALSE;
			E_Timer = 301;
		}
		else if (ESE_miss_flg == TRUE)
		{
			bullet::Cylinder[bullet::FireC] = 0;
			bullet::FireC++;
			E_Timer = 301;
		
		}

	}
	if (E_Timer == 301 && E_Choice == 1&&ESE_hit_flg ==TRUE)
	{
		 GameMain::TurnTime =0;

		GameMain::isPlayerTurn = TRUE;

	}
	if (E_Timer == 301 && E_Choice == 1 && ESE_miss_flg == TRUE)
	{
		E_Timer = 0;
	}
}




void Enemy::Update()
{
	
	

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
	
	if (Nohit_UI == TRUE) {
		DrawGraph(200, 110, NohitImg, FALSE);
	}

	if (OneMore == TRUE)
	{
		DrawGraph(200, 110, OneMoreImg, FALSE);
	}

	/*if (Hit_UI == TRUE&&GameMain::bh2_flg==FALSE) {
		DrawGraph(0, 0, Hitdamage, TRUE);
	}*/
	

}





