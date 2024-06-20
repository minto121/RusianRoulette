#pragma once
#include "AbstractScene.h"
class HelpScene2 : public AbstractScene
{
private:
	int image;
	int Bgm;

	int ASE;
	int BSE;

public:
	HelpScene2();
	~HelpScene2();

public:
	AbstractScene* Update() override;
	void Draw()const override;

};