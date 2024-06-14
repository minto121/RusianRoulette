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

enum class CURSOL
{
    C_ENEMY,
    C_PLAYER
};

bool GameMain::isPlayerTurn;
GameMain::GameMain()
{
	BULLET = new bullet;
    ITEM = new Item;
    TIMER = new Timer;
    ENEMY = new Enemy;
	P_life = 2;
    E_life = 2;
    Round = 1;
    TurnCount = 0;
    isPlayerTurn = TRUE;
    CurX = 170;
    CurY = 550;

    GM_Select = 0;

}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{

  /*  life();*/
    BULLET->Update();
    ITEM->Update();
    ENEMY->Update();
    TIMER->Update();
    //Choice();
    Turn();
    Cursol();
    GM_Select = 0;

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
        WaitTimer(1000);
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
    ENEMY->Draw();
    //UI
	DrawBox(0, 500, 1280, 720, GetColor(255, 255, 255), TRUE);
	DrawBox(10, 510, 1270, 710, GetColor(0, 0, 0), TRUE);
    //UI上
    DrawBox(0,10, 1280, 120, GetColor(255, 255, 255), TRUE);
    DrawBox(10, 20, 1270, 110, GetColor(0, 0, 0), TRUE);

    SetFontSize(14);
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

    //プレイヤーか敵を選ぶ
    SetFontSize(48);
    DrawString(200, 550, "ENEMY", 0xffffff);
    DrawString(200, 600, "PLAYER", 0xffffff);

    DrawBox(CurX, CurY, CurX + 200, CurY + 50, 0xffffff, FALSE);


    SetFontSize(24);
    int z_X = 50;
    int z_Y = 60;
    for (int i = 0; i
        < E_life; ++i) {
        DrawString(z_X + (i * 30), z_Y, "", 0xffffff);
    }
   
}

//void GameMain::Choice()
//
//{
//    //プレイヤーが敵を選択
//    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
//    {
//
//        if (bullet::Cylinder[bullet::FireC] == 1)
//        {
//            E_life--;
//            bullet::Cylinder[bullet::FireC] = 0;
//            bullet::FireC++;
//        }
//        else if (bullet::Cylinder[bullet::FireC] == 0)
//        {
//            bullet::FireC++;
//        }
//        isPlayerTurn = !isPlayerTurn;
//
//    }
//
//    //プレイヤーが自分を選択
//    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
//    {
//
//        if (bullet::Cylinder[bullet::FireC] == 1)
//        {
//            P_life--;
//            isPlayerTurn = !isPlayerTurn;
//            bullet::Cylinder[bullet::FireC] = 0;
//            bullet::FireC++;
//        }
//        else if (bullet::Cylinder[bullet::FireC] == 0)
//        {
//            bullet::FireC++;
//        }
//
//    }
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

void GameMain::Cursol()
{


    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
    {
        switch (static_cast<CURSOL>(GM_Select))
        {
        case CURSOL::C_ENEMY:
            E_Choice();
            break;
        case CURSOL::C_PLAYER:
            P_Choice();
            break;
        default:
            break;
        }
    }
    //上方向
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
    {
        CurY -= 50;
        GM_Select--;
        if (GM_Select < 0)GM_Select = 1;
    }
    //下方向
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
    {
        CurY += 50;
        GM_Select--;
        if (GM_Select > 1)GM_Select = 0;
    }

    if (CurY < 550) {
        CurY = 600;
    }
    if (CurY > 600) {
        CurY = 550;
    }
}

void GameMain::E_Choice()
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
        ENEMY->E_UI_TIME();
    }

void GameMain::P_Choice()
{
  
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && isPlayerTurn == TRUE)
    {
       
        if (bullet::Cylinder[bullet::FireC] == 1)
        {
            P_life--;
            isPlayerTurn = !isPlayerTurn;
            ENEMY->E_UI_TIME();
            bullet::Cylinder[bullet::FireC] = 0;
            bullet::FireC++;
        }
        else if (bullet::Cylinder[bullet::FireC] == 0)
        {
            bullet::FireC++;
        }
        
    }

    //ラウンドが進んだ時にライフをリセットする
    
}

