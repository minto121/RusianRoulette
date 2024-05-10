#include "DxLib.h"
#include <math.h>
#include "GameMain.h"
//#include "Result.h"
#include "PadInput.h"
//#include "FpsController.h"

GameMain::GameMain()
{
	BULLET = new bullet;
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{
	BULLET->Update();
	return this;
}

void GameMain::Draw() const
{
	BULLET->Draw();
	DrawBox(0, 500, 1280, 720, GetColor(255, 255, 255), TRUE);
	DrawBox(10, 510, 1270, 710, GetColor(0, 0, 0), TRUE);
}
