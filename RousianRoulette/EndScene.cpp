#include "DxLib.h"
#include "Padinput.h"
#include "Title.h"
#include "EndScene.h"

EndScene::EndScene()
{

}

EndScene::~EndScene()
{

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
	SetFontSize(50);
	//DrawString(330, 50, "END", 0x000000);
	DrawString(100, 50, "Thank you ", 0xffffff);
	DrawString(260, 100, "for playing!!", 0xffffff);
	SetFontSize(48);
	DrawString(100, 420, "m's feelings", 0xffffff);
	SetFontSize(24);
	DrawString(100, 480, "matsuda tomohide", 0xffffff);
	DrawString(100, 510, "matsutake taketo", 0xffffff);
	DrawString(100, 540, "miyagumi rikuto", 0xffffff);
	DrawString(100, 570, "nagamine sho", 0xffffff);

}