#pragma once
class Item
{
private:
	int L_Check;
	int UItime;
	

public:
	Item();

	~Item();

	void Update();

	void Draw() const;

	void DRAG();

	void BOMB();

	void LOUPE();

	void ITEM_UI_TIME();
};

