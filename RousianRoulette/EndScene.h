#pragma once
#include "AbstractScene.h"
class EndScene : public AbstractScene
{
private:
	int Endimage;
	int EndFontHandle;

public:
	EndScene();
	~EndScene();

	AbstractScene* Update() override;
	void Draw() const override;
};