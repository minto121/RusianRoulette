#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "PadInput.h"


//タイトルメニュー
enum class TITLE_MENU
{
	GAME_START = 0,
	GAME_RANKING,
	GAME_HELP,
	GAME_END
};

Title::Title()
{
	//初期化
	Select = 0;
	Once = TRUE;

	//フォントの追加
	MenuFont = CreateFontToHandle("HG創英角ﾎﾟｯﾌﾟ体", 64, 8, DX_FONTTYPE_ANTIALIASING);

	////タイトル画像の読み込み
	//if ((TitleImg = LoadGraph("Resource/Images/mori.png")) == -1)
	//{
	//	throw "Resource/Images/mori.png";
	//}
	//// カーソル画像の読み込み
	//if ((CursorImg = LoadGraph("Resource/Images/Apple_Red.png")) == -1)
	//{
	//	throw "Resource/Images/apple.png";
	//}
	////BGMの読み込み
	//if ((TitleBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	//{
	//	throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	//}
	////BGMの音量変更
	//ChangeVolumeSoundMem(140, TitleBGM);

	////SEの読み込み
	//if ((MenuSE = LoadSoundMem("Resource/sounds/SE/select01.wav")) == -1) //選択SE
	//{
	//	throw "Resource/sounds/SE/select01.wav";
	//}
	////SEの音量変更
	//ChangeVolumeSoundMem(110, MenuSE);

	////BGMの再生
	//if (CheckSoundMem(TitleBGM) == 0)
	//{
	//	PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP);
	//}

}

Title::~Title()
{
	//フォントの削除
	DeleteFontToHandle(MenuFont);

	StopSoundMem(TitleBGM);
	//サウンドの削除
	DeleteSoundMem(TitleBGM);
	DeleteSoundMem(MenuSE);
}

AbstractScene* Title::Update()
{
	//十字キー↑入力
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 3;
	}
	//十字キー↓入力
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 3)Select = 0;
	}

	//Lスティック上入力
	if (PAD_INPUT::GetLStick().ThumbY > 10000 && Once == TRUE)
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 3;
		Once = FALSE;
	}

	//Lスティック下入力
	if (PAD_INPUT::GetLStick().ThumbY < -10000 && Once == TRUE)
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 3)Select = 0;
		Once = FALSE;
	}

	//Lスティックが元に戻されたらOnceをリセット
	if (Once == FALSE && PAD_INPUT::GetLStick().ThumbY < 10000 && PAD_INPUT::GetLStick().ThumbY > -10000)
	{
		Once = TRUE;
	}

	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	//{
	//	switch (static_cast<TITLE_MENU>(Select))
	//	{
	//		//ゲーム画面へ
	//	case TITLE_MENU::GAME_START:

	//		return new GameMain();
	//		break;
	//		//ランキング画面へ
	//	case TITLE_MENU::GAME_RANKING:
	//		return new DrawRanking();
	//		//StopSoundMem(TitleBGM);
	//		break;
	//		//ヘルプ画面
	//	case TITLE_MENU::GAME_HELP:
	//		return new Help();
	//		//StopSoundMem(TitleBGM);
	//		break;
	//		//エンド画面へ
	//	case TITLE_MENU::GAME_END:
	//		return new End();
	//		//StopSoundMem(TitleBGM);
	//		break;
	//	default:
	//		break;
	//	}
	//}
	return this;
}

void Title::Draw()const
{
	//タイトルの描画
	DrawGraph(0, 0, TitleImg, FALSE);
	DrawStringToHandle(150, 100, "りんごおとし", 0xffffff, MenuFont);

	//メニューの描画
	DrawStringToHandle(730, 240, "すたーと", 0xffffff, MenuFont);
	DrawStringToHandle(730, 320, "らんきんぐ", 0xffffff, MenuFont);
	DrawStringToHandle(730, 400, "へるぷ", 0xffffff, MenuFont);
	DrawStringToHandle(730, 480, "えんど", 0xffffff, MenuFont);

	//カーソルの描画
	int select_y = 230 + Select * 80;
	DrawGraph(650, select_y, CursorImg, TRUE);
}