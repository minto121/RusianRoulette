#include "DxLib.h"
#include <math.h>
#include "GameMain.h"
//#include "Result.h"
#include "PadInput.h"
#include "bullet.h"
#include "Title.h"
//#include "FpsController.h"

GameMain::GameMain()
{
	BULLET = new bullet;
	P_life = 2;
    E_life = 2;
    Round = 1;
    TurnCount = 0;
    //Turn = 1;
   /* isPlayerTurn = TRUE;*/
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{
    life();
    Turn();
    BULLET->Update();

  /*  if (isPlayerTurn) {
        BULLET->Update();
    }*/

    //プレイヤーが負けた時の処理
    if (P_life <= 0) {
        DrawString(20, 140, "Game Over. Press Escape to exit.", GetColor(255, 255, 255));
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)||CheckHitKey(KEY_INPUT_ESCAPE)) {
            return new Title;
        }
    }

	return this;
}

void GameMain::Draw() const
{
	BULLET->Draw();
	DrawBox(0, 500, 1280, 720, GetColor(255, 255, 255), TRUE);
	DrawBox(10, 510, 1270, 710, GetColor(0, 0, 0), TRUE);
    DrawFormatString(0, 100, GetColor(255, 255, 255), "P_life:%d",P_life);
    DrawFormatString(0, 120, GetColor(255, 255, 255), "E_life:%d",E_life);
    DrawFormatString(0, 140, GetColor(255, 255, 255), "Round:%d",Round);
    DrawFormatString(0, 200, GetColor(255, 255, 255), "TurnCount:%d",TurnCount);
   /* DrawFormatString(0, 160, GetColor(255, 255, 255), "Turn:%d",P_Turn);
    DrawFormatString(0, 180, GetColor(255, 255, 255), "Turn:%d",E_Turn);*/
    /*DrawFormatString(0, 130, GetColor(255, 255, 255), "Turn:%d",Trun);*/

    if (isPlayerTurn == TRUE)
    {
        DrawString(0, 160, "Pleyer",0xffffff);
    }
    else
    {
        DrawString(0, 180, "Enemy", 0xffffff);
    }
}

void GameMain::life()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
    {
        E_life--;
    }

    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
    {
        P_life--;
    }

    //ラウンドが進んだ時にライフをリセットする
    if (E_life <= 0) {
        Round++;
        P_life = 2;
        E_life = 2;
    }
}

void GameMain::Turn()
{
    TurnCount = bullet::FireC;

    if (TurnCount%2==0) {
        isPlayerTurn = TRUE;
    }
    else
    {
        isPlayerTurn = FALSE;
    }
     
}
void GameMain::Choice()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
    {
       
    }

    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
    {
       
    }
}
