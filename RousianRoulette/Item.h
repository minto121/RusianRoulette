#pragma once
#include "AbstractScene.h"

	
class Item :public AbstractScene
{
private:


	int UItime;
	/*int JudgeCount[2];*/
	int T_Bullet[10];
	int TotemBack;
	int T_UIRand;
	int T_UI;
	int T_RevivalAnim;
	int R;
	int R2;
	int R5;
	int R6;
	int R7;
	int R8;
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
	int HukkatuSE6;
	int HukkatuSE7;
	int HukkatuSE8;
	int HukkatuSippaiSE;
	int T_Last;
	int T_Last2;
	int T_Last3;
	int F_Flash;

	int Bomb_Img;
	int	Loope_Img;
	int Drag_img;
	int CB_Img;
	int Judge_Img;
	int Loupe_Img;
	int I_Bomb_SE;


	int DragSE;
	int LoupeSE;
	

public:
	Item();

	~Item();

	AbstractScene* Update() override;

	void Draw() const;

	void INIT();

	void GETITEM();

	void DRAG();

	void BOMB();

	void LOUPE();

	void JUDGE();

	void TOTEM();

	void C_BULLET();

	void TOTEM_UI_TIME();

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

	static int L_Check;
	static int J_Player_Flg;
	static int J_Enemy_Flg;
	static int DRAG_Flg;
	static int Bomb_Flg;
	static int C_BULLET_Flg;
	static int BombSE;

};

