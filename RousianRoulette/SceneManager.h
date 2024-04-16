#pragma once
#include"AbstractScene.h"

class SceneManager :
    public AbstractScene
{
private:
    AbstractScene* mScene;
public:

    //�R���X�g���N�^
    SceneManager(AbstractScene* scene) :mScene(scene) {};

    //�f�X�g���N�^
    ~SceneManager()
    {
        delete mScene;
    }

    //�`��ȊO�̍X�V����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ����
    void Draw() const override;
};



