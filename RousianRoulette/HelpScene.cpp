#include"DxLib.h"
#include "HelpScene.h"
#include"PadInput.h"
#include"GameMain.h"
#include"Title.h"

Title title;

HelpScene::HelpScene()
{
	image = LoadGraph("Resources/images/HelpScene.png");
	Bgm = LoadSoundMem("Resources/sounds/I like.wav");
	ASE = LoadSoundMem("Resources/sounds/kettei.mp3");
	BSE = LoadSoundMem("Resources/sounds/cancel.mp3");
}

HelpScene::~HelpScene()
{
	DeleteGraph(image);
	DeleteSoundMem(Bgm);
	DeleteSoundMem(ASE);
	DeleteSoundMem(BSE);
}

AbstractScene* HelpScene::Update()
{

	ChangeVolumeSoundMem(100, Bgm);
	PlaySoundMem(Bgm, DX_PLAYTYPE_LOOP, FALSE);

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == 1) {

		PlaySoundMem(ASE, DX_PLAYTYPE_BACK, FALSE);
		return new GameMain();
		StopSoundMem(Bgm);
	}
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) == 1)
	{
		PlaySoundMem(BSE, DX_PLAYTYPE_BACK, FALSE);
		return new Title();
		StopSoundMem(Bgm);

	}

	return this;
}

void HelpScene::Draw() const
{
	DrawGraph(0, 0, image, FALSE);

	//SetFontSize(48);

	//DrawFormatString(100, 100, 0xffffff, "十字キーでコマンド選択");
	//DrawFormatString(100, 150, 0xffffff, "Aボタンで決定");
	//DrawFormatString(100, 200, 0xffffff, "Bボタンで戻る");

	//SetFontSize(36);
	//DrawFormatString(350, 590, 0xff0000, "A button push to Game Start");
	//DrawFormatString(350, 630, 0x0000ff, "B button push to Title");
	//DrawGraph(0, 0, image, 80FALSE);
}