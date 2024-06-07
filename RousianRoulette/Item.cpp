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

Item::Item()
{
   
    INIT();
    
}


void Item::INIT()
{
    T_Bullet[0] = LoadGraph("Resources/images/White.png");
    T_Bullet[1] = LoadGraph("Resources/images/Red.png");
    T_Bullet[2] = LoadGraph("Resources/images/Yerrow.png");
    T_Bullet[3] = LoadGraph("Resources/images/Blue.png");
    T_Bullet[4] = LoadGraph("Resources/images/Green.png");

    FreezSE = LoadSoundMem("Resources/SE/Freez.mp3");
    RedBulletSE = LoadSoundMem("Resources/SE/RedBullet.mp3");
    WhiteBulletSE = LoadSoundMem("Resources/SE/WhiteBullet.mp3");
    HukkatuSE = LoadSoundMem("Resources/SE/Hukkatu.mp3");
    HukkatuSE2 = LoadSoundMem("Resources/SE/Hukkatu1.mp3");
    ResultBgm = LoadSoundMem("Resources/SE/result.mp3");
    FreezSE2 = LoadSoundMem("Resources/SE/Freez2.mp3");

    R = 1000;
    R2 = 50;
    R3 = 0;
    R4 = 0;
    L_Check = 0;
    UItime = 0;
    Bomb = FALSE;
    TotemRand = 0;
    for (int a = 0; a <= 5; a++)
    {
        itemtable[a] = 0;
    }
    itemtable[4] = 1;
    T_UI = 0;
    T_UIRand = 0;
    T_RevivalAnim = FALSE;
    WaitTime = FALSE;
    WaitTime2 = FALSE;
    Freez = FALSE;
    TotemFlg = FALSE;
    BgmW = 0;
}



Item::~Item()
{

}

void Item::DRAG()
{

    if (itemtable[0] == 1 && PAD_INPUT::OnButton(XINPUT_BUTTON_Y)&& GameMain::P_life==1)
    {
        GameMain::P_life++;
    }
}

void Item::BOMB()
{
    if (itemtable[1] == 1 && PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER))
    {
        Bomb = TRUE;
    }
    
} 

void Item::LOUPE()
{
    if (itemtable[2] == 1 && PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
    {
       
        Timer::FPS = 1;

        if (bullet::Cylinder[bullet::FireC] == 0)
        {
            L_Check = 1;
        }

        else if (bullet::Cylinder[bullet::FireC] == 1)
        {
            L_Check = 2;
        }
        
    }
}

void Item::JUDGE()
{
    int Judge = GetRand(1);
    if(itemtable[3] == 1 && PAD_INPUT::OnButton(XINPUT_BUTTON_X)){
        if (Judge == 0) {
            GameMain::P_life--;
        }
        else {
            GameMain::E_life--;
        }
        
        if (GameMain::E_life < 1) {
            GameMain::P_life = 2;
        }
    }
}

void Item::TOTEM()
{
   
        if (WaitTime2 == FALSE)
        {
            TotemRand = GetRand(1);
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

void Item::C_BULLET()
{
    if (itemtable[5] == 1 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
       
        int i;
        for (i = 0; i < 6; i++) {
            if (bullet::Cylinder[i] == 0) {
                bullet::Cylinder[i] = 1;
            }
            else if (bullet::Cylinder[i] == 1) {
                bullet::Cylinder[i] = 0;
            }
        }
        


    }
}

void Item::ITEM_UI_TIME()
{
    if (GameMain::PushFlgUI != 5 || GameMain::PushFlgUI == 5&&TotemRand ==0) {
        if (WaitTime == FALSE)
        {
            R4 = 0;
        }
        if (WaitTime == TRUE)
        {
            R4++;

            if (TotemRand == 0 && R4 == 300)
            {
                TotemFlg = FALSE;
                itemtable[4] = 0;
                T_UI = 0;
                T_UIRand = 0;
                WaitTime = FALSE;
                WaitTime2 = FALSE;
            }



            if (TotemRand == 1 && R4 == 451)
            {

                INIT();


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

            if (TotemRand == 1 && R4 == 300)
            {
                TotemFlg = FALSE;
                itemtable[4] = 0;
                T_UI = 0;
                T_UIRand = 0;
                WaitTime = FALSE;
                WaitTime2 = FALSE;
            }
        }
    }
    if (GameMain::FreezUI == TRUE)
    {

        if (R != 0) {
            R -= 100;

        }


        if (R == 0) {
            R = 0;

        }


        if (R2 != 0) {
            R2 -= 2;

        }


        if (R2 == 0) {
            R2 = 0;

        }
        if (R2 == 0 && R == 0) {
            R3++;
            T_RevivalAnim = TRUE;
        }
        if (R3 == 451) {

           
            INIT();
           
           
        }
    }

}

void Item::SOUND()
{
   /* if (T_UI == 0)
    {
        PlaySoundMem(ResultBgm, DX_PLAYTYPE_BACK);
    }*/
    
    if (T_UI == 1 && R3 == 1 || T_UI == 1 && R4 == 1)
    {
        PlaySoundMem(WhiteBulletSE, DX_PLAYTYPE_BACK);
    }
    if (T_UI == 2 && R3 == 1 || T_UI == 2 && R4 == 1)
    {
        PlaySoundMem(RedBulletSE, DX_PLAYTYPE_BACK);
    }
    if (T_RevivalAnim == TRUE && R3 == 300 || T_RevivalAnim == TRUE && R4 == 300
        || T_RevivalAnim == TRUE && R3 == 330 || T_RevivalAnim == TRUE && R4 == 330
        || T_RevivalAnim == TRUE && R3 == 360 || T_RevivalAnim == TRUE && R4 == 360
        || T_RevivalAnim == TRUE && R3 == 390 || T_RevivalAnim == TRUE && R4 == 390
        || T_RevivalAnim == TRUE && R3 == 420 || T_RevivalAnim == TRUE && R4 == 420)
    {
        PlaySoundMem(HukkatuSE, DX_PLAYTYPE_BACK);

    }
    if (GameMain::FreezUI == FALSE&&T_RevivalAnim == TRUE && R3 == 420 || 
        GameMain::FreezUI == FALSE && T_RevivalAnim == TRUE && R4 == 420)
    {
        PlaySoundMem(HukkatuSE2, DX_PLAYTYPE_BACK);
    }

    if (GameMain::FreezUI == TRUE && T_RevivalAnim == TRUE && R3 == 300 ||
        GameMain::FreezUI == TRUE && T_RevivalAnim == TRUE && R4 == 300)
    {
        PlaySoundMem(FreezSE2, DX_PLAYTYPE_BACK);
    }
    if (T_RevivalAnim == TRUE && R3 == 450 || T_RevivalAnim == TRUE && R4 == 450)
    {
        StopSoundMem(HukkatuSE);
    }
    if (GameMain::FreezUI == TRUE&&R == 1000 && R2 == 50)
    {
        PlaySoundMem(FreezSE, DX_PLAYTYPE_BACK);
    }
    
    
   
}



AbstractScene*Item::Update()
{
   
  
    SOUND();
    DRAG();
    LOUPE();
    BOMB();
    JUDGE();
    TOTEM();
    C_BULLET();
    ITEM_UI_TIME();
   
    return this;
}


void Item::Draw() const
{
  
   

    if (TotemFlg == TRUE) {
        if (T_UI == 1 && R4 < 400)
        {
            DrawGraph(-150, -600, T_Bullet[0], TRUE);
        }
        if(T_UI == 2 && R4 < 400)
        {
            DrawGraph(-150, -600, T_Bullet[1], TRUE);
        }

        if (GameMain::FreezUI == FALSE) {
            if (T_RevivalAnim == TRUE && R4 >= 300 && R4 < 330)
            {
                DrawBox(0, 0, 1280, 720, 0xFF0000, TRUE);
                DrawGraph(-150, -600, T_Bullet[0], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 330 && R4 < 360)
            {
                DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);
                DrawGraph(60, -380, T_Bullet[1], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 360 && R4 < 390)
            {
                DrawBox(0, 0, 1280, 720, 0xEE82EE, TRUE);
                DrawGraph(-500, -850, T_Bullet[2], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 390 && R4 < 420)
            {
                DrawBox(0, 0, 1280, 720, 0xFFFF00, TRUE);
                DrawGraph(190, -870, T_Bullet[3], TRUE);
            }
            if (T_RevivalAnim == TRUE && R4 >= 420 && R4 < 450)
            {
                DrawBox(0, 0, 1280, 720, 0x0000FF, TRUE);
                DrawGraph(-560, -400, T_Bullet[4], TRUE);
            }
            
        }


    }


    if (GameMain::FreezUI == TRUE) {
        DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
        if (R != 0 && R2 != 0) {
            DrawCircle(620, 320, R, 0xEE82EE, true);
            DrawCircle(620, 320, R2, 0xffffff, true);
        }
        if (T_RevivalAnim == TRUE && R3 >= 300 && R3 < 330)
        {
            DrawBox(0, 0, 1280, 720, 0xFF0000, TRUE);
            DrawGraph(-150, -600, T_Bullet[0], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 330 && R3 < 360)
        {
            DrawBox(0, 0, 1280, 720, 0xFFFFFF, TRUE);
            DrawGraph(60, -380, T_Bullet[1], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 360 && R3 < 390)
        {
            DrawBox(0, 0, 1280, 720, 0xEE82EE, TRUE);
            DrawGraph(-500, -850, T_Bullet[2], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 390 && R3 < 420)
        {
            DrawBox(0, 0, 1280, 720, 0xFFFF00, TRUE);
            DrawGraph(190, -870, T_Bullet[3], TRUE);
        }
        if (T_RevivalAnim == TRUE && R3 >= 420 && R3 < 450)
        {
            DrawBox(0, 0, 1280, 720, 0x0000FF, TRUE);
            DrawGraph(-560, -400, T_Bullet[4], TRUE);
        }
    }


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
    /* DrawString(0, 50, "Loupe:", 0xffffff, TRUE);
   if (L_Check == 1)
   {
       DrawString(70, 50, "0", 0xffffff, TRUE);
   }

   if (L_Check == 2)
   {
       DrawString(70, 50, "1", 0xffffff, TRUE);
   }

   DrawFormatString(100, 20, 0xffffff, "Bomb:%d", Bomb);*/
}



