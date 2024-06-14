#pragma once
#include "AbstractScene.h"

	
class Item:public AbstractScene
{
private:
	
	int L_Check;
	int UItime;
	/*int JudgeCount[2];*/
	int T_Bullet[10];
	int T_UIRand;
	int T_UI;
	int T_RevivalAnim;
	int R;
	int R2;
	int R5;
	int R6;
	int FreezSE;
	int FreezSE2;
	int FreezSE3;
	int FreezSE4;
	int PushSE;
	int PushSE2;
	int RedBulletSE;
	int WhiteBulletSE;
	int HukkatuSE;
	int HukkatuSE2;
	int HukkatuSE3;
	int HukkatuSE4;
	int HukkatuSE5;
	int HukkatuSippaSE;
	
	
	
	int BombSE;
	int DragSE;
	int LoupeSE;

public:
	Item();

	~Item();

	AbstractScene* Update() override;

	void Draw() const;

	void INIT();

	void DRAG();

	void BOMB();

	void LOUPE();

	void JUDGE();

	void TOTEM();

	void C_BULLET();

	void ITEM_UI_TIME();

	void SOUND();

	static int Bomb;
	static int TotemFlg;
	static int TotemRand;
	static int itemtable[6];
	static int WaitTime;
	static int WaitTime2;
	static int Freez;
	static int R3;
	static int R4;
	static int ReRound[2];
};

