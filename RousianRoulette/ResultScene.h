#pragma once

#include "AbstractScene.h"

class ResultScene :
    public AbstractScene

{
private:

    int Select;     //選択数
    int OldKey;		//前の入力キー
    int NowKey;		//今の入力キー
    int KeyFlg;		//入力キー情報

    bool Once;      //Lスティックでカーソルを動かす用

    int score;      //スコア
    int bgimg;      //背景画像

    int CursorImg;

public:
    //コンストラクタ
    ResultScene();

    //デストラクタ
    ~ResultScene();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};



