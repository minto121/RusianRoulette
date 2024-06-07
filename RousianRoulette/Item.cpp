#include "Item.h"
#include "DxLib.h"
#include <math.h>
#include "GameMain.h"
#include "PadInput.h"
#include "Timer.h"
#include "Title.h"


int Item::Bomb;
int Item::itemlist[6];

Item::Item()
{

    for (int x = 0; x <= 5; x++) {
        itemlist[x] = 0;
    }
    L_Check = 0;
    UItime = 0;
    Bomb = FALSE;
}

Item::~Item()
{

}

void Item::DRAG()
{

    if (itemlist[0] ==1&& PAD_INPUT::OnButton(XINPUT_BUTTON_Y)&& GameMain::P_life==1)
    {
        GameMain::P_life++;
    }
}

void Item::BOMB()
{
    if (itemlist[1] == 1 && PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER))
    {
        Bomb = TRUE;
    }
    
} 

void Item::LOUPE()
{
    if (itemlist[2] == 1 && PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
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
    
    if(itemlist[3] == 1 && PAD_INPUT::OnButton(XINPUT_BUTTON_X)){
        int Judge = GetRand(1);
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
    
    if (itemlist[4] == 1 && GameMain::P_life == 0) {
        int Totem = GetRand(1);
        if (Totem == 1) {
            GameMain::P_life = 2;
            itemlist[4] == 0;
        }
    }
}

void Item::C_BULLET()
{
    if (itemlist[5] == 1 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
       
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
    TOTEM();
    C_BULLET();
    ITEM_UI_TIME();
   
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

