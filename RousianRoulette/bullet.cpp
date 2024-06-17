#include "bullet.h"
#include "DxLib.h"
#include "Padinput.h"
#include "GameMain.h"

int bullet::FireC;
int bullet::Cylinder[6];
int bullet::Last_Bullet;

bullet::bullet()
{
	
	B_INIT();
}

bullet::~bullet()
{
	
}


void bullet::B_INIT()
{
	Bullet_img = LoadGraph("Resources/images/Bullet/Bullet.png");
	Shot_Ui_Img = LoadGraph("Resources/images/Bullet/BulletUI.png");
	BulletCur_Img = LoadGraph("Resources/images/Bullet/BulletCur.png");
	Bullet = 0;
	for (int x = 0; x <= 5; x++) {
		Cylinder[x] = 0;
	}
	FireC = 0;
	RandBox = 0;
	Last_Bullet = 0;
	N_Of_Bullet();
	B_location();

}



void bullet::N_Of_Bullet()
{
	RandBox = GetRand(2);
	switch (RandBox)
	{
	case(0):
		Bullet = 2;
		break;
	case(1):
		Bullet = 3;
		break;
	case(2):
		Bullet = 4;
		break;
	}
	Last_Bullet = Bullet;
}


void bullet::Reload()
{
	if (FireC == 6||GameMain::E_life == 0)
	{
		B_INIT();
	}
}




void bullet::B_location()
{
	
	

	for (int x = 1; x <= Bullet; x++) 
	{
		
		RandBox = GetRand(5);
		if (Cylinder[RandBox] == 0)
		{
			Cylinder[RandBox] = 1;
		}

		else if (Cylinder[RandBox] == 1)
		{
			for (int y = 0; y <= 5; y++)
			{
				y = 0;

				RandBox = GetRand(5);

				if (Cylinder[RandBox] == 0)
				{
					Cylinder[RandBox] = 1;
					y = 6;
				}

				
			}
		}

	}

}

void bullet::Update()
{
	/*Shot();*/
	Reload();
}

void bullet::Draw() const
{
	SetFontSize(14);
	/*DrawFormatString(0, 280, 0xffffff, "Bullet:%d", Bullet);
	DrawFormatString(0, 300, 0xffffff, "B_Location:%d", Cylinder[0]);
	DrawFormatString(0, 320, 0xffffff, "B_Location:%d", Cylinder[1]);
	DrawFormatString(0, 340, 0xffffff, "B_Location:%d", Cylinder[2]);
	DrawFormatString(0, 360, 0xffffff, "B_Location:%d", Cylinder[3]);
	DrawFormatString(0, 380, 0xffffff, "B_Location:%d", Cylinder[4]);
	DrawFormatString(0, 400, 0xffffff, "B_Location:%d", Cylinder[5]);
	DrawFormatString(0, 420, 0xffffff, "FC:%d", FireC);*/

	SetFontSize(32);
	/*DrawFormatString(15, 200, 0xffffff, "LAST : %d", Last_Bullet);
	DrawString(80, 240, "BULLET", 0xffffff, TRUE);*/

	/*DrawGraph(15, 140, Bullet_img, TRUE);
	DrawGraph(15, 200, Bullet_img, TRUE);
	DrawGraph(15, 260, Bullet_img, TRUE);
	DrawGraph(15, 320, Bullet_img, TRUE);
	DrawGraph(15, 380, Bullet_img, TRUE);
	DrawGraph(15, 440, Bullet_img, TRUE);*/
	if (FireC == 1 || FireC == 2||FireC == 3 || FireC == 4 || FireC == 5 || FireC == 6)
	{
		DrawGraph(20, 110, Shot_Ui_Img, TRUE);
	}
	if (FireC == 2 || FireC == 3 || FireC == 4 || FireC == 5 || FireC == 6)
	{
		DrawGraph(20, 170, Shot_Ui_Img, TRUE);
	}
	if (FireC == 3 || FireC == 4 || FireC == 5 || FireC == 6)
	{
		DrawGraph(20, 230, Shot_Ui_Img, TRUE);
	}
	if ( FireC == 4 || FireC == 5 || FireC == 6)
	{
		DrawGraph(20, 290, Shot_Ui_Img, TRUE);
	}
	if (FireC == 5 || FireC == 6)
	{
		DrawGraph(20, 350, Shot_Ui_Img, TRUE);
	}
	if (FireC == 6)
	{
		DrawGraph(20, 410, Shot_Ui_Img, TRUE);
	}

	if (FireC == 0)
	{
		DrawGraph(35, 135, BulletCur_Img, TRUE);
	}
	if (FireC == 1 )
	{
		DrawGraph(35, 195, BulletCur_Img, TRUE);
	}
	if (FireC == 2 )
	{
		DrawGraph(35, 255, BulletCur_Img, TRUE);
	}
	if (FireC == 3 )
	{
		DrawGraph(35, 315, BulletCur_Img, TRUE);
	}
	if (FireC == 4 )
	{
		DrawGraph(35, 375, BulletCur_Img, TRUE);
	}
	if (FireC == 5)
	{
		DrawGraph(35, 435, BulletCur_Img, TRUE);
	}
}



