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
    P_life = 1;
    E_life = 2;
    Round = 1;
    ResultFlg = /*FALSE*/TRUE;
    INIT();
}

void GameMain::INIT()
{
    CurX = 180;
    CurY = 576;
    P_UI_INIT();

    flash = 0;
    BULLET = new bullet;
    ITEM = new Item;
    TIMER = new Timer;
    ENEMY = new Enemy;
   
    TurnCount = 0;
    //Turn = 1;
   /* isPlayerTurn = TRUE;*/
    Enemyimg[0] = LoadGraph("Resources/images/reaper.png");
    Enemyimg[1] = LoadGraph("Resources/images/skeleton.png");
    Enemyimg[2] = LoadGraph("Resources/images/zombie.png");
    Enemyimg[3] = LoadGraph("Resources/images/shocker.png");
    Enemyimg[4] = LoadGraph("Resources/images/ghost.png");
    bullet_holes = LoadGraph("Resources/images/k0100_1.png");
    bullet_holes2 = LoadGraph("Resources/images/White.png");
    P_LifeImg = LoadGraph("Resources/images/P_Life.png");
    E_LifeImg = LoadGraph("Resources/images/E_Life.png");
    BackGRImg = LoadGraph("Resources/images/BG.png");
    CursolImg[0] = LoadGraph("resouce/image/cursor3.png");
    CursolImg[1] = LoadGraph("resouce/image/cursor2.png");
    CursolImg[2] = LoadGraph("resouce/image/cursor4.png");

    PushSE = LoadSoundMem("Resources/SE/Push.mp3");
    PushSE2 = LoadSoundMem("Resources/SE/Push2.mp3");
    ResultBgm = LoadSoundMem("Resources/SE/result.mp3");
    ResultBackImg[0] = LoadGraph("Resources/images/Result1.png");
    ResultBackImg[1] = LoadGraph("Resources/images/Result2.png");
    ResultBackImg[2] = LoadGraph("Resources/images/Result3.png");
    ResultBackImg[3] = LoadGraph("Resources/images/Result4.png");
    ResultBackImg[4] = LoadGraph("Resources/images/Result5.png");
    ResultBackImg[5] = LoadGraph("Resources/images/Result6.png");
    ResultBackImg[6] = LoadGraph("Resources/images/Result7.png");

    RoundBackImg1 = LoadGraph("Resources/images/HukkatuRound.png");
    RoundBackImg2 = LoadGraph("Resources/images/FreezRound.png");


    UraBotanSE = LoadSoundMem("Resources/SE/UraBotann.mp3");
    ShuffleEnemyNum = 0;
    LastEnemyNum = -1;
    isPlayerTurn = TRUE;

    WaitFlg = FALSE;
    WaitFlg2 = FALSE;
    WaitFlg3 = FALSE;


    ResultFlg = FALSE;
    GM_Select = 0;
    a = 0;
    E_life = 2;
   
    bh_flg = FALSE;
    bh2_flg = FALSE;
    PushFlg = FALSE;
    PushFlgUI = 0;
    Flash = 0;

    FreezUI = FALSE;
    PushSEflg = FALSE;
    ResultBgmFlg = TRUE;
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
    ROUND_UI();
   
    if (RoundUiflg == FALSE) 
    {

 
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_X))
        {
            return new Title();
        }
        if (ResultFlg == TRUE&& ResultBgmFlg == TRUE)
        {
            PlaySoundMem(ResultBgm, TRUE);
            ResultBgmFlg = FALSE;
        }
        if (PushFlg == TRUE) {
           /* flash++;*/
           
                Flash++;
                if (Flash == 120)
                {
                    Flash = 0;
                }
                if (Flash == 1&& PushFlgUI != 1&& PushSEflg == FALSE) {
                    PlaySoundMem(PushSE, DX_PLAYTYPE_BACK);
                    PushSEflg = TRUE;
                }
                if (Flash == 1 && PushFlgUI == 1 && PushSEflg == FALSE && Item::TotemRand == 1) {
                    PlaySoundMem(PushSE2, DX_PLAYTYPE_BACK);
                    PushSEflg = TRUE;
                }

                if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER)&& flash == 0&&Item::TotemRand == 1)
                {

                  
                        flash = 1;
                    
                }
                if (flash >= 1)
                {
                    if (Flash % 30 ==0)
                    {
                        flash += 1;
                        PlaySoundMem(UraBotanSE, TRUE);
                    }
                }
                if (flash == 12)
                {
                   
                        flash = 0;
                   
                }
        }


        Result();


        ITEM->Update();



        if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && ResultFlg == TRUE && Item::WaitTime == FALSE
            && Item::itemtable[4] == 0&&Item::Freez == FALSE)
        {
            return new Title();
        }
    

        if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && ResultFlg == TRUE && Item::itemtable[4] == 1)
        {
            if (WaitFlg3 == FALSE)
            {
               PushFlgUI = GetRand(5);
          
            }
      
                P_UI_INIT();
       
      
            WaitFlg3 = TRUE;
            PushFlg = TRUE;
        
        }

    


        if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && ResultFlg == TRUE && Item::WaitTime == FALSE
            && Item::itemtable[4] == 0 && Item::Freez == TRUE)
        {
            FreezUI = TRUE;
       
        }


        if (ResultFlg == FALSE && P_life > 0 && FreezUI == FALSE)
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

            ////if (WaitFlg == FALSE && isPlayerTurn == TRUE && P_Ui[1] == TRUE && P_Ui[0] == FALSE)
            ////{
            ////    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
            ////    {
            ////        switch (static_cast<CURSOL>(GM_Select))
            ////        {
            ////        case CURSOL::C_ENEMY:
            ////            E_Choice();
            ////            break;
            ////        case CURSOL::C_PLAYER:
            ////            P_Choice();
            ////            break;
            ////        default:
            ////            break;
            ////        }
            ////    }
            ////    //上方向
            ////    if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
            ////    {
            ////        /*  CurY -= 50;*/
            ////        GM_Select--;
            ////        if (GM_Select < 0)GM_Select = 1;
            ////    }
            ////    //下方向
            ////    if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
            ////    {
            ////        /*CurY += 50;*/
            ////        GM_Select++;
            ////        if (GM_Select > 1)GM_Select = 0;
            ////    }
            //}




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
        }
        
    }
    return this;
}


void GameMain::Draw() const
{
    if (RoundUiflg == TRUE)
    {
        DrawBox(0, 0, 1280, 720, 0x00FFFF, TRUE);
        DrawString(550, 80, "Round", 0x000000, TRUE);
        if (Item::ReRound[0] == TRUE)
        {
            DrawGraph(0, 0, RoundBackImg1, TRUE);
            DrawString(550, 80, "Round", 0x00FFFF, TRUE);
        }
        if (Item::ReRound[1] == TRUE)
        {
            DrawGraph(0, 0, RoundBackImg2, TRUE);
            DrawString(550, 80, "Round", 0x8A2BE2, TRUE);
        }
       
        
    }


    if (ResultFlg == FALSE&& RoundUiflg == FALSE) {
        DrawGraph(0, 0, BackGRImg, TRUE);
        /* DrawGraph(370, 100, Enemyimg[ShuffleEnemyNum], FALSE);*/
        if (bh_flg == TRUE)
        {
            DrawGraph(370, 50, bullet_holes, TRUE);
        }
        BULLET->Draw();
        ENEMY->Draw();

        //ラウンド数描画
        SetFontSize(48);
        DrawFormatString(250, 30, 0xffffff, "%d", Round);

        SetFontSize(48);
        DrawFormatString(1220, 420, 0xffffff, "%d", P_life);

        //  //白枠
        //DrawBox(0, 5, 1280, 115, GetColor(255, 255, 255), TRUE);
        //DrawBox(10, 15, 1270, 105, GetColor(0, 0, 0), TRUE);
        //DrawBox(330, 5, 340, 105, GetColor(255, 255, 255), TRUE);
        //DrawBox(950, 5, 960, 105, GetColor(255, 255, 255), TRUE);
        //DrawBox(190, 105, 200, 500, GetColor(255, 255, 255), TRUE);
        //DrawBox(0, 105, 10, 500, GetColor(255, 255, 255), TRUE);
        //DrawBox(1090, 105, 1100, 500, GetColor(255, 255, 255), TRUE);
        //DrawBox(1270, 105, 1280, 500, GetColor(255, 255, 255), TRUE);
        //DrawBox(950, 5, 960, 105, GetColor(255, 255, 255), TRUE);
        //DrawBox(1090, 180, 1280, 190, GetColor(255, 255, 255), TRUE);
        //DrawBox(1090, 300, 1280, 310, GetColor(255, 255, 255), TRUE);
        //DrawBox(1090, 375, 1280, 385, GetColor(255, 255, 255), TRUE);
        //DrawBox(0, 500, 1280, 720, GetColor(255, 255, 255), TRUE);
        //DrawBox(10, 510, 1270, 710, GetColor(0, 0, 0), TRUE);
        //DrawBox(380, 500, 390, 710, GetColor(255, 255, 255), TRUE);
        //DrawBox(800, 500, 810, 710, GetColor(255, 255, 255), TRUE);
        //DrawBox(0, 560, 1280, 570, GetColor(255, 255, 255), TRUE);
        //DrawBox(140, 560, 150, 710, GetColor(255, 255, 255), TRUE);

        //SetFontSize(36);

        ////Life
        //DrawString(1140, 130, "ENEMY", 0xFF0000);
        //DrawString(1130, 325, "PLAYER", 0xFFFF00);
        //DrawGraph(1110, 225, E_LifeImg, TRUE);
        //DrawGraph(1110, 420, P_LifeImg, TRUE);
        //DrawFormatString(1180, 227, 0xffffff, ": ", E_life);
        //DrawFormatString(1180, 422, 0xffffff, ":", P_life);


        //SetFontSize(48);

        ////Round
        //DrawString(40, 35, "ROUND :", 0xE6E6FA);

        //   //Turn
        //DrawString(1130, 35, ":TURN", 0xEE82EE);

        ////Action

        //DrawString(250, 580, "SHOOT", 0xFF0000);
        //DrawString(247, 650, "ITEM", 0x87CEFA);
        //DrawString(620, 655, "PLAYER", 0xFFFF00);
        //DrawString(620, 580, "ENEMY", 0xFF0000);

        //SetFontSize(42);
        //DrawString(30, 515, "ACTION FOR SELF", 0xFFFF00);
        //DrawString(430, 515, "SHOOT FOR ALL !!", 0xFF0000);
        //DrawString(950, 515, "ITEM LIST", 0x87CEFA);
        //DrawString(410, 618, "SHOOT:", 0xFF0000);


        //SetFontSize(24);
        //     DrawString(35, 575, "BUTTON", 0xFFFFFF);
        //    DrawString(65, 605, "A", 0x9ACD32);
        //    DrawString(25, 630, "DECISION", 0x9ACD32);
       
        //    DrawString(65, 655, "B", 0xFF0000);
        //    DrawString(45, 680, "BACK", 0xFF0000);
     
       
          //if (P_Ui[1] == FALSE)
          //{
          //   /* DrawBox(390, 510, 800, 560, 0x000000, TRUE);*/
          //    DrawBox(390, 570, 800, 710, 0x000000, TRUE);
          //}
        
       
          //カーソル

        DrawGraph(CurX, CurY, CursolImg[0], TRUE);
        if (P_Ui[1] == TRUE)
        {
            DrawGraph(CurX2, CurY2, CursolImg[1], TRUE);
            DrawLine(190, 630, 375, 630, 0xFFFF00);
        }
        if (P_Ui[2] == TRUE)
        {
            DrawGraph(CurX3, CurY3, CursolImg[2], TRUE);
            DrawLine(190, 700, 375, 700, 0xFFFF00);
           
        }
       
          /*  if (isPlayerTurn == TRUE)
            {
                DrawString(1130, 350, "PLAYER", 0xFFFF00);
            }
            else
            {
                DrawString(1135, 350, "ENEMY", 0xfa2000);
            }*/




            //プレイヤーか敵を選ぶ



        if (bh2_flg == TRUE)
        {
            DrawGraph(-150, -600, bullet_holes2, TRUE);
        }


    }



    SetFontSize(48);
        if (ResultFlg == TRUE) {

            DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
          
            DrawGraph(5, 10, ResultBackImg[0], TRUE);
            if (flash == 1|| flash == 7)
            {
                DrawGraph(5, 10, ResultBackImg[1], TRUE);
            }
            if (flash == 2 || flash == 8)
            {
                DrawGraph(5, 10, ResultBackImg[2], TRUE);
            }
            if (flash == 3 || flash == 9)
            {
                DrawGraph(5, 10, ResultBackImg[3], TRUE);
            }
            if (flash == 4 || flash == 10)
            {
                DrawGraph(5, 10, ResultBackImg[4], TRUE);
            }
            if (flash == 5 || flash == 11)
            {
                DrawGraph(5, 10, ResultBackImg[5], TRUE);
            }
            if (flash == 6 || flash == 12)
            {
                DrawGraph(5, 10, ResultBackImg[6], TRUE);
            }
            DrawGraph(220, 180, P_LifeImg, TRUE);

            DrawFormatString(430, 310, 0xFFFFFF, "TOTAL:  %d   ROUND", Round);
            DrawString(550, 80, "RESULT", 0xFF0000);
            DrawString(400, 650, "PRESS _A_ BACK TITLE", 0x32CD32);

        }


        if (PushFlg == TRUE && Item::itemtable[4] == 1 && Flash <= 80 && PushFlgUI != 1
            || Item::TotemRand == 0 && PushFlgUI == 1 && Flash <= 80 && PushFlg == TRUE && Item::itemtable[4] == 1) {
            DrawBox(460, 440, 830, 580, 0xADD8E6, TRUE);
            DrawString(585, 390, "PUSH!", 0xFFFF00);
            DrawString(575, 590, "START!", 0xFFFF00);
           
        }
        if (PushFlg == TRUE && Item::itemtable[4] == 1 && PushFlgUI != 1 ||
            Item::TotemRand == 0 && PushFlgUI == 1 && PushFlg == TRUE && Item::itemtable[4] == 1)
        {
            DrawBox(480, 460, 810, 560, 0xffffff, TRUE);
            DrawTriangle(590, 470, 590, 550, 710, 510, 0xFF0000, TRUE);
           
        }



        if (PushFlg == TRUE && Item::itemtable[4] == 1 && Flash <= 80 &&
            PushFlgUI == 1 && Item::TotemRand == 1)
        {
            DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
            DrawBox(80, 80, 1200, 640, 0xFFFF00, TRUE);
            SetFontSize(72);
            DrawString(520, 0, "PUSH!!", 0xFFFF00);
            DrawString(500, 640, "START!!", 0xFFFF00);
        }

        if (PushFlg == TRUE && Item::itemtable[4] == 1 && PushFlgUI == 1
            && Item::TotemRand == 1)
        {
            DrawBox(150, 150, 1130, 570, 0x0000FF, TRUE);
           
            DrawTriangle(470, 160, 470, 560, 900, 370, 0xFF0000, TRUE);
          
           
        }

        ITEM->Draw();
 
}






void GameMain::Turn()
{
    TurnCount = bullet::FireC;


    //if (isPlayerTurn == FALSE)
    //{
    //    //敵がプレイヤーを選択
    //    if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && isPlayerTurn == FALSE)
    //    {
    //        if (bullet::Cylinder[bullet::FireC] == 1 && isPlayerTurn == FALSE)
    //        {
    //            P_life--;
    //            isPlayerTurn = TRUE;
    //        }
    //        else
    //        {
    //            isPlayerTurn = TRUE;
    //        }
    //    }
    //    WaitFlg = FALSE;
    //}
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
            Item::Bomb = FALSE;
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
        PushSEflg = FALSE;
        ResultBgmFlg = TRUE;
        isPlayerTurn = TRUE;
        bh2_flg = FALSE;
        ResultFlg = FALSE;
        PushFlg = FALSE;
        PushFlgUI = 0;
        Flash = 0;
        FreezUI = FALSE;
        ITEM->INIT();
        RoundUiflg = TRUE;

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
        RoundUiflg = TRUE;
    }
    
}


void GameMain::P_UI()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
    {
        P_UI_INIT();
    }

    if (P_Ui[0] == TRUE)
    {
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) && CurX == 180 && CurY == 576)
        {
            CurX = 180; 
            CurY = 645;
        }
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) && CurX == 180 && CurY == 645)
        {
            CurX = 180;
            CurY = 576;
        }
        if (CurX == 180 && CurY == 576 && WaitFlg2 == TRUE
            && PAD_INPUT::OnRelease(XINPUT_BUTTON_A))
        {
            P_Ui[1] = TRUE;
            P_Ui[0] = FALSE;
        }

        if (CurX == 180 && CurY == 645 && WaitFlg2 == TRUE
            && PAD_INPUT::OnRelease(XINPUT_BUTTON_A))
        {
            P_Ui[2] = TRUE;
            P_Ui[0] = FALSE;
        }
    }

    if (P_Ui[1] == TRUE)
    {
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) && CurX2 == 555 && CurY2 == 575)
        {
            CurX2 = 555;
            CurY2 = 650;
        }
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) && CurX2 == 555 && CurY2 == 650)
        {
            CurX2 = 555;
            CurY2 = 575;
        }
        if (CurX2 == 555 && CurY2 == 575 
            && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
        {
            E_Choice();
        }
        if (CurX2 == 555 && CurY2 == 650
            && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
        {
            P_Choice();
        }
    }

    if (P_Ui[2] == TRUE)
    {
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) &&CurY3 == 590)
        {         
            CurY3 = 640;
        }
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) && CurY3 == 640)
        {
            CurY3 = 590;
        }

        if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)&&CurX3!=1100)
        {
            CurX3 += 135;
        }
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT) && CurX3 != 830)
        {
            CurX3 -= 135;
        }
        if (CurX3 == 830 && CurY3 == 590
            && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
        {
            ITEM->DRAG();
        }
        if (CurX3 == 935 && CurY3 == 590
            && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
        {
            ITEM->LOUPE();
        }
        if (CurX3 == 1070 && CurY3 == 590
            && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
        {
            ITEM->JUDGE();
        }
       /* if (CurX3 == 555 && CurY3 == 650
            && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
        {
            P_Choice();
        }
        if (CurX3 == 555 && CurY3 == 575
            && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
        {
            E_Choice();
        }
        if (CurX3 == 555 && CurY3 == 650
            && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
        {
            P_Choice();
        }*/

    }
       
}


void GameMain::P_UI_INIT()
{
    P_Ui[0] = TRUE;
   
    CurX2 = 555;
    CurY2 = 575;
    CurX3 = 830;
    CurY3 = 590;


    for (int i = 1; i < 5; i++)
    {
        P_Ui_flg[i] = FALSE;
    }

    for (int i = 1; i < 5; i++)
    {
        P_Ui[i] = FALSE;
    }


}

void GameMain::ROUND_UI()
{
    if (RoundUiflg == TRUE && PAD_INPUT::OnRelease(XINPUT_BUTTON_A))
    {
      
        RoundUiflg = FALSE;
        Enemy::E_WaitFlg = TRUE;
        INIT();
        Item::ReRound[0] = FALSE;
        Item::ReRound[1] = FALSE;
    }


}

