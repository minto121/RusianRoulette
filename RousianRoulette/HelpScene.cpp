#include"DxLib.h"
#include "HelpScene.h"
#include "HelpScene0.h"
#include "HelpScene2.h"
#include"PadInput.h"
#include"GameMain.h"
#include"Title.h"
#include "DrawRanking.h"


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
		StopSoundMem(Bgm);
		return new HelpScene2();
	}
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) == 1)
	{
		PlaySoundMem(BSE, DX_PLAYTYPE_BACK, FALSE);
		StopSoundMem(Bgm);
		return new HelpScene0();

	}

	return this;
}

void HelpScene::Draw() const
{
	DrawGraph(0, 0, image, FALSE);
}