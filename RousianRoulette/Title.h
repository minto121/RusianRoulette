#pragma once
#include "AbstractScene.h"

class Title :
    public AbstractScene

{
private:
    int Select;     //選択数
    int OldKey;		//前の入力キー
    int NowKey;		//今の入力キー
    int KeyFlg;		//入力キー情報

    bool Once;      //Lスティックでカーソルを動かす用

    int MenuFont; //メニュー用のフォント

    int TitleBGM;     //BGM用
    int MenuSE;       //選択SE用
    int TitleImg;     //タイトル画像
    int CursorImg;    //カーソル画像


public:
    //コンストラクタ
    Title();

    //デストラクタ
    ~Title();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};


