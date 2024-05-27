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
private:
    
    int Round;
    int TurnCount;
    int CurX;
    int CurY;
    int GM_Select;

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

    bullet* BULLET;
    Item* ITEM;
    Timer* TIMER;
    Enemy* ENEMY;

    static int P_life;
    static int E_life;
    static bool isPlayerTurn;
    static int NowSelect;

};

