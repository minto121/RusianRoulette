#include "DxLib.h"
#include "ResultScene.h"
#include "GameMain.h"
#include "Padinput.h"

ResultScene::ResultScene()
{
	Select = 0;
	Once = TRUE;
}

ResultScene::~ResultScene()
{

}

AbstractScene* ResultScene::Update()
{
	//十字キー↑入力
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		//PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 3;
	}
	//十字キー↓入力
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		//PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 3)Select = 0;
	}

	//Lスティック上入力
	if (PAD_INPUT::GetLStick().ThumbY > 10000 && Once == TRUE)
	{
		//PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 3;
		Once = FALSE;
	}

	//Lスティック下入力
	if (PAD_INPUT::GetLStick().ThumbY < -10000 && Once == TRUE)
	{
		//PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 3)Select = 0;
		Once = FALSE;
	}

	//Lスティックが元に戻されたらOnceをリセット
	if (Once == FALSE && PAD_INPUT::GetLStick().ThumbY < 10000 && PAD_INPUT::GetLStick().ThumbY > -10000)
	{
		Once = TRUE;
	}

	return this;
}

void ResultScene::Draw()const
{
	//タイトルの描画
	//DrawGraph(0, 0, TitleImg, FALSE);
	//DrawStringToHandle(150, 100, "りんごおとし", 0xffffff, MenuFont);

	//メニューの描画
	//DrawStringToHandle(730, 240, "すたーと", 0xffffff, MenuFont);
	//DrawStringToHandle(730, 320, "らんきんぐ", 0xffffff, MenuFont);
	//DrawStringToHandle(730, 400, "へるぷ", 0xffffff, MenuFont);
	//DrawStringToHandle(730, 480, "えんど", 0xffffff, MenuFont);

	//カーソルの描画
	int select_y = 230 + Select * 80;
	DrawGraph(650, select_y, CursorImg, TRUE);
}