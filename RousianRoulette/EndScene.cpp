#include "DxLib.h"
#include "Padinput.h"
#include "Title.h"
#include "EndScene.h"

EndScene::EndScene()
{
	Endimage = LoadGraph("Resources/images/EndScene.png");
}

EndScene::~EndScene()
{
	DeleteGraph(Endimage);
}

AbstractScene* EndScene::Update()
{
	static int time = 300;
	if (time-- <= 0) {
		return nullptr;
	}
	return this;
}

void EndScene::Draw() const
{
	DrawGraph(0, 0, Endimage, FALSE);
}