#include"DxLib.h"
#include "HelpScene.h"
#include "HelpScene2.h"
#include"PadInput.h"
#include"GameMain.h"
#include"Title.h"
#include "DrawRanking.h"

Title title;

HelpScene2::HelpScene2()
{
	image = LoadGraph("Resources/images/HelpScene2.png");
	Bgm = LoadSoundMem("Resources/sounds/I like.wav");
	//ASE = LoadSoundMem("Resources/sounds/kettei.mp3");
	//BSE = LoadSoundMem("Resources/sounds/cancel.mp3");
}

HelpScene2::~HelpScene2()
{
	DeleteGraph(image);
	DeleteSoundMem(Bgm);
	//DeleteSoundMem(ASE);
	//DeleteSoundMem(BSE);
}

AbstractScene* HelpScene2::Update()
{

	ChangeVolumeSoundMem(100, Bgm);
	PlaySoundMem(Bgm, DX_PLAYTYPE_LOOP, FALSE);

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == 1) {

		//PlaySoundMem(ASE, DX_PLAYTYPE_BACK, FALSE);
		return new GameMain();
		StopSoundMem(Bgm);
	}
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) == 1)
	{
		//PlaySoundMem(BSE, DX_PLAYTYPE_BACK, FALSE);
		return new HelpScene();
		StopSoundMem(Bgm);

	}

	return this;
}

void HelpScene2::Draw() const
{
	DrawGraph(0, 0, image, FALSE);
}