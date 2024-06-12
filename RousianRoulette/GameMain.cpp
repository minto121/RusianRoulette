#include "DxLib.h"
#include <math.h>
#include "GameMain.h"
//#include "Result.h"
#include "PadInput.h"
#include "bullet.h"
#include "Title.h"
#include "Timer.h"
#include "Enemy.h"
#include "Item.h"
//#include "FpsController.h"


int GameMain::E_life;
int GameMain::P_life;
int GameMain::bh_flg;
int GameMain::bh2_flg;
int GameMain::PushFlgUI;
int GameMain::FreezUI;

enum class CURSOL
{
    C_ENEMY = 0,
    C_PLAYER
};

bool GameMain::isPlayerTurn;

GameMain::GameMain()
{
  /*  R = 2000;*/
    P_UI_INIT();
    BULLET = new bullet;
    ITEM = new Item;
    TIMER = new Timer;
    ENEMY = new Enemy;
    P_life = 2;
    E_life = 2;
    Round = 1;
    TurnCount = 0;
    //Turn = 1;
   /* isPlayerTurn = TRUE;*/
    Enemyimg[0] = LoadGraph("Resources/images/reaper.png");
    Enemyimg[1] = LoadGraph("Resources/images/skeleton.png");
    Enemyimg[2] = LoadGraph("Resources/images/zombie.png");
    Enemyimg[3] = LoadGraph("Resources/images/shocker.png");
    Enemyimg[4] = LoadGraph("Resources/images/ghost.png");
    bullet_holes = LoadGraph("Resources/images/k0100_1.png");
    bullet_holes2 = LoadGraph("Resources/images/b2.png");
    ShuffleEnemyNum = 0;
    LastEnemyNum = -1;
    isPlayerTurn = TRUE;

    WaitFlg = FALSE;
    WaitFlg2 = FALSE;
    WaitFlg3 = FALSE;

    CurX = 170;
    CurY = 570;

    GM_Select = 0;
    a = 0;
   
    ResultFlg = true;
    bh_flg = FALSE;
    bh2_flg = FALSE;
    PushFlg = FALSE;
    PushFlgUI = 0;
    Flash = 0;
    FreezUI = FALSE;
}


GameMain::~GameMain()
{
    for (int i = 0; i < IMAGE_CNT - 1; i++)
    {
        DeleteGraph(Enemyimg[i]);
    }
}


AbstractScene* GameMain::Update()
{
  
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_X))
    {
        return new Title();
    }

    if (PushFlg == TRUE) {
      
       
            Flash++;
            if (Flash == 120)
            {
                Flash = 0;
            }
       
    }


    Result();


    ITEM->Update();



    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && ResultFlg == TRUE && Item::WaitTime == FALSE
        && Item::itemtable[4] == 0&&Item::Freez == FALSE)
    {
        return new Title();
    }
    

    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && ResultFlg == TRUE && Item::itemtable[4] == 1)
    {
        if (WaitFlg3 == FALSE)
        {
           PushFlgUI = 5/*GetRand(5)*/;
          
        }
        WaitFlg3 = TRUE;
        PushFlg = TRUE;
    }

    


    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && ResultFlg == TRUE && Item::WaitTime == FALSE
        && Item::itemtable[4] == 0 && Item::Freez == TRUE)
    {
        FreezUI = TRUE;
       
    }


    if (ResultFlg == FALSE && P_life > 0&& FreezUI == FALSE)
    {

        if (Timer::FPS == 30) {
            WaitFlg2 = TRUE;

        }
        if (isPlayerTurn == FALSE && Timer::FPS == 750)
        {
            P_UI_INIT();
        }
        /*  life();*/
        BULLET->Update();
      
        ENEMY->Update();
        TIMER->Update();
        //Choice();
        Turn();
        if (isPlayerTurn == TRUE)
        {
            P_UI();
        }
        /*  Cursol();*/

        if (Timer::FPS == 200 || Timer::FPS == 799)
        {
            bh_flg = FALSE;
            bh2_flg = FALSE;
        }

        if (WaitFlg == FALSE && isPlayerTurn == TRUE && P_Ui[1] == TRUE && P_Ui[0] == FALSE)
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
                /*  CurY -= 50;*/
                GM_Select--;
                if (GM_Select < 0)GM_Select = 1;
            }
            //下方向
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
            {
                /*CurY += 50;*/
                GM_Select++;
                if (GM_Select > 1)GM_Select = 0;
            }
        }


       

    //敵のHPがなくなるとラウンドが進み弾がリロードされる
        if (E_life <= 0) {
            Round++;
            do
            {
                ShuffleEnemyNum = GetRand(IMAGE_CNT - 1);
            } while (ShuffleEnemyNum == LastEnemyNum);

            LastEnemyNum = ShuffleEnemyNum;

            /*       P_life = 2;*/
            BULLET->B_INIT();
            WaitFlg = FALSE;
            isPlayerTurn = TRUE;
            P_UI_INIT();
            E_life = 2;
        }
        return this;
    }

}


void GameMain::Draw() const
{
   
    if (ResultFlg == FALSE) {

        DrawGraph(370, 100, Enemyimg[ShuffleEnemyNum], FALSE);
        if (bh_flg == TRUE)
        {
            DrawGraph(370, 50, bullet_holes, TRUE);
        }
        BULLET->Draw();
        ENEMY->Draw();


      //白枠
    DrawBox(0, 5, 1280, 115, GetColor(255, 255, 255), TRUE);
    DrawBox(10, 15, 1270, 105, GetColor(0, 0, 0), TRUE);
    DrawBox(330, 5, 340, 105, GetColor(255, 255, 255), TRUE);
    DrawBox(950, 5, 960, 105, GetColor(255, 255, 255), TRUE);
    DrawBox(190, 105, 200, 500, GetColor(255, 255, 255), TRUE);
    DrawBox(0, 105, 10, 500, GetColor(255, 255, 255), TRUE);
    DrawBox(1090, 105, 1100, 500, GetColor(255, 255, 255), TRUE);
    DrawBox(1270, 105, 1280, 500, GetColor(255, 255, 255), TRUE);
    DrawBox(950, 5, 960, 105, GetColor(255, 255, 255), TRUE);
    DrawBox(1090, 180, 1280, 190, GetColor(255, 255, 255), TRUE);
    DrawBox(1090, 300, 1280, 310, GetColor(255, 255, 255), TRUE);
    DrawBox(1090, 375, 1280, 385, GetColor(255, 255, 255), TRUE);
    //UI
    DrawBox(0, 500, 1280, 720, GetColor(255, 255, 255), TRUE);
    DrawBox(10, 510, 1270, 710, GetColor(0, 0, 0), TRUE);


    SetFontSize(36);
   
    DrawString(1145, 130, "LIFE", 0xFF0000);
    DrawString(1145, 325, "LIFE", 0xFFFF00);


 
      
       
      /*  if (isPlayerTurn == TRUE)
        {
            DrawString(1130, 350, "PLAYER", 0xFFFF00);
        }
        else
        {
            DrawString(1135, 350, "ENEMY", 0xfa2000);
        }*/

        //プレイヤーか敵を選ぶ
        SetFontSize(48);


        if (P_Ui[0] == TRUE)
        {
            DrawString(200, 550, "SHOT", 0xffffff);
            DrawString(200, 600, "ITEM", 0xffffff);
            DrawCircle(CurX, CurY, 10, 0xffffff, TRUE);
        }

        if (P_Ui[2] == TRUE)
        {
            DrawString(200, 530, "DRAG:", 0xffffff);
            DrawString(550, 530, "BOMB:", 0xffffff);
            DrawString(900, 530, "LOUPE:", 0xffffff);
            DrawString(200, 650, "JUDGE:", 0xffffff);
            DrawString(550, 650, "TOTEM:", 0xffffff);
            DrawString(900, 650, "C_BULLET:", 0xffffff);
            DrawCircle(CurX, CurY, 10, 0xffffff, TRUE);
        }

        if (P_Ui[1] == TRUE)
        {
            DrawString(200, 550, "ENEMY", 0xffffff);
            DrawString(200, 600, "PLAYER", 0xffffff);
        }
        if (P_Ui[1] == TRUE)
        {
            int select_y = 570 + GM_Select * 50;
            DrawCircle(170, select_y, 10, GetColor(255, 255, 255), TRUE);
        }

        if (bh2_flg == TRUE && ResultFlg == FALSE)
        {
            DrawGraph(-120, -140, bullet_holes2, TRUE);
        }
 
    }
   
 
    
   

    SetFontSize(48);
    if (ResultFlg == TRUE) {

       
        DrawFormatString(550, 300, GetColor(255, 255, 255), "Round:%d", Round);
        DrawString(550, 50, "Result", 0xffffff);
        DrawString(480, 650, "Press_A_Button", 0xffffff);

    }


    if (PushFlg == TRUE && Item::itemtable[4] == 1 && Flash <= 80 && PushFlgUI != 1 
        || Item::TotemRand == 0 && PushFlgUI == 1 && Flash <= 80&& PushFlg == TRUE && Item::itemtable[4] == 1) {
        DrawBox(440, 440, 810, 580, 0xADD8E6, TRUE);
        DrawString(570, 390, "PUSH", 0xFFFF00);
    }
    if (PushFlg == TRUE && Item::itemtable[4] == 1 && PushFlgUI != 1|| 
        Item::TotemRand == 0&& PushFlgUI == 1&&PushFlg == TRUE && Item::itemtable[4] == 1)
    {
        DrawBox(460, 460, 790, 560, 0xffffff, TRUE);
        DrawTriangle(570, 470, 570, 550, 690, 510, 0xFF0000, TRUE);
        DrawString(560, 490, "START", 0x0000FF);
    }



    if (PushFlg == TRUE && Item::itemtable[4] == 1 && Flash <= 80 &&
        PushFlgUI == 1 && Item::TotemRand == 1)
    {
        DrawBox(80, 80, 1200, 640, 0xADD8E6, TRUE);
        SetFontSize(72);
        DrawString(540, 0, "PUSH", 0xFFFF00);
    }

    if (PushFlg == TRUE && Item::itemtable[4] == 1&&PushFlgUI == 1 
        && Item::TotemRand == 1)
    {
        DrawBox(150, 150, 1130, 570, 0xffffff, TRUE);
        DrawTriangle(470, 160, 470, 560, 900, 370, 0xFF0000, TRUE);
        SetFontSize(72);
        DrawString(530, 320, "START", 0x0000FF);
    }



   




    
    
   
   
    ITEM->Draw();
   
}




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
        WaitFlg = FALSE;
    }
}


void GameMain::E_Choice()
{
    if (WaitFlg == FALSE)
    {
        WaitFlg = !WaitFlg;
    }
    if (bullet::Cylinder[bullet::FireC] == 1)
    {
        bh_flg = TRUE;
        E_life--;
        if (Item::Bomb == TRUE)
        {
            E_life--;
        }
        bullet::Cylinder[bullet::FireC] = 0;
        bullet::FireC++;

    }
    else if (bullet::Cylinder[bullet::FireC] == 0)
    {
        bullet::FireC++;
    }
    isPlayerTurn = !isPlayerTurn;
    ENEMY->E_UI_TIME();

    Item::Bomb = FALSE;
}


void GameMain::P_Choice()
{
    /*if (WaitFlg == FALSE)
    {
        WaitFlg =!WaitFlg;
    }*/

    if (bullet::Cylinder[bullet::FireC] == 1)
    {
        bh2_flg = TRUE;
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


void GameMain::Result()
{

    if (P_life <= 0 && a == 0)
    {
        Timer::FPS = 0;
        a = 1;
    }
    if (a == 1)
    {
        Timer::FPS++;
    }
    if (P_life <= 0 && Timer::FPS == 200)
    {
        ResultFlg = TRUE;
    }

    if (Item::R4 == 460)
    {
        Item::itemtable[4] = 0;
        isPlayerTurn = TRUE;
        bh2_flg = FALSE;
        ResultFlg = FALSE;
        PushFlg = FALSE;
        PushFlgUI = 0;
        Flash = 0;
        FreezUI = FALSE;

    }


    if (PushFlg == TRUE &&Item::itemtable[4] ==1&&
        PAD_INPUT::OnButton(XINPUT_BUTTON_START))
    {
        P_life = 2;
        Item::TotemFlg = TRUE;
       
        WaitFlg3 = FALSE;
        PushFlg = FALSE;
    }
    
    if (Item::R3 == 460)
    {
        isPlayerTurn = TRUE;
        bh2_flg = FALSE;
        ResultFlg = FALSE;
        PushFlg = FALSE;
        PushFlgUI = 0;
        Flash = 0;
        Item:: Freez = FALSE;
        FreezUI = FALSE;
        Item::itemtable[4] = 0;
        ITEM->INIT();
       
    }
    
}


void GameMain::P_UI()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
    {
        P_UI_INIT();
    }
    if (P_Ui_flg[0] == TRUE)
    {
        P_Ui[0] = TRUE;

    }
    if (P_Ui_flg[1] == TRUE)
    {


    }
    if (P_Ui[0] == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)
        && CurX == 170 && CurY == 570)
    {
        P_Ui_flg[0] = FALSE;
        P_Ui_flg[1] = TRUE;
        CurX = 170;
        CurY = 620;
    }

    if (P_Ui_flg[1] == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)
        && CurX == 170 && CurY == 620)
    {
        P_Ui_flg[1] = FALSE;
        P_Ui_flg[0] = TRUE;
        CurX = 170;
        CurY = 570;
    }



    if (P_Ui_flg[0] == TRUE && PAD_INPUT::OnRelease(XINPUT_BUTTON_A) && WaitFlg2 == TRUE)
    {
        P_Ui[1] = TRUE;
        P_Ui[0] = FALSE;
        P_Ui_flg[0] = FALSE;
    }


    if (P_Ui_flg[1] == TRUE && PAD_INPUT::OnRelease(XINPUT_BUTTON_A) && WaitFlg2 == TRUE)
    {

        P_Ui[2] = TRUE;
        P_Ui[0] = FALSE;
        P_Ui_flg[0] = FALSE;
        CurX = 170;
        CurY = 550;
        P_Ui_flg[1] = FALSE;
    }

    if (P_Ui[2] == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT) && CurX != 870)
    {
        CurX += 350;
    }
    if (P_Ui[2] == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT) && CurX != 170)
    {
        CurX -= 350;
    }
    if (P_Ui[2] == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) && CurY != 670)
    {
        CurY += 120;
    }
    if (P_Ui[2] == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) && CurY != 570)
    {
        CurY -= 120;
    }
}


void GameMain::P_UI_INIT()
{
    P_Ui_flg[0] = TRUE;
    CurX = 170;
    CurY = 570;
    for (int i = 1; i < 5; i++)
    {
        P_Ui_flg[i] = FALSE;
    }

    for (int i = 0; i < 5; i++)
    {
        P_Ui[i] = FALSE;
    }


}

