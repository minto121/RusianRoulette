#include"DxLib.h"
#include "HelpScene.h"
#include "HelpScene0.h"
#include"PadInput.h"
#include"GameMain.h"
#include"Title.h"
#include "DrawRanking.h"



HelpScene0::HelpScene0()
{
	image = LoadGraph("Resources/images/HelpScene0.png");
	Bgm = LoadSoundMem("Resources/sounds/I like.wav");
	//ASE = LoadSoundMem("Resources/sounds/kettei.mp3");
	//BSE = LoadSoundMem("Resources/sounds/cancel.mp3");
}

HelpScene0::~HelpScene0()
{
	DeleteGraph(image);
	DeleteSoundMem(Bgm);
	//DeleteSoundMem(ASE);
	//DeleteSoundMem(BSE);
}

AbstractScene* HelpScene0::Update()
{

	ChangeVolumeSoundMem(100, Bgm);
	PlaySoundMem(Bgm, DX_PLAYTYPE_LOOP, FALSE);

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == 1) {

		//PlaySoundMem(ASE, DX_PLAYTYPE_BACK, FALSE);
		return new HelpScene();
		StopSoundMem(Bgm);
	}
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) == 1)
	{
		//PlaySoundMem(BSE, DX_PLAYTYPE_BACK, FALSE);
		return new Title();
		StopSoundMem(Bgm);

	}

	return this;
}

void HelpScene0::Draw() const
{
	DrawGraph(0, 0, image, FALSE);
}