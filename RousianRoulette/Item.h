#pragma once
#include "AbstractScene.h"

	
class Item:public AbstractScene
{
private:
	int L_Check;
	int UItime;
	int JudgeCount[2];
	
	int BombSE;
	int DragSE;
	int LoupeSE;

public:
	Item();

	~Item();

	AbstractScene* Update() override;

	void Draw() const;

	void DRAG();

	void BOMB();

	void LOUPE();

	void JUDGE();

	void ITEM_UI_TIME();

	static int Bomb;
};

