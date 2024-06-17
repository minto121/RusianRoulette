#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "PadInput.h"
#include "DrawRanking.h"
#include "ResultScene.h"
#include "EndScene.h"
#include "InputRanking.h"
#include "HelpScene.h"

enum class TITLE_MENU
{
	GAME_START = 0,
	GAME_RANKING,
	GAME_HELP,
	GAME_END
};

Title::Title()
{
	//������
	Select = 0;
	Once = TRUE;
	TitleBgm = LoadSoundMem("Resources/sounds/I like.wav");
	MenuSE = LoadSoundMem("Resources/sounds/cursorsound.mp3");
	ASE = LoadSoundMem("Resources/sounds/kettei.mp3");

	TitleImg = LoadGraph("resouce/image/title.png");
	CursorImg=LoadGraph("resouce/image/BulletCur.png");
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

	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 3;
	}
	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 3)Select = 0;
	}

	//L�X�e�B�b�N�����
	if (PAD_INPUT::GetLStick().ThumbY > 10000 && Once == TRUE)
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 3;
		Once = FALSE;
	}

	//L�X�e�B�b�N������
	if (PAD_INPUT::GetLStick().ThumbY < -10000 && Once == TRUE)
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 3)Select = 0;
		Once = FALSE;
	}

	//L�X�e�B�b�N�����ɖ߂��ꂽ��Once����Z�b�g
	if (Once == FALSE && PAD_INPUT::GetLStick().ThumbY < 10000 && PAD_INPUT::GetLStick().ThumbY > -10000)
	{
		Once = TRUE;
	}

	if (PAD_INPUT::OnRelease(XINPUT_BUTTON_A))
	{
		PlaySoundMem(ASE, DX_PLAYTYPE_BACK);

		switch (static_cast<TITLE_MENU>(Select))
		{
			//�Q�[����ʂ�
		case TITLE_MENU::GAME_START:
			return new GameMain();
			StopSoundMem(TitleBgm);
			break;
			//�����L���O��ʂ�
		case TITLE_MENU::GAME_RANKING:
			return new HelpScene();
			StopSoundMem(TitleBgm);
			break;
			//�w���v���
		case TITLE_MENU::GAME_HELP:
			return new DrawRankingScene(100);
			StopSoundMem(TitleBgm);
			break;
			//�G���h��ʂ�
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

	//DrawCircle(Select, Select, 10, GetColor(0, 255, 0), TRUE);

	//�^�C�g���̕`��
	DrawGraph(0, 0, TitleImg, FALSE);
	//DrawFormatString(370, 100, 0xffffff, "Russian Roulette", 0xffffff);

	SetFontSize(48);

	//���j���[�̕`��
	//DrawFormatString(520, 380, 0xffffff, "START");
	//DrawFormatString(520, 460, 0xffffff, "RANKING");
	//DrawFormatString(520, 540, 0xffffff, "HELP");
	//DrawFormatString(520, 620, 0xffffff, "END");

	//�J�[�\���̕`��
	int select_y = 360 + Select * 80;
	//DrawGraph(650, select_y, CursorImg, TRUE);

	//DrawCircle(480, select_y, 10, GetColor(0, 255, 0), TRUE);
	DrawGraph(550, select_y,CursorImg,TRUE);
	
	DrawGraph(1280, 720, TitleImg, TRUE);
}