#include"DxLib.h"
#include "HelpScene.h"
#include"PadInput.h"
#include"GameMain.h"
#include"Title.h"

HelpScene::HelpScene()
{
	//image = LoadGraph("Resources/images/HELP.png");
	//select = 0;
	//bgm = sound;
	//TitleSE2 = LoadSoundMem("Resources/sounds/decision.wav");
}

HelpScene::~HelpScene()
{

}

AbstractScene* HelpScene::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == 1) {

		return new GameMain();

	}
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) == 1)
	{
		return new Title();
	}

	return this;
}

void HelpScene::Draw() const
{

	// 文字コード設定をUTF-8に変更
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);

	SetFontSize(48);

	DrawFormatString(100, 100, 0xffffff, "十字キーでコマンド選択");
	DrawFormatString(100, 130, 0xffffff, "Aボタンで決定");
	DrawFormatString(100, 160, 0xffffff, "Bボタンで戻る");

	SetFontSize(36);
	DrawFormatString(350, 590, 0xffffff, "A button push to Game Start");
	DrawFormatString(350, 630, 0xffffff, "B button push to Title");
	//DrawGraph(0, 0, image, 80FALSE);
}