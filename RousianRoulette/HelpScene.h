#pragma once
#include "AbstractScene.h"
class HelpScene : public AbstractScene
{
private:
	int image;
	int Bgm;

	int ASE;
	int BSE;

public:
	HelpScene();
	~HelpScene();

public:
	AbstractScene* Update() override;
	void Draw()const override;

};