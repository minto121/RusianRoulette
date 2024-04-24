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
}
