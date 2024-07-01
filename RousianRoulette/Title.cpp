#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "PadInput.h"
#include "DrawRanking.h"
#include "ResultScene.h"
#include "EndScene.h"
#include "InputRanking.h"
#include "HelpScene.h"
#include "HelpScene0.h"

int Title::MenuSE;

enum class TITLE_MENU
{
	GAME_START = 0,
	GAME_RANKING,
	GAME_HELP,
	GAME_END
};

Title::Title()
{

	Select = 0;
	Once = TRUE;
	TitleBgm = LoadSoundMem("Resources/sounds/I like.wav");
	MenuSE = LoadSoundMem("Resources/sounds/cursorsound.mp3");
	ASE = LoadSoundMem("Resources/sounds/kettei.mp3");

	TitleImg = LoadGraph("resouce/image/title.png");
	CursorImg = LoadGraph("resouce/image/BulletCur.png");
}

Title::~Title()
{

	//StopSoundMem(TitleBgm);
	DeleteSoundMem(TitleBgm);
	//DeleteSoundMem(MenuSE);
}

AbstractScene* Title::Update()
{
	ChangeVolumeSoundMem(100, TitleBgm);
	PlaySoundMem(TitleBgm, DX_PLAYTYPE_LOOP, FALSE);

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 3;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 3)Select = 0;
	}

	if (PAD_INPUT::GetLStick().ThumbY > 10000 && Once == TRUE)
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 3;
		Once = FALSE;
	}

	if (PAD_INPUT::GetLStick().ThumbY < -10000 && Once == TRUE)
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 3)Select = 0;
		Once = FALSE;
	}

	if (Once == FALSE && PAD_INPUT::GetLStick().ThumbY < 10000 && PAD_INPUT::GetLStick().ThumbY > -10000)
	{
		Once = TRUE;
	}

	if (PAD_INPUT::OnRelease(XINPUT_BUTTON_A))
	{
		PlaySoundMem(ASE, DX_PLAYTYPE_BACK);

		switch (static_cast<TITLE_MENU>(Select))
		{
		case TITLE_MENU::GAME_START:
			return new GameMain();
			StopSoundMem(TitleBgm);
			break;
		case TITLE_MENU::GAME_RANKING:
			return new  DrawRankingScene(0);
			StopSoundMem(TitleBgm);
			break;
		case TITLE_MENU::GAME_HELP:
			return new HelpScene0();
			StopSoundMem(TitleBgm);
			break;
		case TITLE_MENU::GAME_END:
			return new EndScene;
			StopSoundMem(TitleBgm);
			break;
		default:
			break;
		}
	}
	return this;
}

void Title::Draw()const
{
	SetFontSize(64);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "select:%d", Select);


	DrawGraph(0, 0, TitleImg, FALSE);

	SetFontSize(48);

	int select_y = 360 + Select * 80;

	DrawGraph(550, select_y,CursorImg,TRUE);
	
	DrawGraph(1280, 720, TitleImg, TRUE);
}