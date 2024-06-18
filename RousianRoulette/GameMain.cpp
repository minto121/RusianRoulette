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
#include "FpsControl.h"


int GameMain::E_life;
int GameMain::P_life;
int GameMain::bh_flg;
int GameMain::bh2_flg;
int GameMain::PushFlgUI;
int GameMain::FreezUI;
int GameMain::ResultBgm2;
int GameMain::FreezDiray;


enum class CURSOL
{
    C_ENEMY = 0,
    C_PLAYER
};


bool GameMain::isPlayerTurn;


GameMain::GameMain()
{
    BULLET = new bullet;
    ITEM = new Item;
    TIMER = new Timer;
    ENEMY = new Enemy;
  /*  R = 2000;*/
    P_life = 2;
    E_life = 2;
    Round = 0;
    ResultFlg = /*FALSE*/TRUE;
  
    INIT();
   /* RoundUiflg = TRUE;*/
}


void GameMain::INIT()
{
    CurX = 180;
    CurY = 576;
    P_UI_INIT();
    flash = 0;
  
   
    TurnCount = 0;

    for (int a = 0; a <= 1; a++) {
        A_UI[a]=FALSE;
    }

    AT = 0;
    ET = 0;
    //Turn = 1;
   /* isPlayerTurn = TRUE;*/
    Enemyimg[0] = LoadGraph("Resources/images/reaper.png");
    Enemyimg[1] = LoadGraph("Resources/images/skeleton.png");
    Enemyimg[2] = LoadGraph("Resources/images/mummy.png");
    Enemyimg[3] = LoadGraph("Resources/images/shocker.png");
    Enemyimg[4] = LoadGraph("Resources/images/devil.png");
    bullet_holes = LoadGraph("Resources/images/k0100_1.png");
    bullet_holes2 = LoadGraph("Resources/images/Item/Red.png");
    P_LifeImg = LoadGraph("Resources/images/P_Life.png");
    E_LifeImg = LoadGraph("Resources/images/E_Life.png");
    BackGRImg = LoadGraph("Resources/images/BG.png");
    CursolImg[0] = LoadGraph("resouce/image/cursor3.png");
    CursolImg[1] = LoadGraph("resouce/image/cursor2.png");
    CursolImg[2] = LoadGraph("resouce/image/cursor4.png");

    PushSE = LoadSoundMem("Resources/SE/Push.mp3");
    PushSE2 = LoadSoundMem("Resources/SE/Push2.mp3");
    ResultBgm = LoadSoundMem("Resources/BGM/Result/result.mp3");
    ResultBgm2 = LoadSoundMem("Resources/BGM/Result/Result2.mp3");
    ResultBackImg[0] = LoadGraph("Resources/images/Result/Result1.png");
    ResultBackImg[1] = LoadGraph("Resources/images/Result/Result2.png");
    ResultBackImg[2] = LoadGraph("Resources/images/Result/Result3.png");
    ResultBackImg[3] = LoadGraph("Resources/images/Result/Result4.png");
    ResultBackImg[4] = LoadGraph("Resources/images/Result/Result5.png");
    ResultBackImg[5] = LoadGraph("Resources/images/Result/Result6.png");
    ResultBackImg[6] = LoadGraph("Resources/images/Result/Result7.png");
    ResultBackImg[7] = LoadGraph("Resources/images/Result/ResultBackImg.png");
    ResultBackImg[8] = LoadGraph("Resources/images/Result/ResultBackImg2.png");
    ResultBackImg[9] = LoadGraph("Resources/images/Result/ResultBackImg3.png");

    RoundBackImg1 = LoadGraph("Resources/images/Round/ROUND1.png");
    RoundBackImg2 = LoadGraph("Resources/images/Round/ROUND2.png");
    RoundBackImg3 = LoadGraph("Resources/images/Round/ROUND3.png");
    REnemyimg = LoadGraph("Resources/images/RinjiEnemy.png");

    UraBotanSE = LoadSoundMem("Resources/SE/UraBotann.mp3");
   RoundButtonSE = LoadSoundMem("Resources/sounds/kettei.mp3");
    ShuffleEnemyNum = 0;
    LastEnemyNum = -1;
    GMBgm = LoadSoundMem("Resources/sounds/destruct.wav");
    SelectSE = LoadSoundMem("Resources/sounds/cursorsound.mp3");
    ShotSE = LoadSoundMem("Resources/sounds/Gunshot.mp3");
    NshotSE = LoadSoundMem("Resources/sounds/not shot.mp3");
    TotemChanceBgm = LoadSoundMem("Resources/BGM/Result/TotemChance1.mp3");


    isPlayerTurn = TRUE;

    WaitFlg = FALSE;
    WaitFlg2 = 0;
    WaitFlg3 = FALSE;
    WaitFlg4 = FALSE;
    UraBotanFlg = TRUE;

    /*ResultFlg = TRUE;*/
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
    FreezDiray = 0;
    RoundUiflg = FALSE;
}


GameMain::~GameMain()
{
    for (int i = 0; i < IMAGE_CNT - 1; i++)
    {
        DeleteGraph(Enemyimg[i]);
    }
    DeleteSoundMem(GMBgm);
    DeleteSoundMem(SelectSE);
    DeleteSoundMem(ShotSE);
    DeleteSoundMem(NshotSE);
}


AbstractScene* GameMain::Update()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_X))
    {
        return new Title();
    }
    ROUND_UI();
   
    



    if (RoundUiflg == FALSE)
    {
        //BGM
            if (ResultFlg == FALSE) {
            ChangeVolumeSoundMem(75, GMBgm);
            PlaySoundMem(GMBgm, DX_PLAYTYPE_LOOP, FALSE);
            }
          
            if (ResultFlg == TRUE && ResultBgmFlg == TRUE)
            {
             
                StopSoundMem(GMBgm);
                PlaySoundMem(ResultBgm, TRUE);
                ChangeVolumeSoundMem(255, ResultBgm2);
                PlaySoundMem(ResultBgm2, DX_PLAYTYPE_LOOP, FALSE);
                ResultBgmFlg = FALSE;
            }

           
  

        //Result
            if (PushFlg == TRUE) {

                StopSoundMem(ResultBgm2);
                Flash++;
                if (Flash == 60)
                {
                    Flash = 0;
                }
                if (Flash == 1 && PushFlgUI != 1 && PushSEflg == FALSE) {
                    PlaySoundMem(PushSE, DX_PLAYTYPE_BACK);
                    PushSEflg = TRUE;
                }
                if (Flash == 1 && PushFlgUI == 1 && PushSEflg == FALSE && Item::TotemRand == 1) {
                    PlaySoundMem(PushSE2, DX_PLAYTYPE_BACK);
                    PushSEflg = TRUE;
                }

                if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER) && flash == 0 && Item::TotemRand == 1 && UraBotanFlg == TRUE)
                {

                    int a = GetRand(1);
                    if (a == 0) {
                        flash = 1;
                        UraBotanFlg = FALSE;
                    }
                    if (a == 1) {
                        UraBotanFlg = FALSE;
                    }
                }
                if (flash >= 1)
                {
                    if (Flash % 5 == 0)
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

            if (PAD_INPUT::OnRelease(XINPUT_BUTTON_A) && ResultFlg == TRUE && Item::WaitTime == FALSE
                && Item::itemtable[4]== 0 && Item::Freez == FALSE)
            {
                FreezDiray = 2;
            }
          

            if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && ResultFlg == TRUE && Item::itemtable[4] >= 1 &&WaitFlg4 == FALSE)
            {
                StopSoundMem(ResultBgm2);
                if (WaitFlg3 == FALSE)
                {
                   PushFlgUI = 5/*GetRand(5)*/;
          
                }
      
                P_UI_INIT();
       
                PlaySoundMem(TotemChanceBgm, DX_PLAYTYPE_LOOP, FALSE);
                WaitFlg3 = TRUE;
                PushFlg = TRUE;
          
        
            }


            //freez
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && ResultFlg == TRUE && Item::WaitTime == FALSE
                && Item::itemtable[4] >= 1 && Item::Freez == TRUE &&FreezDiray == 0)
            {
               
                FreezDiray += 2;
            }
            if (FreezDiray >= 2)
            {
                FreezDiray++;
                if (FreezDiray == 58)
                {
                    StopSoundMem(ResultBgm2);
                }
                if (FreezDiray == 60)
                {
                    if (Item::itemtable[4] >= 1 && Item::Freez == TRUE) {
                        FreezUI = TRUE;
                        FreezDiray = 1;
                    }
                    if (Item::itemtable[4] == 0 && Item::TotemRand == 0 && Item::Freez == FALSE)
                    {
                      
                        return new Title();
                        FreezDiray = 1;
                       
                      
                    }
                }
            }



            Result();


            ITEM->Update();



     //ゲームメイン
            if (ResultFlg == FALSE && P_life > 0 && FreezUI == FALSE)
            {
                if (A_UI[1] == TRUE) {
                    AT++;
                    if (AT == 100) {
                        AT = 0;
                        A_UI[1] = FALSE;
                    }
                }

                if (A_UI[0] == TRUE) {
                    AT++;
                    if (AT == 100) {
                        AT = 0;
                        A_UI[0] = FALSE;
                    }
                }

                if (E_life <= 0)
                {
                    ET++;
                }


                if (Timer::FPS >= 10) {
                    WaitFlg2 = TRUE;

                }
                if (isPlayerTurn == FALSE && Timer::FPS == 250)
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
               

                if (Timer::FPS == 100 || Timer::FPS == 299)
                {
                    bh_flg = FALSE;
                    bh2_flg = FALSE;
                }

              

            
            }
        
    }




    return this;
}


void GameMain::Draw() const
{
    if (RoundUiflg == TRUE)
    {
        SetFontSize(160);
        if (Item::ReRound[0] == FALSE && Item::ReRound[1] == FALSE)
        {
            DrawGraph(0, 0, RoundBackImg1, TRUE);
            DrawFormatString(860, 222, 0xFFFFFF, "%d", Round+1);
        }
        if (Item::ReRound[0] == TRUE)
        {
            DrawGraph(0, 0, RoundBackImg2, TRUE);
            DrawFormatString(860, 222, 0xFF0000, "%d", Round+1);
        }
        if (Item::ReRound[1] == TRUE)
        {
            DrawGraph(0, 0, RoundBackImg3, TRUE);
            DrawFormatString(860, 222, 0x8A2BE2, "%d", Round+1);
            
        }
       
        
    }


    //ゲームメイン
    if (ResultFlg == FALSE&& RoundUiflg == FALSE) {

        //背景
        DrawGraph(0, 0, BackGRImg, TRUE);

        //敵
        if (E_life > 0) {
            /*  DrawGraph(370, 100, Enemyimg[ShuffleEnemyNum], TRUE);*/
            DrawGraph(520, 170, REnemyimg, TRUE);
        }

        if (bh_flg == TRUE)
        {
           
            DrawGraph(370, 50, bullet_holes, TRUE);
        }
        BULLET->Draw();
        ENEMY->Draw();

        //ラウンド数描画
        SetFontSize(48);
        DrawFormatString(250, 30, 0xffffff, "%d", Round);

        //ライフ
        SetFontSize(48);
        DrawFormatString(1220, 420, 0xffffff, "%d", P_life);
        DrawFormatString(1220, 220, 0xffffff, "%d", E_life);
      
        //アイテム
        SetFontSize(28);
        DrawFormatString(940, 600, 0xffffff, "%d", Item::itemtable[0]);
        DrawFormatString(940, 650, 0xffffff, "%d", Item::itemtable[1]);
        DrawFormatString(1080, 600, 0xffffff, "%d", Item::itemtable[2]);
        DrawFormatString(1220, 600, 0xffffff, "%d", Item::itemtable[3]);
        DrawFormatString(1080, 650, 0xffffff, "%d", Item::itemtable[4]);
        DrawFormatString(1180, 650, 0xffffff, "%d", Item::itemtable[5]);

      //if()
      //  DrawString(450, 40, "USE DRAG", 0xffffff);
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
       
        //ターン
            if (isPlayerTurn == TRUE)
            {
                SetFontSize(48);
                DrawString(980, 35, "PLAYER", 0xFFFF00);
            }
            else
            {
                SetFontSize(48);
                DrawString(990, 35, "ENEMY", 0xfa2000);
            }

            //アクションUI
            SetFontSize(36);
            if (A_UI[0] == TRUE)
            {
                DrawString(450, 40, "PLAYER", 0xfa2000, TRUE);
                DrawString(560, 40, ": SHOT ENEMY!!", 0xffffff, TRUE);
            }

            if (A_UI[1] == TRUE)
            {
                DrawString(460, 40, "PLAYER", 0xfa2000, TRUE);
                DrawString(570, 40, ": SHOT SELF!!", 0xffffff, TRUE);
            }

      


        if (bh2_flg == TRUE)
        {
            DrawCircle(660, 350, 150, 0x000000);
            DrawGraph(-150, -650, bullet_holes2, TRUE);
        }


    }


    //リザルト画面
   
   
        if (ResultFlg == TRUE) {
            DrawGraph(0, 0, ResultBackImg[7], TRUE);
            SetFontSize(78);
         
           
            DrawFormatString(830, 280, 0xFF0000, "%d", Round);


            if (Item::itemtable[4] >= 1 && Item::Freez == TRUE && FreezDiray >= 57)
            {
                DrawGraph(0, 0, ResultBackImg[9], FALSE);
            }

        }


        SetFontSize(48);

        //Push
  
        if (PushFlg == TRUE && Item::itemtable[4] >= 1  && PushFlgUI != 1
            || Item::TotemRand == 0 && PushFlgUI == 1  && PushFlg == TRUE && Item::itemtable[4] == 1) {
           /*DrawBox(0,0,1280,720,0x000000,TRUE)*/
            DrawGraph(0, 0, ResultBackImg[8], FALSE);
            if (Flash <= 40) {
                
                DrawBox(490, 510, 860, 650, 0x332c2c, TRUE);


                DrawBox(605, 450, 740, 510, 0x000000, TRUE);
                DrawBox(605, 650, 780, 700, 0x000000, TRUE);
                DrawString(615, 460, "PUSH!", 0xFF0000);
                DrawString(605, 660, "START!", 0xFF0000);
                DrawBox(510, 530, 840, 630, 0x645959, TRUE);
                DrawTriangle(620, 540, 620, 620, 740, 580, 0xFFFFFF, FALSE);
            }

           
        }
       


        //bigpush
        if (PushFlg == TRUE && Item::itemtable[4] >= 1 && Flash <= 40 &&
            PushFlgUI == 1 && Item::TotemRand == 1)
        {
            DrawGraph(0, 0, ResultBackImg[8], FALSE);
            DrawBox(80, 80, 1200, 640, 0x645959, TRUE);
            SetFontSize(72);
            DrawString(520, 0, "PUSH!!", 0xFF0000);
            DrawString(500, 640, "START!!", 0xFF0000);
            DrawBox(150, 150, 1130, 570, 0x3a3232, TRUE);

            DrawTriangle(470, 160, 470, 560, 900, 370, 0xFFFFFF, FALSE);
        }

      /*  if (PushFlg == TRUE && Item::itemtable[4] >= 1 && PushFlgUI == 1
            && Item::TotemRand == 1)
        {
            
          
           
        }*/


        //URABOTAN
        if (flash == 1 || flash == 7)
        {
            DrawGraph(-25, 60, ResultBackImg[1], TRUE);
        }
        if (flash == 2 || flash == 8)
        {
            DrawGraph(-25, 60, ResultBackImg[2], TRUE);
        }
        if (flash == 3 || flash == 9)
        {
            DrawGraph(-25, 60, ResultBackImg[3], TRUE);
        }
        if (flash == 4 || flash == 10)
        {
            DrawGraph(-25, 60, ResultBackImg[4], TRUE);
        }
        if (flash == 5 || flash == 11)
        {
            DrawGraph(-25, 60, ResultBackImg[5], TRUE);
        }
        if (flash == 6 || flash == 12)
        {
            DrawGraph(-25, 60, ResultBackImg[6], TRUE);
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
    if (A_UI[0] == FALSE) {
        A_UI[0] = TRUE;
    }
    if (WaitFlg == FALSE)
    {
        WaitFlg = !WaitFlg;
    }
    if (bullet::Cylinder[bullet::FireC] == 1)
    {
        PlaySoundMem(ShotSE, DX_PLAYTYPE_BACK);
        bh_flg = TRUE;
        PlaySoundMem(ShotSE, DX_PLAYTYPE_BACK);
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

        if (A_UI[1] == FALSE) {
            A_UI[1] = TRUE;
        }

       

        if (bullet::Cylinder[bullet::FireC] == 1)
        {
            bh2_flg = TRUE;
            PlaySoundMem(ShotSE, DX_PLAYTYPE_BACK);
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

    if (PushFlg == TRUE && Item::itemtable[4] >= 1 &&
        PAD_INPUT::OnButton(XINPUT_BUTTON_START))
    {
        StopSoundMem(TotemChanceBgm);
      /*  Item::itemtable[4] -= 1;*/
        WaitFlg3 = FALSE;
        WaitFlg4 = TRUE;
        PushFlg = FALSE;
        P_life = 2;
        Item::TotemFlg = TRUE;



    }



    if (Item::R4 == 425)
    {
        Item::ReRound[0] = TRUE;
      
       
      /*  PushSEflg = FALSE;
        ResultBgmFlg = TRUE;
        isPlayerTurn = TRUE;
        bh2_flg = FALSE;*/
        ResultFlg = FALSE;
      /*  PushFlg = FALSE;
        PushFlgUI = 0;
        Flash = 0;*/
    /*    FreezUI = FALSE;*/
        ITEM->INIT();
        Item::itemtable[4] -= 1;
        RoundUiflg = TRUE;

    }


    if (Item::R3 == 425)
    {
        Item::ReRound[0] = FALSE;
        Item::ReRound[1] = TRUE;
       
     /*   isPlayerTurn = TRUE;
        bh2_flg = FALSE;*/
        ResultFlg = FALSE;
       /* PushFlg = FALSE;
        PushFlgUI = 0;
        Flash = 0;
        Item:: Freez = FALSE;*/
        FreezUI = FALSE;
       
       
        ITEM->INIT();
        Item::itemtable[4] -= 1;
        RoundUiflg = TRUE;
    }
    
}


void GameMain::P_UI()
{
    if (Item::J_Player_Flg == FALSE && Item::J_Enemy_Flg == FALSE && Item::DRAG_Flg == FALSE && Item::Bomb_Flg == FALSE &&
        Item::C_BULLET_Flg == FALSE && Item::L_Check == 0)
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
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) && CurY3 == 590)
            {
                CurY3 = 640;
            }
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) && CurY3 == 640)
            {
                CurY3 = 590;
            }

            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT) && CurX3 != 1100)
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
            if (CurX3 == 965 && CurY3 == 590
                && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
            {
                ITEM->LOUPE();
            }
            if (CurX3 == 1100 && CurY3 == 590
                && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
            {
                ITEM->JUDGE();
            }
            if (CurX3 == 830 && CurY3 == 640
                && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
            {
                ITEM->BOMB();
            }
            if (CurX3 == 1100 && CurY3 == 640
                && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
            {
                ITEM->C_BULLET();
            }

        }
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
  
    
        if (ET == 60)
        {
            RoundUiflg = TRUE;
            E_life = 2;
        }
  
    if (RoundUiflg == TRUE && PAD_INPUT::OnRelease(XINPUT_BUTTON_A))
    {
        StopSoundMem(GMBgm);
        PlaySoundMem(RoundButtonSE, TRUE);
        Enemy::E_WaitFlg = TRUE;
        Item::ReRound[0] = FALSE;
        Item::ReRound[1] = FALSE;
      
        ROUND_UP();
       
        RoundUiflg = FALSE;
    }
  
   
}


void GameMain::ROUND_UP()
{
    //敵のHPがなくなるとラウンドが進み弾がリロードされる
    
        Round++;
       
        isPlayerTurn = TRUE;
        do
        {
            ShuffleEnemyNum = GetRand(IMAGE_CNT - 1);
        } while (ShuffleEnemyNum == LastEnemyNum);

        LastEnemyNum = ShuffleEnemyNum;

        Item:: ReRound[0] = FALSE;
        Item::ReRound[1] = FALSE;
       
        BULLET->B_INIT();
        ITEM->INIT();
        ITEM->GETITEM();
        ENEMY->E_INIT();
        P_UI_INIT();
        WaitFlg = FALSE;

        E_life = 2;
        Timer::FPS = 0;
        INIT();
      
     
   
}

