#pragma once
class Enemy
{
private:

	int E_Choice;

public:
	Enemy();

	~Enemy();

	void Update();

	void Draw() const;

	void E_Turn();

	void E_AI();


};

