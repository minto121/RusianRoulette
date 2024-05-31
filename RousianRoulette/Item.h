#pragma once
#include "AbstractScene.h"

	
class Item:public AbstractScene
{
private:
	int L_Check;
	int UItime;
	int JudgeCount[2];
	

public:
	Item();

	~Item();

	AbstractScene* Update() override;

	void Draw() const;

	void DRAG();

	void BOMB();

	void LOUPE();

	void JUDGE();

	void TOTEM();

	void C_BULLET();

	void ITEM_UI_TIME();

	static int Bomb;
};

