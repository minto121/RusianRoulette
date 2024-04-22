#include "DxLib.h"
#include <math.h>
#include "GameMain.h"
//#include "Result.h"
#include "PadInput.h"
//#include "bullet.h"
#include "Title.h"
//#include "FpsController.h"

GameMain::GameMain()
{
	BULLET = new bullet;
	P_life = 2;
    E_life = 2;
    Round = 1;
    //Turn = 1;
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{

  /*  if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
    {
        switch (currentPlayer)
        {
        case PlayerState::PLAYER:
           
        default:
            break;
        }
    }*/
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
    else
    {
     /*   if(currentPlayer == PlayerState::PLAYER)
            if (chamber[rand() % NUM_CHAMBERS] == 1) {
                P_life--;
            }
        currentPlayer = PlayerState::ENEMY;

        if(currentPlayer == PlayerState::ENEMY)
            if (chamber[rand() % NUM_CHAMBERS] == 1) {
                E_life;
            }
        currentPlayer == PlayerState::PLAYER;*/
    }


    //プレイヤーが負けた時の処理
    if (P_life <= 0) {
        DrawString(20, 140, "Game Over. Press Escape to exit.", GetColor(255, 255, 255));
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)||CheckHitKey(KEY_INPUT_ESCAPE)) {
            return new Title;
        }
    }

	return this;
	BULLET->Update();
	return this;
}

void GameMain::Draw() const
{
	BULLET->Draw();
    DrawFormatString(0, 100, GetColor(255, 255, 255), "P_life:%d",P_life);
    DrawFormatString(0, 120, GetColor(255, 255, 255), "E_life:%d",E_life);
    DrawFormatString(0, 140, GetColor(255, 255, 255), "Round:%d",Round);
    /*DrawFormatString(0, 130, GetColor(255, 255, 255), "Turn:%d",Trun);*/
}
