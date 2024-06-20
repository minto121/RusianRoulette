#pragma once
#include "AbstractScene.h"
class HelpScene0 : public AbstractScene
{
private:
	int image;
	int Bgm;

	int ASE;
	int BSE;

public:
	HelpScene0();
	~HelpScene0();

public:
	AbstractScene* Update() override;
	void Draw()const override;

};