#include "DxLib.h"
#include <math.h>
#include "GameMain.h"
//#include "Result.h"
#include "Item.h"
#include "PadInput.h"
//#include "FpsController.h"

GameMain::GameMain()
{
	//int CorsolImg=LoadGraph("")
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{

	return this ;
}

void GameMain::Draw()const
{
	DrawString(1120, 550, "Your Item\n", 0xfffffff);
	DrawString(1120, 570, "cigarettes\n", 0xfffffff);
	DrawString(1120, 590, "Loupe\n", 0xfffffff);
	DrawString(1120, 610, "Beer\n", 0xfffffff);
	DrawString(1120, 630, "Bomb\n", 0xfffffff);
}
