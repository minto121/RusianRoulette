#pragma once
class Enemy
{
private:

	int E_Choice;
	int E_Shot_P;
	int E_Shot_Self;

	int E_UI[2];

	int Damage_UI;

public:
	static int E_WaitFlg;

	Enemy();

	~Enemy();

	void Update();

	void Draw() const;

	void E_Turn();

	void E_AI();

	void E_UI_TIME();

	
};

