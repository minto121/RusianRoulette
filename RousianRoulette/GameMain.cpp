#include "DxLib.h"
#include <math.h>
#include "GameMain.h"
//#include "Result.h"
#include "Item.h"
#include "PadInput.h"
//#include "FpsController.h"

GameMain::GameMain()
{
	 CursolImg = LoadGraph("./resouce/image/cursor.png");
	 Life=1;
	 int i = 0;
	 LocationX = 950;
	 LocationY = 540;
	 isUseCigarettes = false;
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
		LocationY += 30;
	}
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
		LocationY -= 30;
	}


	if (LocationY < 540) {
		LocationY = 540;
	}
	else if (LocationY > 720) {
		LocationY = 720;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		if(Life < 3){
			Life += 1;
			isUseCigarettes = true;
		}	
		
	}
	
	return this;
}

void GameMain::Draw()const
{
	SetFontSize(40);
	DrawString(1030, 500, "Your Item\n", 0xfffffff);
	DrawString(1030, 540, "Cigarettes\n", 0xfffffff);
	DrawString(1030, 580, "Loupe\n", 0xfffffff);
	DrawString(1030, 620, "Beer\n", 0xfffffff);
	DrawString(1030, 660, "Bomb\n", 0xfffffff);
	DrawGraph(LocationX, LocationY, CursolImg,TRUE);
	DrawFormatString(100, 500,0xfffffff,"life%d",Life);
	if (isUseCigarettes) {
		SetFontSize(20);
		DrawString(500, 660, "Used Cigarettes\n", 0xfffffff);
	}
	
}

