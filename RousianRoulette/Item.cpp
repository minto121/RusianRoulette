#include "Item.h"
#include "DxLib.h"
#include <math.h>
#include "GameMain.h"
#include "PadInput.h"
#include "Timer.h"
#include "Title.h"


int Item::Bomb;

Item::Item()
{
    L_Check = 0;
    UItime = 0;
    Bomb = FALSE;

    BombSE = LoadSoundMem("Resources/sounds/Explosion.mp3");
    DragSE = LoadSoundMem("Resources/sounds/Drag.mp3");
    LoupeSE = LoadSoundMem("Resources/sounds/glass.mp3");
}

Item::~Item()
{
    DeleteSoundMem(BombSE);
    DeleteSoundMem(DragSE);
    DeleteSoundMem(LoupeSE);
}

void Item::DRAG()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y)&& GameMain::P_life==1)
    {
        PlaySoundMem(DragSE, DX_PLAYTYPE_BACK);
        GameMain::P_life++;
    }
}

void Item::BOMB()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER))
    {
        Bomb = TRUE;
        ChangeVolumeSoundMem(155, BombSE);
        PlaySoundMem(BombSE, DX_PLAYTYPE_BACK);
    }
    
} 

void Item::LOUPE()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
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
        
    }
}

void Item::JUDGE()
{
    int Judge = GetRand(1);
    if(PAD_INPUT::OnButton(XINPUT_BUTTON_X)){
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

void Item::ITEM_UI_TIME()
{
    if (Timer::FPS == 0)
    {
        L_Check = 0;
    }

   
}



AbstractScene*Item::Update()
{
    DRAG();
    LOUPE();
    BOMB();
    JUDGE();
    ITEM_UI_TIME();
    BOMB();
    return this;
}


void Item::Draw() const
{
    DrawString(0, 50, "Loupe:", 0xffffff, TRUE);
    if (L_Check == 1)
    {
        DrawString(70, 50, "0", 0xffffff, TRUE);
    }

    if (L_Check == 2)
    {
        DrawString(70, 50, "1", 0xffffff, TRUE);
    }

    DrawFormatString(100, 20, 0xffffff, "Bomb:%d", Bomb);
   
}

