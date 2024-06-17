#include "Item.h"
#include "DxLib.h"
#include <math.h>
#include "GameMain.h"
#include "PadInput.h"
#include "Timer.h"
#include "Title.h"


int Item::Bomb;
int Item::TotemFlg;
int Item::itemtable[6];
int Item::TotemRand;
int Item::WaitTime;
int Item::WaitTime2;
int Item::Freez;
int Item::R3;
int Item::R4;
int Item::ReRound[2];

Item::Item()
{
   
    for (int a = 0; a <= 5; a++)
    {
        itemtable[a] = 0;
    }
    itemtable[4] = 1;
    ReRound[0] = FALSE;
    ReRound[1] = FALSE;
    INIT();

   
}


void Item::INIT()
{
    T_Bullet[0] = LoadGraph("Resources/images/White.png");
    T_Bullet[1] = LoadGraph("Resources/images/Item/Red.png");
    T_Bullet[2] = LoadGraph("Resources/images/Item/Yerrow.png");
    T_Bullet[3] = LoadGraph("Resources/images/Item/Blue.png");
    T_Bullet[4] = LoadGraph("Resources/images/Item/Green.png");
    T_Bullet[5] = LoadGraph("Resources/images/Item/Pupple.png");
    T_Bullet[6] = LoadGraph("Resources/images/Item/Pink.png");
    T_Bullet[7] = LoadGraph("Resources/images/Item/Mizuiro.png");
    T_Bullet[8] = LoadGraph("Resources/images/Item/Orange.png");
    T_Bullet[9] = LoadGraph("Resources/images/Item/Gray.png");
    T_Last = LoadGraph("Resources/images/Item/T_Last.png");
    T_Last2 = LoadGraph("Resources/images/Item/T_Last2.png");
    T_Last3 = LoadGraph("Resources/images/Item/T_Last3.png");
    F_Flash = LoadGraph("Resources/images/Item/ F_Flash.png");

    FreezSE = LoadSoundMem("Resources/SE/Totem/Freez.mp3");
    RedBulletSE = LoadSoundMem("Resources/SE/Totem/RedBullet.mp3");
    WhiteBulletSE = LoadSoundMem("Resources/SE/Totem/WhiteBullet.mp3");
    HukkatuSE = LoadSoundMem("Resources/SE/Totem/Hukkatu.mp3");
    HukkatuSE2 = LoadSoundMem("Resources/SE/Totem/Hukkatu1.mp3");
    HukkatuSE3 = LoadSoundMem("Resources/SE/Totem/Hukkatu3.mp3");
    HukkatuSE4 = LoadSoundMem("Resources/SE/Totem/Hukkatu4.mp3");
    HukkatuSE5 = LoadSoundMem("Resources/SE/Totem/Hukkatu5.mp3");
    HukkatuSE6 = LoadSoundMem("Resources/SE/UraBotann.mp3");
    HukkatuSE7 = LoadSoundMem("Resources/SE/Totem/Hukkatu2.mp3");
    HukkatuSE8 = LoadSoundMem("Resources/SE/Totem/Hukkatu6.mp3");


    FreezSE2 = LoadSoundMem("Resources/SE/Totem/Freez2.mp3");
    FreezSE3 = LoadSoundMem("Resources/SE/Totem/Freez3.mp3");
    FreezSE4 = LoadSoundMem("Resources/SE/Totem/Freez4.mp3");
    HukkatuSippaiSE = LoadSoundMem("Resources/SE/Totem/TotemShippai.mp3");

        /*TotemShippai.mp3"*/

    R = 1000;
    R2 = 70;

    R3 = 0;
    R4 = 0;

    R5 = -100;
    R6 = 1380;

    R7 = 720;
    R8 = 0;

    L_Check = 0;
    UItime = 0;
    Bomb = FALSE;
    TotemRand = 0;
  /*  itemtable[4] = 1;*/
    itemtable[2] = 1;
    T_UI = 0;
    T_UIRand = 0;
    T_RevivalAnim = FALSE;
    WaitTime = FALSE;
    WaitTime2 = FALSE;
    Freez = FALSE;
    TotemFlg = FALSE;


  

    BombSE = LoadSoundMem("Resources/sounds/Explosion.mp3");
    DragSE = LoadSoundMem("Resources/sounds/Drag.mp3");
    LoupeSE = LoadSoundMem("Resources/sounds/glass.mp3");
}

void Item::GETITEM()
{
    int table = GetRand(5);
    itemtable[table] += 1;
}

Item::~Item()
{
    DeleteSoundMem(BombSE);
    DeleteSoundMem(DragSE);
    DeleteSoundMem(LoupeSE);
}

void Item::DRAG()
{

    if (itemtable[0] >= 1 &&GameMain::P_life==1)
    {
        PlaySoundMem(DragSE, DX_PLAYTYPE_BACK);
        GameMain::P_life++;
        itemtable[0] -= 1;
    }
}

void Item::BOMB()
{
    if (itemtable[1] >= 1)
    {
        Bomb = TRUE;
        itemtable[1] -= 1;
        ChangeVolumeSoundMem(155, BombSE);
        PlaySoundMem(BombSE, DX_PLAYTYPE_BACK);
    }
    
} 

void Item::LOUPE()
{
    if (itemtable[2] >= 1)
    {
        PlaySoundMem(LoupeSE, DX_PLAYTYPE_BACK);

      
        Timer::FPS = 1;
        if (bullet::Cylinder[bullet::FireC] == 0)
        {
            L_Check = 1;

        }

        else if (bullet::Cylinder[bullet::FireC] == 1)
        {
            L_Check = 2;
 
        }
        itemtable[2] -= 1;
        
    
    }
}

void Item::JUDGE()
{
    int Judge = GetRand(1);
    if(itemtable[3] >= 1){
        if (Judge == 0) {
            GameMain::P_life--;
        }
        else {
            GameMain::E_life--;
        }
        
        if (GameMain::E_life < 1) {
            GameMain::P_life = 2;
        }
        itemtable[3] -= 1;
    }
}

void Item::TOTEM()
{
    if (itemtable[4] >= 1) {
        if (WaitTime2 == FALSE)
        {
            TotemRand = 1/*GetRand(1)*/;
            WaitTime2 = TRUE;
        }
        if (TotemFlg == TRUE)
        {

            if (WaitTime == FALSE) {


                if (TotemRand == 0)
                {
                    T_UIRand = GetRand(3);
                }

                if (TotemRand == 1) {
                    T_UIRand = GetRand(3);
                    /* GameMain::P_life = 2;*/
                }
                WaitTime = TRUE;
            }

            if (TotemRand == 0)
            {
                switch (T_UIRand)
                {
                case(0):
                    T_UI = 2;
                    break;
                case(1):
                    T_UI = 1;
                    break;
                case(2):
                    T_UI = 1;
                    break;
                case(3):
                    T_UI = 1;
                    break;
                }
            }

            if (TotemRand == 1)
            {
                if (GameMain::PushFlgUI != 5)
                {
                    switch (T_UIRand)
                    {
                    case(0):
                        T_UI = 1;
                        T_RevivalAnim = TRUE;
                        break;
                    case(1):
                        T_UI = 2;
                        T_RevivalAnim = TRUE;
                        break;
                    case(2):
                        T_UI = 2;
                        T_RevivalAnim = TRUE;
                        break;
                    case(3):
                        T_UI = 2;
                        T_RevivalAnim = TRUE;
                        break;
                    }
                }

                if (GameMain::PushFlgUI == 5)
                {
                    Freez = TRUE;
                    switch (T_UIRand)
                    {
                    case(0):
                        T_UI = 1;

                        break;
                    case(1):
                        T_UI = 1;

                        break;
                    case(2):
                        T_UI = 2;

                        break;
                    case(3):
                        T_UI = 2;

                        break;
                    }

                }

            }

            /* itemtable[4] = 0;*/
             /*TotemFlg = FALSE;*/
        }
    }
}

void Item::C_BULLET()
{
    if (itemtable[5] >= 1) {
       
        int i;
        for (i = 0; i < 6; i++) {
            if (bullet::Cylinder[i] == 0) {
                bullet::Cylinder[i] = 1;
            }
            else if (bullet::Cylinder[i] == 1) {
                bullet::Cylinder[i] = 0;
            }
        }
        itemtable[5] -= 1;


    }
}

void Item::TOTEM_UI_TIME()
{
    if (GameMain::PushFlgUI != 5 || GameMain::PushFlgUI == 5&&TotemRand ==0) {
        if (WaitTime == FALSE)
        {
            R4 = 0;
        }
        if (WaitTime == TRUE)
        {
            R4++;

            if (TotemRand == 0 && R4 == 120)
            {
                TotemFlg = FALSE;
                T_UI = 0;
                T_UIRand = 0;
                WaitTime = FALSE;
                WaitTime2 = FALSE;
            }



          

        }
    }
   
   
    if (Freez==TRUE)
    {
        if (WaitTime == FALSE)
        {
            R4 = 0;
        }
        if (WaitTime == TRUE)
        {
            R4++;

            if (TotemRand == 1 && R4 == 120)
            {
                TotemFlg = FALSE;
                T_UI = 0;
                T_UIRand = 0;
                WaitTime = FALSE;
                WaitTime2 = FALSE;
            }
        }
    }


    if (GameMain::FreezUI == TRUE)
    {
        //freez横線
        if (R5 != 640)
        {
            R5 += 70;
        }
      
        if (R6 != 640)
        {
            R6 -= 70;
        }
        if (R5 >= 640||R2<=0) {
            R5 = 640;
            R6 = 640;
        }

        //freez縦線
        if (R7 != 360)
        {
            R7 -= 85;
        }
        if (R7 <= 360)
        {
            R7 = 360;
        }
  
        if (R8 != 360)
        {
            R8 += 85;
        }
        if (R8 >= 360)
        {
            R8 = 360;
        }


        //freez円
        if (R != -1000) {
            R -= 400;

        }


        if (R == -1000) {
            R = -1000;

        }


        if (R2 != -650) {
            R2 -= 10;

        }


        if (R2 == -650) {
            R2 = -650;

        }
        if (R2 == -650 && R == -1000) {
        
            R3++;
            T_RevivalAnim = TRUE;
        }
       
       
       
      
    }


    
}

void Item::SOUND()
{
  
    //Totem↓
    if (T_UI == 1 && R3 == 1 || T_UI == 1 && R4 == 1)
    {
        
        PlaySoundMem(WhiteBulletSE, DX_PLAYTYPE_BACK);
    }
    if (T_UI == 2 && R3 == 1 || T_UI == 2 && R4 == 1)
    {
      
        PlaySoundMem(RedBulletSE, DX_PLAYTYPE_BACK);
    }


    if (TotemRand == 0 && R4 == 120 || TotemRand == 1 && R4 == 120 && Freez == TRUE)
    {
        PlaySoundMem(HukkatuSippaiSE, TRUE);
        PlaySoundMem(GameMain::ResultBgm2, DX_PLAYTYPE_LOOP, FALSE);
    }



    if (T_RevivalAnim == TRUE && R4 == 120
        || T_RevivalAnim == TRUE && R4 == 125
        || T_RevivalAnim == TRUE && R4 == 130
        || T_RevivalAnim == TRUE && R4 == 135
        || T_RevivalAnim == TRUE && R4 == 140
        || T_RevivalAnim == TRUE && R4 == 145
        || T_RevivalAnim == TRUE && R4 == 150
        || T_RevivalAnim == TRUE && R4 == 155
        || T_RevivalAnim == TRUE && R4 == 160
        || T_RevivalAnim == TRUE && R4 == 165
        || T_RevivalAnim == TRUE && R4 == 170
        || T_RevivalAnim == TRUE && R4 == 175)
    {
        PlaySoundMem(HukkatuSE, DX_PLAYTYPE_BACK);

    }



    if (T_RevivalAnim == TRUE && R3 == 180 || T_RevivalAnim == TRUE && R4 == 180)
    {
       
        PlaySoundMem(HukkatuSE4, DX_PLAYTYPE_BACK);
       
      
      
    }

  
  
    //freez
    if (GameMain::FreezUI == TRUE && T_RevivalAnim == TRUE && R3 == 120 ||
        GameMain::FreezUI == TRUE && T_RevivalAnim == TRUE && R4 == 120)
    {
        PlaySoundMem(FreezSE2, DX_PLAYTYPE_BACK);
    }

    if (   T_RevivalAnim == TRUE && R3 == 120
        || T_RevivalAnim == TRUE && R3 == 125
        || T_RevivalAnim == TRUE && R3 == 130
        || T_RevivalAnim == TRUE && R3 == 135
        || T_RevivalAnim == TRUE && R3 == 140
        || T_RevivalAnim == TRUE && R3 == 145
        || T_RevivalAnim == TRUE && R3 == 150
        || T_RevivalAnim == TRUE && R3 == 155
        || T_RevivalAnim == TRUE && R3 == 160
        || T_RevivalAnim == TRUE && R3 == 165
        || T_RevivalAnim == TRUE && R3 == 170
        || T_RevivalAnim == TRUE && R3 == 175)
    {
     
        PlaySoundMem(HukkatuSE3, DX_PLAYTYPE_BACK);
       /* PlaySoundMem(HukkatuSE4, DX_PLAYTYPE_BACK);*/

    }


    if (T_RevivalAnim == TRUE && R3 == 180)
    {
        PlaySoundMem(FreezSE3, DX_PLAYTYPE_BACK);
    }
    
    if (GameMain::FreezUI == TRUE&&R == 1000 && R2 == 70)
    {
        StopSoundMem(HukkatuSippaiSE);
        StopSoundMem(GameMain::ResultBgm2);
        PlaySoundMem(FreezSE, DX_PLAYTYPE_BACK);
       
    }
    if (GameMain::FreezUI == TRUE && R == 600)
    {
        PlaySoundMem(FreezSE4, DX_PLAYTYPE_BACK);
    }
   
    
    if (R4 >= 190&& R4 < 250 && R4 % 5 == 0 || R3 >= 190 && R3 < 250 && R3 % 5 == 0)
    {
        PlaySoundMem(FreezSE4, DX_PLAYTYPE_BACK);
      /*  PlaySoundMem(HukkatuSE2, DX_PLAYTYPE_BACK);*/
        PlaySoundMem(HukkatuSE7, DX_PLAYTYPE_BACK);
    }
    if (R4 == 280 || R3 == 280)
    {
        PlaySoundMem(FreezSE4, DX_PLAYTYPE_BACK);
        PlaySoundMem(HukkatuSE2, DX_PLAYTYPE_BACK);
        PlaySoundMem(HukkatuSE8, DX_PLAYTYPE_BACK);
    }
  
    if (R4 == 354 || R3 == 354)
    {
      
        PlaySoundMem(FreezSE4, DX_PLAYTYPE_BACK);
        PlaySoundMem(HukkatuSE2, DX_PLAYTYPE_BACK);
        PlaySoundMem(HukkatuSE6, DX_PLAYTYPE_BACK);
    }
    //Totem↑




}



AbstractScene*Item::Update()
{
   
    SOUND();
  /*  DRAG();*/
 /*   LOUPE();
    BOMB();
    JUDGE();*/
    TOTEM();
 /*   C_BULLET();*/
    TOTEM_UI_TIME();

    if (Timer::FPS == 200)
    {
        L_Check = 0;
    }
   
   /* if (TotemRand == 1&&Freez == FALSE)
    {
        ReRound[0] = TRUE;
    }
    if (TotemRand == 1 && Freez == TRUE)
    {
        ReRound[1] = TRUE;
    }*/

    return this;
}


void Item::Draw() const
{


        if (L_Check == 1)
        {
            DrawString(450, 40, "Blank Bullets", 0xffffff, TRUE);
        }
        if (L_Check == 2)
        {
            DrawString(450, 40, "Live Bullets", 0xffffff, TRUE);
        }

   

    //totem
    if (TotemFlg == TRUE) {
        if (T_UI == 1 && R4 < 120)
        {
            DrawCircle(625, 370, 150, 0x000000);
            DrawGraph(-150, -650, T_Bullet[0], TRUE);
        }
        if (T_UI == 2 && R4 < 120)
        {
            DrawCircle(625, 370, 150, 0x000000);
            DrawGraph(-150, -650, T_Bullet[1], TRUE);
        }

        if (GameMain::FreezUI == FALSE) {
            if (T_RevivalAnim == TRUE && R4 >= 120 && R4 < 125)
            {

                DrawBox(0, 0, 1280, 720, 0xFF0000, TRUE);
                DrawGraph(-150, -650, T_Bullet[0], TRUE);

            }
            if (T_RevivalAnim == TRUE && R4 >= 125 && R4 < 130)
            {
                DrawBox(0, 0, 1280, 720, 0x0beadb, TRUE);
                /*  DrawGraph(300, -380, T_Bullet[1], TRUE);*/
                DrawGraph(340, -400, T_Bullet[1], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 130 && R4 < 135)
            {
                DrawBox(0, 0, 1280, 720, 0xEE82EE, TRUE);
                /* DrawGraph(-400, -850, T_Bullet[2], TRUE);*/
                DrawGraph(-570, -850, T_Bullet[2], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 135 && R4 < 140)
            {
                DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);
                /* DrawGraph(190, -870, T_Bullet[3], TRUE);*/
                DrawGraph(300, -870, T_Bullet[3], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 140 && R4 < 145) {
                DrawBox(0, 0, 1280, 720, 0x0000FF, TRUE);
                /*  DrawGraph(-560, -400, T_Bullet[4], TRUE);*/
                DrawGraph(-590, -470, T_Bullet[4], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 145 && R4 < 150)
            {
                DrawBox(0, 0, 1280, 720, 0xFFA500, TRUE);
                /* DrawGraph(210, -900, T_Bullet[5], TRUE);*/
                DrawGraph(280, -850, T_Bullet[5], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 150 && R4 < 155) {
                /* DrawBox(0, 0, 1280, 720, 0x9370DB, TRUE);
                 DrawGraph(-650, -800, T_Bullet[6], TRUE);*/
                DrawBox(0, 0, 1280, 720, 0x008000, TRUE);
                DrawGraph(-660, -840, T_Bullet[6], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 155 && R4 < 160)
            {
                DrawBox(0, 0, 1280, 720, 0xf1888b, TRUE);
                /*  DrawGraph(220, -370, T_Bullet[7], TRUE);*/
                DrawGraph(300, -480, T_Bullet[7], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 160 && R4 < 165)
            {
                DrawBox(0, 0, 1280, 720, 0x0000FF, TRUE);
                DrawGraph(-580, -470, T_Bullet[8], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 165 && R4 < 170)
            {
                DrawBox(0, 0, 1280, 720, 0xFF0000, TRUE);
                DrawGraph(-150, -650, T_Bullet[0], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 170 && R4 < 175)
            {
                DrawBox(0, 0, 1280, 720, 0x0beadb, TRUE);
                DrawGraph(340, -400, T_Bullet[1], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 175 && R4 < 180)
            {
                DrawBox(0, 0, 1280, 720, 0xEE82EE, TRUE);
                DrawGraph(-570, -850, T_Bullet[2], TRUE);
            }


        }


    }


    if (GameMain::FreezUI == TRUE) {
        DrawGraph(0, 0, F_Flash, TRUE);
        DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
        /*0xEE82EE*/
        if (R != 0 && R2 != 0) {
            DrawBox(638, R8, 642, R7, 0xEE82EE, true);
            DrawBox(639, R8, 641, R7, 0xFFFFFF, true);
            DrawBox(R5, 358, R6, 362, 0xEE82EE, true);
            DrawBox(R5, 359, R6, 361, 0xffffff, true);
            DrawCircle(640, 360, R, 0xEE82EE, true);

            DrawCircle(640, 360, R2, 0xffffff, true);
        }

        if (T_RevivalAnim == TRUE && R3 >= 120 && R3 < 125)
        {

            DrawBox(0, 0, 1280, 720, 0xFF0000, TRUE);
            DrawGraph(-150, -650, T_Bullet[0], TRUE);

        }
        if (T_RevivalAnim == TRUE && R3 >= 125 && R3 < 130)
        {
            DrawBox(0, 0, 1280, 720, 0x0beadb, TRUE);
            /*  DrawGraph(300, -380, T_Bullet[1], TRUE);*/
            DrawGraph(340, -400, T_Bullet[1], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 130 && R3 < 135)
        {
            DrawBox(0, 0, 1280, 720, 0xEE82EE, TRUE);
            /* DrawGraph(-400, -850, T_Bullet[2], TRUE);*/
            DrawGraph(-570, -850, T_Bullet[2], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 135 && R3 < 140)
        {
            DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);
            /* DrawGraph(190, -870, T_Bullet[3], TRUE);*/
            DrawGraph(300, -870, T_Bullet[3], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 140 && R3 < 145) {
            DrawBox(0, 0, 1280, 720, 0x0000FF, TRUE);
            /*  DrawGraph(-560, -400, T_Bullet[4], TRUE);*/
            DrawGraph(-590, -470, T_Bullet[4], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 145 && R3 < 150)
        {
            DrawBox(0, 0, 1280, 720, 0xFFA500, TRUE);
            /* DrawGraph(210, -900, T_Bullet[5], TRUE);*/
            DrawGraph(280, -850, T_Bullet[5], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 150 && R3 < 155) {
            /* DrawBox(0, 0, 1280, 720, 0x9370DB, TRUE);
             DrawGraph(-650, -800, T_Bullet[6], TRUE);*/
            DrawBox(0, 0, 1280, 720, 0x008000, TRUE);
            DrawGraph(-660, -840, T_Bullet[6], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 155 && R3 < 160)
        {
            DrawBox(0, 0, 1280, 720, 0xf1888b, TRUE);
            /*  DrawGraph(220, -370, T_Bullet[7], TRUE);*/
            DrawGraph(300, -480, T_Bullet[7], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 160 && R3 < 165)
        {
            DrawBox(0, 0, 1280, 720, 0x0000FF, TRUE);
            DrawGraph(-580, -470, T_Bullet[8], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 165 && R3 < 170)
        {
            DrawBox(0, 0, 1280, 720, 0xFF0000, TRUE);
            DrawGraph(-150, -650, T_Bullet[0], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 170 && R3 < 175)
        {
            DrawBox(0, 0, 1280, 720, 0x0beadb, TRUE);
            DrawGraph(340, -400, T_Bullet[1], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 175 && R3 < 180)
        {
            DrawBox(0, 0, 1280, 720, 0xEE82EE, TRUE);
            DrawGraph(-570, -850, T_Bullet[2], TRUE);
        }





        /* if (T_RevivalAnim == TRUE && R3 >= 180)
         {
             DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
             DrawGraph(0, 0, T_Last, TRUE);

         }*/

    }



    if (T_RevivalAnim == TRUE && R4 >= 180 || T_RevivalAnim == TRUE && R3 >= 180)
    {
        DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
        if (R4 >= 190 && R4 < 220 || R4 >= 220 && R4 < 250 || R4 >= 250 && R4 < 280)
        {
            DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);
        }
        if (R4 >= 195 && R4 < 220 || R4 >= 225 && R4 < 250 || R4 >= 255 && R4 < 280)
        {
            DrawBox(0, 0, 1280, 720, 0x0000FF, TRUE);
        }
        if (R4 >= 200 && R4 < 220 || R4 >= 230 && R4 < 250 || R4 >= 260 && R4 < 280)
        {
            DrawBox(0, 0, 1280, 720, 0xFFFF00, TRUE);
        }
        if (R4 >= 205 && R4 < 220 || R4 >= 235 && R4 < 250 || R4 >= 265 && R4 < 280)
        {
            DrawBox(0, 0, 1280, 720, 0xFF0000, TRUE);
        }
        if (R4 >= 210 && R4 < 220 || R4 >= 240 && R4 < 250 || R4 >= 270 && R4 < 280)
        {
            DrawBox(0, 0, 1280, 720, 0xFFFF00, TRUE);
        }
        if (R4 >= 215 && R4 < 220 || R4 >= 245 && R4 < 250 || R4 >= 275 && R4 < 280)
        {
            DrawBox(0, 0, 1280, 720, 0x0000FF, TRUE);
        }



        if (R3 >= 190 && R3 < 220 || R3 >= 220 && R3 < 250 || R3 >= 250 && R3 < 280)
        {
            DrawBox(0, 0, 1280, 720, 0xFF0000, TRUE);
        }
        if (R3 >= 195 && R3 < 220 || R3 >= 225 && R3 < 250 || R3 >= 255 && R3 < 280)
        {
            DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);
        }
        if (R3 >= 200 && R3 < 220 || R3 >= 230 && R3 < 250 || R3 >= 260 && R3 < 280)
        {
            DrawBox(0, 0, 1280, 720, 0xee7800, TRUE);
        }
        if (R3 >= 205 && R3 < 220 || R3 >= 235 && R3 < 250 || R3 >= 265 && R3 < 280)
        {
            DrawBox(0, 0, 1280, 720, 0xFFFF00, TRUE);
        }
        if (R3 >= 210 && R3 < 220 || R3 >= 240 && R3 < 250 || R3 >= 270 && R3 < 280)
        {
            DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);
        }
        if (R3 >= 215 && R3 < 220 || R3 >= 245 && R3 < 250 || R3 >= 275 && R3 < 280)
        {
            DrawBox(0, 0, 1280, 720, 0x0000FF, TRUE);
        }

        DrawGraph(0, 0, T_Last, TRUE);


        if (R3 >= 280 || R4 >= 280)
        {
            DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);

            if (R3 >= 285 || R4 >= 285) {
                DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
            }
            if (R3 >= 290 || R4 >= 290) {
                DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);
            }
            if (R3 >= 295 || R4 >= 295) {
                DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
            }
            if (R3 >= 300 || R4 >= 300) {
                DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);
            }
            if (R3 == 305 || R4 == 305) {
                DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
            }
            if (R3 >= 310 || R4 >= 310) {
                DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);
            }
            if (R3 >= 315 || R4 >= 315) {
                DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
            }
            if (R3 >= 320 || R4 >= 320) {
                DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);
            }
            if (R3 >= 325 || R4 >= 325) {
                DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
            }
            if (R3 >= 330 || R4 >= 330) {
                DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);
            }
            if (R3 >= 335 || R4 >= 335) {
                DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
            }
            if (R3 >= 340 || R4 >= 340) {
                DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
            }
            if (R3 >= 345 || R4 >= 345) {
                DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
            }
            if (R3 >= 350 || R4 >= 350) {
                DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);
            }


            DrawGraph(0, 0, T_Last2, TRUE);

            if (R3 >= 355 || R4 >= 355) {
                DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
                DrawGraph(0, 0, T_Last3, TRUE);
            }
        }
    }


}
  /*  DrawBox(638, R8, 642, R7, 0xEE82EE, true);
    DrawBox(R5, 359, R6, 361, 0xEE82EE, true);
   
    DrawCircle(640, 360, R2, 0xFFFFFF, true);*/


  

    

   
   


   /* SetFontSize(28);
    DrawString(860, 600, "DRAG:", 0xffff00, TRUE);
    DrawString(990, 600, "LOUPE:", 0x87CEFA, TRUE);
    DrawString(1130, 600, "JUDGE:", 0xFF0000, TRUE);
    DrawString(860, 650, "BOMB:", 0xFF0000, TRUE);
    DrawString(990, 650, "TOTEM:", 0xffff00, TRUE);
    DrawString(1130, 650, "BC:", 0x87CEFA, TRUE);*/

   
   
   
  /*  DrawFormatString(100, 340, 0x000ff, "T:%d", itemtable[4]);*/
    /* DrawFormatString(100, 20, 0xffffff, "TR:%d", TotemRand);
     DrawFormatString(100, 40, 0xffffff, "TCOLOR:%d", T_UIRand);*/
     /*DrawFormatString(100, 40, 0x000ff, "FREEZ:%d", Freez);
     DrawFormatString(100, 80, 0x0000ff, "FREEZUI:%d", GameMain::FreezUI);
     DrawFormatString(100, 160, 0x000ff, "PUSHUI:%d", GameMain::PushFlgUI);
     DrawFormatString(100, 120, 0x000ff, "R:%d", R);
     DrawFormatString(100, 280, 0x000ff, "R2:%d", R2);
     DrawFormatString(100, 200, 0x000ff, "T:%d", R4);
     DrawFormatString(100, 240, 0x000ff, "A:%d", T_RevivalAnim);
     DrawFormatString(100, 320, 0x000ff, "To:%d", TotemRand);
     DrawFormatString(100, 360, 0x000ff, "TUI:%d", T_UI);
     DrawFormatString(100, 400, 0x000ff, "TUIR:%d", T_UIRand);
     */
     /* DrawString(0, 50, "Loupe:", 0xffffff, TRUE);*/
    

   /* DrawFormatString(100, 20, 0xffffff, "Bomb:%d", Bomb);*/
   




