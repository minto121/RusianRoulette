#pragma once
#include "AbstractScene.h"
class HelpScene : public AbstractScene
{
private:

public:
	HelpScene();
	~HelpScene();

public:
	AbstractScene* Update() override;
	void Draw()const override;

};