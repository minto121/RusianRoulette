#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Item.h"

class GameMain :
    public AbstractScene

{
private:

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
    void Choice();

    bullet* BULLET;
};

