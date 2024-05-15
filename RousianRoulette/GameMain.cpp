#include "DxLib.h"
#include <math.h>
#include "GameMain.h"
//#include "Result.h"
#include "PadInput.h"
#include "bullet.h"
#include "Title.h"
#include "Timer.h"
//#include "FpsController.h"

int GameMain::E_life;
int GameMain::P_life;

GameMain::GameMain()
{
	BULLET = new bullet;
    ITEM = new Item;
    TIMER = new Timer;
	P_life = 2;
    E_life = 2;
    Round = 1;
    TurnCount = 0;
    isPlayerTurn = TRUE;
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{
  /*  life();*/
    BULLET->Update();
    ITEM->Update();
    TIMER->Update();
    Choice();
    Turn();

  /*  if (isPlayerTurn) {
        BULLET->Update();
    }*/

    //プレイヤーが負けた時の処理
    if (P_life <= 0) {
        return new Title;
    }

    

    //敵のHPがなくなるとラウンドが進み弾がリロードされる
    if (E_life <= 0) {
        Round++;
        /*       P_life = 2;*/
        BULLET->B_INIT();
        isPlayerTurn = TRUE;
        E_life = 2;
    }

	return this;
}

void GameMain::Draw() const
{
	BULLET->Draw();
    ITEM->Draw();
    TIMER->Draw();
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

//void GameMain::life()
//{
//  /*  if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
//    {
//        E_life--;
//    }*/
//
//    //if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
//    //{
//    //    P_life--;
//    //}
//
//  
//}
//



void GameMain::Choice()

{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
    {

        if (bullet::Cylinder[bullet::FireC] == 1)
        {
            E_life--;
            bullet::Cylinder[bullet::FireC] = 0;
            bullet::FireC++;
        }
        else if (bullet::Cylinder[bullet::FireC] == 0)
        {
            bullet::FireC++;
        }
        isPlayerTurn = !isPlayerTurn;

    }

    //プレイヤーが自分を選択
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
    {

        if (bullet::Cylinder[bullet::FireC] == 1)
        {
            P_life--;
            isPlayerTurn = !isPlayerTurn;
            bullet::Cylinder[bullet::FireC] = 0;
            bullet::FireC++;
        }
        else if (bullet::Cylinder[bullet::FireC] == 0)
        {
            bullet::FireC++;
        }

    }
}

    ////ラウンドが進んだ時にライフをリセットする
    //if (E_life <= 0) {
    //    Round++;
    //    P_life = 2;
    //    E_life = 2;
    //}

void GameMain::Turn()
{
    TurnCount = bullet::FireC;

    if (isPlayerTurn == FALSE)
    {
        //敵がプレイヤーを選択
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && isPlayerTurn == FALSE)
        {
         

            if (bullet::Cylinder[bullet::FireC] == 1 && isPlayerTurn == FALSE)
            {
                P_life--;
                isPlayerTurn = TRUE;
            }
            else
            {
                isPlayerTurn = TRUE;
            }
        }
    }
}
