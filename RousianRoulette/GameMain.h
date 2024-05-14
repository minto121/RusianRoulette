#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "bullet.h"
#include "Item.h"
#include "Timer.h"

class GameMain :
    public AbstractScene
{
private:
    
    int Round;
    int TurnCount;

    bool isPlayerTurn; // プレイヤーターンのフラグ

    // プレイヤーとコンピュータの状態を表す列挙型
    enum class PlayerState {
        PLAYER,
        ENEMY
    };

    PlayerState currentPlayer = PlayerState::PLAYER; // 現在のプレイヤー
public:

    //�R���X�g���N�^
    GameMain();

    //�f�X�g���N�^
    ~GameMain();

    //�`��ȊO�̍X�V����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ����
    void Draw() const override;

    void life();
    void Turn();

    bullet* BULLET;
    Item* ITEM;
    Timer* TIMER;

    static int P_life;
    static int E_life;
};

