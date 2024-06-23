#include "DxLib.h"
#include <math.h>
#include "GameMain.h"
#include "PadInput.h"
#include "bullet.h"
#include "Title.h"
#include "Timer.h"
#include "Enemy.h"
#include "Item.h"
#include "FpsControl.h"
#include "InputRanking.h"


int GameMain::E_life;
int GameMain::P_life;
int GameMain::bh_flg;
int GameMain::bh2_flg;
int GameMain::PushFlgUI;
int GameMain::FreezUI;
int GameMain::ResultBgm2;
int GameMain::FreezDiray;
int GameMain::BulettCount_UI;
int GameMain::TurnTime;
int GameMain::GMBgm;

enum class CURSOL
{
    C_ENEMY = 0,
    C_PLAYER
};


bool GameMain::isPlayerTurn;


GameMain::GameMain()
{
    ShuffleEnemyNum = 0;
    BULLET = new bullet;
    ITEM = new Item;
    TIMER = new Timer;
    ENEMY = new Enemy;
  /*  R = 2000;*/
    P_life = 2;
    E_life = 2;
    Round = 0;
    ResultFlg = FALSE/*TRUE*/;
  
    INIT();
    RoundUiflg = TRUE;


    Enemyimg[0] = LoadGraph("Resources/images/reaper.png");
    Enemyimg[1] = LoadGraph("Resources/images/skeleton.png");
    Enemyimg[2] = LoadGraph("Resources/images/mummy.png");
    Enemyimg[3] = LoadGraph("Resources/images/shocker.png");
    Enemyimg[4] = LoadGraph("Resources/images/devil.png");
    Enemyimg[5] = LoadGraph("Resources/images/ghost.png");
    Enemyimg[6] = LoadGraph("Resources/images/sinigami.png");
    Enemyimg[7] = LoadGraph("Resources/images/zombie.png");
    bullet_holes = LoadGraph("Resources/images/NewBh.png");
    bullet_holes2 = LoadGraph("Resources/images/White.png");
    bullet_holes3 = LoadGraph("Resources/images/NewBh2.5.png");
    P_LifeImg = LoadGraph("Resources/images/P_Life.png");
    E_LifeImg = LoadGraph("Resources/images/E_Life.png");
    BackGRImg = LoadGraph("Resources/images/BG.png");
    BackGR_PlayerImg = LoadGraph("Resources/images/BG_Player.png");
    BackGR_EnemyImg = LoadGraph("Resources/images/BG_Enemy.png");
    CursolImg[0] = LoadGraph("resouce/image/cursor3.png");
    CursolImg[1] = LoadGraph("resouce/image/cursor2.png");
    CursolImg[2] = LoadGraph("resouce/image/cursor4.png");
    Bakuhatsu_Img = LoadGraph("Resources/images/Item2/bakuhatsu.png");
    PTurnImg = LoadGraph("Resources/images/PlayerTurn.png");
    ETurnImg = LoadGraph("Resources/images/Enemyturn.png");

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

    BulletCount_Img = LoadGraph("Resources/images/Bullet/BulletUIImg1.png");
    BulletCount_Img2 = LoadGraph("Resources/images/Bullet/BulletUIImg2.png");
    BulletCount_Img3 = LoadGraph("Resources/images/Bullet/BulletUIImg3.png");
    missImg = LoadGraph("Resources/images/PSE_Miss.png");

    A_shotImg = LoadGraph("resouce/image/AShot.png");

    Totem2Img = LoadGraph("Resources/images/Result/TotemBegin.png");

    


    UraBotanSE = LoadSoundMem("Resources/SE/UraBotann.mp3");
    RoundButtonSE = LoadSoundMem("Resources/sounds/kettei.mp3");

    LastEnemyNum = -1;
    GMBgm = LoadSoundMem("Resources/sounds/destruct.wav");
    SelectSE = LoadSoundMem("Resources/sounds/cursorsound.mp3");
    ShotSE = LoadSoundMem("Resources/sounds/Gunshot.mp3");
    NshotSE = LoadSoundMem("Resources/sounds/not shot.mp3");
    TotemChanceBgm = LoadSoundMem("Resources/BGM/Result/TotemChance1.mp3");
    GM_SelectSE = LoadSoundMem("Resources/SE/Cursol.wav");
    P_UI_SE[0] = LoadSoundMem("Resources/SE/PUI[0]SE.mp3");
    P_UI_SE[1] = LoadSoundMem("Resources/SE/PUI[1]SE.mp3");
    P_UI_SE[2] = LoadSoundMem("Resources/SE/Cancel.mp3");
    Totem2SE = LoadSoundMem("Resources/SE/TotemCutin.mp3");
}


void GameMain::INIT()
{
    CurX = 180;
    CurY = 576;
    P_UI_INIT();
    flash = 0;
    TurnTime =0;
   
    TurnCount = 0;
    TotemTime = 0;

    for (int a = 0; a <= 1; a++) {
        A_UI[a]=FALSE;
    }

    AT = 0;
    ET = 0;
   

  
    PSP_hit_Flg = FALSE;
    PSP_miss_Flg = FALSE;
    PSE_hit_Flg = FALSE;
    PSE_miss_Flg = FALSE;


    //Turn = 1;
   /* isPlayerTurn = TRUE;*/
   

    

    
  

 /*   BlankSE = LoadSoundMem("Resources/SE/kuuhou.wav");*/


    isPlayerTurn = TRUE;
    BK_Flg = FALSE;

    WaitFlg = FALSE;
    WaitFlg2 = 0;
    WaitFlg3 = FALSE;
    WaitFlg4 = FALSE;
    UraBotanFlg = TRUE;

    BulettCount_UI = 0;

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
   
    ROUND_UI();
   
    if (E_life <= 0)
    {
        ShuffleEnemyNum = GetRand(7);
    }



    if (RoundUiflg == FALSE)
    {

       


        //BGM
            if (ResultFlg == FALSE&&RoundUiflg == FALSE&& BulettCount_UI == 181) {
            ChangeVolumeSoundMem(75, GMBgm);
            PlaySoundMem(GMBgm, DX_PLAYTYPE_LOOP, FALSE);
            }

            if (RoundUiflg == TRUE|| BulettCount_UI != 181||ET!=0||a ==1)
            {
                StopSoundMem(GMBgm);
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
                PlaySoundMem(RoundButtonSE, DX_PLAYTYPE_BACK);
                FreezDiray = 2;
            }
          

            if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && ResultFlg == TRUE && Item::itemtable[4] >= 1 &&WaitFlg4 == FALSE)
            {
               
                if (WaitFlg3 == FALSE)
                {
                   PushFlgUI = GetRand(5);
          
                }
                StopSoundMem(ResultBgm2);
                    TotemTime += 1;
              
              
                    PlaySoundMem(Totem2SE, DX_PLAYTYPE_BACK);
                    WaitFlg4 = TRUE;
        
            }
            if (TotemTime != 0 && TotemTime < 180)
            {
                TotemTime++;
               
            }
            if (TotemTime == 180)
            {
                P_UI_INIT();

                PlaySoundMem(TotemChanceBgm, DX_PLAYTYPE_LOOP, FALSE);
                WaitFlg3 = TRUE;
               
                PushFlg = TRUE;
                TotemTime = 0;
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
                if (FreezDiray == 28)
                {
                    StopSoundMem(ResultBgm2);
                }
                if (FreezDiray == 30)
                {
                    if (Item::itemtable[4] >= 1 && Item::Freez == TRUE) {
                        FreezUI = TRUE;
                        FreezDiray = 1;
                    }
                    if (Item::itemtable[4] == 0 && Item::TotemRand == 0 && Item::Freez == FALSE)
                    {
                      
                        return new InputRankingScene(Round);
                        FreezDiray = 1;
                       
                      
                    }
                }
            }



            Result();


            ITEM->Update();



     //ゲームメイン
            if (ResultFlg == FALSE && P_life > 0 && FreezUI == FALSE)
            {
                BULLET->Update();
                
               
                 BulettUI();

                


                 if (BulettCount_UI == 181)
                 {

                     if (TurnTime != 120)
                     {
                         TurnTime++;
                     }
                     if (TurnTime == 120)

                     {
                         if (isPlayerTurn == TRUE)
                         {
                             P_UI();
                         }

                         P_Choice();
                         E_Choice();


                         if (Timer::FPS >= 10) {
                             WaitFlg2 = TRUE;

                         }
                         if (isPlayerTurn == FALSE/* && Timer::FPS == 250*/)
                         {
                             P_UI_INIT();
                         }



                         ENEMY->Update();
                         TIMER->Update();
                         //Choice();
                         Turn();

                     }

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

       
       
        if (isPlayerTurn == FALSE)
        {
            DrawGraph(0, 0, BackGR_EnemyImg, TRUE);
        }
        if (isPlayerTurn == TRUE)
        {
            DrawGraph(0, 0, BackGR_PlayerImg, TRUE);
        }

        if (TurnTime <= 119)
        {
            if (isPlayerTurn == TRUE)
            {
                DrawGraph(200, 115, PTurnImg, FALSE);
            }
            if (isPlayerTurn == FALSE)
            {
                DrawGraph(200, 115, ETurnImg, FALSE);
            }
        }
        //敵
        if (E_life > 0&&TurnTime ==120) {
              DrawGraph(450, 140, Enemyimg[ShuffleEnemyNum], TRUE);
          
        }



       

       





        if (bh_flg == TRUE&&Item::Bomb_Flg==FALSE)
        {
           
            DrawGraph(200, 110, bullet_holes, TRUE);
        }
        if (BK_Flg == TRUE)
        {
            DrawExtendGraph(350, 120, 950, 490, Bakuhatsu_Img, TRUE);
            /*DrawGraph(370, 50, Bakuhatsu_Img, TRUE);*/
        }
        
        BULLET->Draw();
        ENEMY->Draw();


        //リロード
        if (BulettCount_UI < 180) {

            DrawGraph(0, 0, BackGRImg, TRUE);

            DrawBox(200, 115, 1090, 500, 0x000000, TRUE);
            if (bullet::Bullet == 2)
            {
                DrawGraph(200, 115, BulletCount_Img, TRUE);

            }
            if (bullet::Bullet == 3)
            {
                DrawGraph(200, 115, BulletCount_Img2, TRUE);

            }
            if (bullet::Bullet == 4)
            {
                DrawGraph(200, 115, BulletCount_Img3, TRUE);

            }
        }
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
            if (A_UI[0] == TRUE&&AT<=121)
            {
                DrawString(450, 40, "PLAYER", 0xfa2000, TRUE);
                DrawString(560, 40, ": SHOT ENEMY!!", 0xffffff, TRUE);
            }

            if (A_UI[1] == TRUE && AT <= 121)
            {
                DrawString(460, 40, "PLAYER", 0xfa2000, TRUE);
                DrawString(570, 40, ": SHOT SELF!!", 0xffffff, TRUE);
            }

      

        //弾
        if (bh2_flg == TRUE)
        {
            DrawGraph(200, 110, bullet_holes3, TRUE);
            DrawCircle(640,370, 140, 0x000000);
            DrawGraph(-150, -650, bullet_holes2, TRUE);
           
        }


        if (PSP_miss_Flg == TRUE) {
            DrawGraph(200, 110, A_shotImg, FALSE);
        }
        if (missFlg == TRUE) {
            DrawGraph(200, 110, missImg, FALSE);
        }

       





        if (E_life <= 0) 
        {
            SetFontSize(72);
            DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
            DrawString(500, 300, "YOU WIN", 0xFFFF00, TRUE);
        }
        if (P_life <= 0)
        {
            SetFontSize(72);
            DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
            DrawString(490, 300, "YOU DEAD", 0xFF0000, TRUE);
        }

    }


    //リザルト画面
   
   
        if (ResultFlg == TRUE) {
            DrawGraph(0, 0, ResultBackImg[7], TRUE);
            SetFontSize(78);
         
           
            DrawFormatString(830, 280, 0xFF0000, "%d", Round);


            if (Item::itemtable[4] >= 1 && Item::Freez == TRUE && FreezDiray >= 27)
            {
                DrawGraph(0, 0, ResultBackImg[9], FALSE);
            }

        }


        SetFontSize(48);

        if (TotemTime != 0 && TotemTime < 180)
        {
            DrawGraph(0, 0, Totem2Img, FALSE);
        }

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
        if (PushFlg == TRUE && Item::itemtable[4] >= 1 &&
            PushFlgUI == 1 && Item::TotemRand == 1)
        {
            DrawGraph(0, 0, ResultBackImg[8], FALSE);
            if (Flash <= 40) {
                DrawBox(80, 80, 1200, 640, 0x645959, TRUE);
                SetFontSize(72);
                DrawString(520, 0, "PUSH!!", 0xFF0000);
                DrawString(500, 640, "START!!", 0xFF0000);
                DrawBox(150, 150, 1130, 570, 0x3a3232, TRUE);

                DrawTriangle(470, 160, 470, 560, 900, 370, 0xFFFFFF, FALSE);
            }
        }

    


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

    if (A_UI[0] == FALSE && A_UI[1] == FALSE)
    {
        AT = 0;
    }


    //プレイヤーから敵への射撃
    if (A_UI[0] == TRUE) {
        ChangeVolumeSoundMem(55, GMBgm);

        //処理の順番のための加算されるフレーム数
        AT++;
       

        //弾が発射 画像を表示 (AT == 121)
        if (bullet::Cylinder[bullet::FireC] == 1&&AT == 121)
        {
            PSE_hit_Flg = TRUE;
            PlaySoundMem(ShotSE, DX_PLAYTYPE_BACK);

            //爆弾がないなら
            if (Item::Bomb == FALSE)
            {
                bh_flg = TRUE;
              
            }
         

            //爆弾があるなら
            if (Item::Bomb == TRUE)
            {
                PlaySoundMem(Item::BombSE, DX_PLAYTYPE_BACK);
                BK_Flg = TRUE;
               
            }
           

            bullet::Last_Bullet -= 1;
        }


        //弾が入ってなかった時 MISS表示 (AT == 121)
        else if (bullet::Cylinder[bullet::FireC] == 0 && AT == 121)
        {
            PSE_miss_Flg = TRUE;
            missFlg = TRUE;
            ChangeVolumeSoundMem(255, NshotSE);
            PlaySoundMem(NshotSE, DX_PLAYTYPE_BACK);
           
        }
       

        //弾が発射された場合、銃痕の画像を消して敵のHPを減らしシリンダーを進める  (AT == 241)
        if (PSE_hit_Flg == TRUE && AT == 241)
        {

            //敵のHPを減らしシリンダーを進める
            E_life--;
            bullet::Cylinder[bullet::FireC] = 0;
            bullet::FireC++;


            //弾の画像を消す
            bh_flg = FALSE;

            //爆弾が発動中ならHPを1減らして画像を消す
            if (Item::Bomb == TRUE) {
                E_life--;
                Item::Bomb = FALSE;
            }


            AT = 301; 

        }


        //弾が入ってなかった時、シリンダーを進めて敵のターンへ  (AT == 241)
        if (PSE_miss_Flg == TRUE && AT == 241  )
        {
           
            bullet::Cylinder[bullet::FireC] = 0;
            bullet::FireC++;
            missFlg = FALSE;
            AT = 301;
          
        }


        //敵のターンに切り替える  (AT == 301)
        if (AT == 301) {
            isPlayerTurn = !isPlayerTurn;
            
        }


        //敵のターンになったら初期化する
        if (isPlayerTurn == FALSE)
        {
            PSE_hit_Flg = FALSE;
            PSE_miss_Flg = FALSE;
            TurnTime = 0;
            A_UI[0] = FALSE;
        }
    }
}


void GameMain::P_Choice()
{

    
    if (A_UI[0] == FALSE && A_UI[1] == FALSE)
    {
        AT = 0;
    }


        //プレイヤーからプレイヤーへの射撃
    if (A_UI[1] == TRUE) {

        ChangeVolumeSoundMem(55, GMBgm);
        //処理の順番のための加算されるフレーム数
        AT++;


        // 弾が発射 画像を表示　(AT == 121)
        if (bullet::Cylinder[bullet::FireC] == 1 && AT == 121)
        {
            bullet::Last_Bullet -= 1;
            PSP_hit_Flg = TRUE;
            bh2_flg = TRUE;

            PlaySoundMem(ShotSE, DX_PLAYTYPE_BACK);

           
          
        }


        //弾が入ってなかった時 1MORE表示(AT == 121)
        else if (bullet::Cylinder[bullet::FireC] == 0 && AT == 121)
        {
            PSP_miss_Flg = TRUE;
            ChangeVolumeSoundMem(255, NshotSE);
            PlaySoundMem(NshotSE, DX_PLAYTYPE_BACK);
           
          

        }


        //弾が発射された時、銃痕の画像を消してプレイヤーのHPを減らしシリンダーを進める  (AT == 241)
        if (AT == 241 && PSP_hit_Flg == TRUE)
        {

            P_life--;
            bullet::Cylinder[bullet::FireC] = 0;
            bullet::FireC++;
            bh2_flg = FALSE;
            AT = 301;
        }


        //弾が入ってなかった時、シリンダーを進めて処理を中断する  (AT == 241)
        if (AT == 241 && PSP_miss_Flg == TRUE)
        {
           
           
            bullet::Cylinder[bullet::FireC] = 0;
            bullet::FireC++;
            PSP_hit_Flg = FALSE;
            PSP_miss_Flg = FALSE;
            P_UI_INIT();
            A_UI[1] = FALSE;
        }


        //敵のターンに切り替える、変数を初期化する  (AT == 301)
        if (AT == 301 && PSP_hit_Flg == TRUE) {
          
            isPlayerTurn = !isPlayerTurn;
         
        }


        //敵のターンになったら初期化する
        if (isPlayerTurn == FALSE)
        {
            PSP_hit_Flg = FALSE;
            PSP_miss_Flg = FALSE;
            TurnTime = 0;
            P_UI_INIT();
            A_UI[1] = FALSE;
        }


      
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
            PlaySoundMem(P_UI_SE[2], DX_PLAYTYPE_BACK);
            P_UI_INIT();
        }

        if (P_Ui[0] == TRUE)
        {
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) && CurX == 180 && CurY == 576)
            {
                PlaySoundMem(GM_SelectSE, DX_PLAYTYPE_BACK);
                CurX = 180;
                CurY = 645;
            }
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) && CurX == 180 && CurY == 645)
            {
                PlaySoundMem(GM_SelectSE, DX_PLAYTYPE_BACK);
                CurX = 180;
                CurY = 576;
            }
            if (CurX == 180 && CurY == 576 && WaitFlg2 == TRUE
                && PAD_INPUT::OnRelease(XINPUT_BUTTON_A))
            {
                PlaySoundMem(P_UI_SE[0], DX_PLAYTYPE_BACK);
                P_Ui[1] = TRUE;
                P_Ui[0] = FALSE;
              
            }

            if (CurX == 180 && CurY == 645 && WaitFlg2 == TRUE
                && PAD_INPUT::OnRelease(XINPUT_BUTTON_A))
            {
                PlaySoundMem(P_UI_SE[0], DX_PLAYTYPE_BACK);
                P_Ui[2] = TRUE;
                P_Ui[0] = FALSE;
                
            }
        }


        if (P_Ui[1] == TRUE&& P_Ui[0] == FALSE)
    {
        if (AT == 0) {

            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) && CurX2 == 555 && CurY2 == 575)
            {
                PlaySoundMem(GM_SelectSE, DX_PLAYTYPE_BACK);
                CurX2 = 555;
                CurY2 = 650;
            }

            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) && CurX2 == 555 && CurY2 == 650)
            {
                PlaySoundMem(GM_SelectSE, DX_PLAYTYPE_BACK);
                CurX2 = 555;
                CurY2 = 575;
            }

            if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
                if (CurX2 == 555 && CurY2 == 575)
                {
                    PlaySoundMem(P_UI_SE[1], DX_PLAYTYPE_BACK);

                    if (A_UI[0] == FALSE) {
                        A_UI[0] = TRUE;
                    }
                   
                }
                if (CurX2 == 555 && CurY2 == 650)
                {
                    PlaySoundMem(P_UI_SE[1], DX_PLAYTYPE_BACK);

                    if (A_UI[1] == FALSE) {
                        A_UI[1] = TRUE;
                    }
                }
               
            }
        }
    }


        if (P_Ui[2] == TRUE && P_Ui[0] == FALSE)
        {
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) && CurY3 == 590)
            {
                PlaySoundMem(GM_SelectSE, DX_PLAYTYPE_BACK);
                CurY3 = 640;
            }
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) && CurY3 == 640)
            {
                PlaySoundMem(GM_SelectSE, DX_PLAYTYPE_BACK);
                CurY3 = 590;
            }

            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT) && CurX3 != 1100)
            {
                PlaySoundMem(GM_SelectSE, DX_PLAYTYPE_BACK);
                CurX3 += 135;
            }
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT) && CurX3 != 830)
            {
                PlaySoundMem(GM_SelectSE, DX_PLAYTYPE_BACK);
                CurX3 -= 135;
            }



            if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
                PlaySoundMem(P_UI_SE[0], DX_PLAYTYPE_BACK);
                if (CurX3 == 830 && CurY3 == 590)
                {
                    ITEM->DRAG();
                }

                if (CurX3 == 965 && CurY3 == 590) 
                {
                    ITEM->LOUPE();
                }

                if (CurX3 == 1100 && CurY3 == 590)
                {
                    ITEM->JUDGE();
                }

                if (CurX3 == 830 && CurY3 == 640)
                {
                    ITEM->BOMB();
                }

                if (CurX3 == 1100 && CurY3 == 640)
                {
                    ITEM->C_BULLET();
                }
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
  
    if (E_life <= 0 && A_UI[0] == FALSE && A_UI[1] == FALSE)
    {
        ET++;
    }
        if (ET == 180)
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
       /* do
        {
            ShuffleEnemyNum = GetRand(IMAGE_CNT - 1);
        } while (ShuffleEnemyNum == LastEnemyNum);

        LastEnemyNum = ShuffleEnemyNum;*/
        
       


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
      
        isPlayerTurn = TRUE;
   
}


void GameMain::BulettUI()
{
    if (RoundUiflg == FALSE&& BulettCount_UI != 181) {
        BulettCount_UI++;
        if (BulettCount_UI == 180) {
           
            BulettCount_UI = 181;
        }
    }
}

