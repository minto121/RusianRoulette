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
    
    int TurnCount;
   /* int CurX;
    int CurY;*/
    int GM_Select;
    int a;
    bool WaitFlg;
    int ResultFlg;

     // プレイヤーターンのフラグ

    // プレイヤーとコンピュータの状態を表す列挙型
    enum class PlayerState {
        PLAYER,
        ENEMY
    };

    PlayerState currentPlayer = PlayerState::PLAYER; // 現在のプレイヤー

    int Enemyimg[IMAGE_CNT];
    int ShuffleEnemyNum;
    int LastEnemyNum;
    int bullet_holes;
    int bullet_holes2;
    
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
};

