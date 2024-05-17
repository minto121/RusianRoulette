#include "Item.h"
#include "DxLib.h"
#include <math.h>
#include "GameMain.h"
#include "PadInput.h"
#include "Timer.h"
Item::Item()
{
    L_Check = 0;
    UItime = 0;
}

Item::~Item()
{

}

void Item::DRAG()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y)&& GameMain::P_life==1)
    {
        GameMain::P_life++;
    }
}

void Item::BOMB()
{
    
}

void Item::LOUPE()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
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

void Item::ITEM_UI_TIME()
{
    if (Timer::FPS == 0)
    {
        L_Check = 0;
    }

   
}


void Item::Update()
{
    DRAG();
    LOUPE();
    ITEM_UI_TIME();
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

   
}

