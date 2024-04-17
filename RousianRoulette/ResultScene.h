#pragma once

#include "AbstractScene.h"

class ResultScene :
    public AbstractScene

{
private:

    int Select;     //�I��
    int OldKey;		//�O�̓��̓L�[
    int NowKey;		//���̓��̓L�[
    int KeyFlg;		//���̓L�[���

    bool Once;      //L�X�e�B�b�N�ŃJ�[�\���𓮂����p

    int stage;      //�X�R�A
    int bgimg;      //�w�i�摜

    int CursorImg;

public:
    //�R���X�g���N�^
    ResultScene();

    //�f�X�g���N�^
    ~ResultScene();

    //�`��ȊO�̍X�V����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ����
    void Draw() const override;
};



