#pragma once
class Enemy
{
private:

	int E_Choice;
	int E_Shot_P;
	int E_Shot_Self;

	int E_UI[2];

	int NohitImg;
	int Hitdamage;
	int E_Timer;

	int Nohit_UI;
	int Hit_UI;
	int NT;
	int YT;
	int ShotSE;
	int NshotSE;
	int ESP_hit_flg;
	int ESP_miss_flg;
	int ESE_hit_flg;
	int ESE_miss_flg;
	int OneMore;
	int OneMoreImg;
public:
	static int E_WaitFlg;

	Enemy();

	~Enemy();

	void Update();

	void Draw() const;

	void E_INIT();

	void E_Turn();

	void E_AI();

	void E_UI_TIME();

	void E_PChoice();

	void E_EChoice();
};

