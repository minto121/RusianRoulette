#pragma once
#include "AbstractScene.h"
#include "bullet.h"
#include "Item.h"
#include "Timer.h"
#include "Enemy.h"

#define IMAGE_CNT 5

class GameMain :
    public AbstractScene
{
public:
     int Round;
private:
   
    int PushFlg;
    /*int PushFlgUI;*/
    int Flash;

   
    int R;
    int TurnCount;
    int CurX;
    int CurY;
    int CurX2;
    int CurY2;
    int CurX3;
    int CurY3;
   
    int GM_Select;
    int I_Select;
    int A_Select;
    int a;
    bool WaitFlg;
    bool WaitFlg2;
    bool WaitFlg3;
    int ResultFlg;

     // プレイヤーターンのフラグ

    // プレイヤーとコンピュータの状態を表す列挙型
    enum class PlayerState {
        PLAYER,
        ENEMY
    };

    PlayerState currentPlayer = PlayerState::PLAYER; // 現在のプレイヤー

    int Enemyimg[IMAGE_CNT];
    int E_LifeImg;
    int P_LifeImg;
    int ShuffleEnemyNum;
    int LastEnemyNum;
    int bullet_holes;
    int bullet_holes2;
    int P_Ui_flg[5];
    int P_Ui[5];
    int BackGRImg;
    int CursolImg[3];
    int PushSE;
    int PushSE2;
    int PushSEflg;
public:

    //�R���X�g���N�^
    GameMain();

    //�f�X�g���N�^
    ~GameMain();

    //�`��ȊO�̍X�V����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ����
    void Draw() const override;

    void Turn();
   /* void Choice();*/
    void Cursol();
    void E_Choice();
    void P_Choice();
    void Result();
    void P_UI();
    void P_UI_INIT();
    bullet* BULLET;
    Item* ITEM;
    Timer* TIMER;
    Enemy* ENEMY;

    static int P_life;
    static int E_life;
    static bool isPlayerTurn;
    static int NowSelect;
    static int bh_flg;
    static int bh2_flg;
    static int PushFlgUI;
    static int FreezUI;
};

