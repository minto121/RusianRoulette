#include"DxLib.h"
#include"SceneManager.h"
#include"FPS.h"
#include"Title.h"
#include"PadInput.h"
#include"GameMain.h"

#define FRAMERATE 60.0 //フレームレート

#define HEIGHT 720
#define WIDTH 1280 
#define REFRESHRATE 32

/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("Russian Rolette");

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	SetGraphMode(WIDTH, HEIGHT, REFRESHRATE);	//画面サイズの設定

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	SceneManager* sceneMng;

	try
	{
		sceneMng = new SceneManager((AbstractScene*)new Title());

	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);
		//ファイルオープン
		fopen_s(&fp, "ErrLog.txt", "a");
		//エラーデータの書き込み
		fprintf_s(fp, "%02d年 %02d月 %02d日 %02d時 %02d分 %02d秒 : %sがありません。\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}
	//FpsController FPSC(FRAMERATE, 800);

	// ゲームループ
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {

		ClearDrawScreen();		// 画面の初期化
		PAD_INPUT::UpdateKey();
		sceneMng->Draw();
		//FPSC.All();
		//FPSC.Disp();
		//強制終了
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_BACK))
		{
			break;
		}

		ScreenFlip();			// 裏画面の内容を表画面に反映
	}
	return 0;
}