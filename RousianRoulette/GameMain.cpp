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
#include "ResultScene.h"
//#include "FpsController.h"

int GameMain::E_life;
int GameMain::P_life;
int GameMain::bh_flg;
int GameMain::bh2_flg;

enum class CURSOL
{
    C_ENEMY = 0,
    C_PLAYER,
    DRAG,
    BOMB,
    LOUPE,
    JUDGE
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
    //CurX = 170;
    //CurY = 550;
    WaitFlg = FALSE;

    GM_Select = 0;
    I_Select = 0;
    A_Select = 0;
    a = 0;
    ResultFlg = FALSE;
    bh_flg = FALSE;
    bh2_flg = FALSE;
    ShotFlg = FALSE;
    ItemFlg = FALSE;
    ActionFlg = TRUE;
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
    Result();
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && ResultFlg == TRUE)
    {
        return new Title;
    }
    if (ResultFlg == FALSE&&P_life>0)
    {
        /*  life();*/
        BULLET->Update();
        ITEM->Update();
        ENEMY->Update();
        TIMER->Update();
        //Choice();
        ////I_Choice();
        //Turn();
        /*  Cursol();*/
        Action();

        if (Timer::FPS == 200|| Timer::FPS == 799)
        {
            bh_flg = FALSE;
            bh2_flg = FALSE;
        }

        if (Timer::FPS == 750)
        {
            ShotFlg = FALSE;
            ActionFlg = TRUE;
        }

    /*    if (ShotFlg == TRUE)
        {*/
            if (WaitFlg == FALSE && isPlayerTurn == TRUE&&ShotFlg == TRUE&&Timer::FPS>1)
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
                if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
                {
                    ShotFlg = FALSE;
                    ActionFlg = TRUE;
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
        //}


        ////プレイヤーが負けた時の処理
        //if (P_life <= 0) {
        //    return new Title;
        //}

    //敵のHPがなくなるとラウンドが進み弾がリロードされる
        if (E_life <= 0) {
            Round++;
            do
            {
                ShuffleEnemyNum = GetRand(IMAGE_CNT - 1);
            } while (ShuffleEnemyNum == LastEnemyNum);

            LastEnemyNum = ShuffleEnemyNum;

            /*P_life = 2;*/
            BULLET->B_INIT();
            WaitFlg = FALSE;
            isPlayerTurn = TRUE;
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
       
        SetFontSize(14);
        BULLET->Draw();
        ITEM->Draw();
        TIMER->Draw();
        ENEMY->Draw();
        //UI
        DrawBox(0, 500, 1280, 720, GetColor(255, 255, 255), TRUE);
        DrawBox(10, 510, 1270, 710, GetColor(0, 0, 0), TRUE);
        SetFontSize(24);
        DrawFormatString(0, 100, GetColor(255, 255, 255), "P_life:%d", P_life);
        DrawFormatString(0, 120, GetColor(255, 255, 255), "E_life:%d", E_life);
        DrawFormatString(0, 140, GetColor(255, 255, 255), "Round:%d", Round);
        DrawFormatString(0, 200, GetColor(255, 255, 255), "TurnCount:%d", TurnCount);
        DrawFormatString(0, 220, GetColor(255, 255, 255), "GM_select:%d", GM_Select);
        /* DrawFormatString(0, 160, GetColor(255, 255, 255), "Turn:%d",P_Turn);
         DrawFormatString(0, 180, GetColor(255, 255, 255), "Turn:%d",E_Turn);*/
         /*DrawFormatString(0, 130, GetColor(255, 255, 255), "Turn:%d",Trun);*/
        DrawFormatString(0, 0, GetColor(255, 255, 255), "a:%d", a);

        if (isPlayerTurn == TRUE)
        {
            DrawString(0, 160, "Pleyer", 0xffffff);
        }
        else
        {
            DrawString(0, 180, "Enemy", 0xffffff);
        }

        if (ActionFlg == TRUE)
        {
            SetFontSize(48);
            DrawString(200, 550, "SHOT", 0xffffff);
            DrawString(750, 550, "ITEM", 0xffffff);

            int select = 200 + A_Select * 500;
            DrawCircle(select, 570, 10, GetColor(255, 255, 255), TRUE);
        }

        //プレイヤーか敵を選ぶ
        if (ShotFlg == TRUE)
        {
            SetFontSize(48);
            DrawString(200, 550, "ENEMY", 0xffffff);
            DrawString(200, 600, "PLAYER", 0xffffff);

            int select_y = 570 + GM_Select * 50;
            DrawCircle(170, select_y, 10, GetColor(255, 255, 255), TRUE);
        }
       
        if (ItemFlg == TRUE)
        {
        //アイテム
        SetFontSize(48);
        DrawString(750, 550, "DRAG", 0xffffff);
        DrawString(750, 600, "BOMB", 0xffffff);

        DrawString(900, 550, "LOOPE", 0xffffff);
        DrawString(900, 600, "JUDGE", 0xffffff);
        }
        //DrawBox(CurX, CurY, CurX + 200, CurY + 50, 0xffffff, FALSE);
    }
    if (bh2_flg == TRUE&& ResultFlg == FALSE)
    {
        DrawGraph(-120, -140, bullet_holes2, TRUE);
    }
    if (ResultFlg == TRUE) {
        DrawFormatString(550, 350, GetColor(255, 255, 255), "Round:%d", Round);
        DrawString(480, 650, "Press_A_Button", 0xffffff);
        DrawString(550, 50, "Result", 0xffffff);
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

//void GameMain::Turn()
//{
//    TurnCount = bullet::FireC;
//
//
//    if (isPlayerTurn == FALSE)
//    {
//        //敵がプレイヤーを選択
//        if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && isPlayerTurn == FALSE)
//        {
//            if (bullet::Cylinder[bullet::FireC] == 1 && isPlayerTurn == FALSE)
//            {
//                P_life--;
//                isPlayerTurn = TRUE;
//            }
//            else
//            {
//                isPlayerTurn = TRUE;
//            }
//        }
//        WaitFlg = FALSE;
//    }
//}

void GameMain::Action()
{
    if (ActionFlg == TRUE) {
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
        {
            switch (static_cast<action>(A_Select))
            {
            case action::SHOT:
                ActionFlg = FALSE;
                ShotFlg = TRUE;

                break;
            case action::ITEM:
                ActionFlg = FALSE;
                ItemFlg = TRUE;
                break;
            default:
                break;
            }
        }
        //左方向
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
        {
            /*  CurY -= 50;*/
            A_Select--;
            if (A_Select < 0)A_Select = 1;
        }
        //右方向
        if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
        {
            /*CurY += 50;*/
            A_Select++;
            if (A_Select > 1)A_Select = 0;
        }
        Timer::FPS = 0;
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

void GameMain::ITEM_Choice()
{
    if (ItemFlg == TRUE) {
        if (WaitFlg == FALSE && isPlayerTurn == TRUE)
        {
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
            {
                switch (static_cast<CURSOL>(I_Select))
                {
                case CURSOL::DRAG:
                    ITEM->DRAG();
                    break;
                case CURSOL::BOMB:
                    ITEM->BOMB();
                    break;
                case CURSOL::LOUPE:
                    ITEM->LOUPE();
                    break;
                case CURSOL::JUDGE:
                    ITEM->JUDGE();
                    break;
                default:
                    break;
                }
            }
            //上方向
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
            {
                /*  CurY -= 50;*/
                I_Select--;
                if (I_Select < 0)I_Select = 1;
            }
            //下方向
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
            {
                /*CurY += 50;*/
                I_Select++;
                if (I_Select > 1)I_Select = 0;
            }
            //左方向
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
            {
                /*  CurY -= 50;*/
                //I_Select--;
                if (I_Select == 0)
                {
                    I_Select = 3;
                }
                /*  if (I_Select < 0)I_Select = 1;*/
            }
            //右方向
            if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
            {
                /*CurY += 50;*/
                I_Select++;
                /* if (I_Select > 1)I_Select = 0;*/
            }
          
        }
    }
}


void GameMain::Result()
{
    
    if (P_life <= 0&&a==0)
    {
        Timer::FPS = 0;
        a = 1;
    }
    if (a == 1)
    {
        Timer::FPS++;
    }
    if (P_life <= 0&&Timer::FPS ==200) 
    {
        ResultFlg = TRUE;
    }
    
}