#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "PadInput.h"
#include "DrawRanking.h"
#include "ResultScene.h"

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

	
	////�^�C�g���摜�̓ǂݍ���
	//if ((TitleImg = LoadGraph("Resource/Images/mori.png")) == -1)
	//{
	//	throw "Resource/Images/mori.png";
	//}
	//// �J�[�\���摜�̓ǂݍ���
	//if ((CursorImg = LoadGraph("Resource/Images/Apple_Red.png")) == -1)
	//{
	//	throw "Resource/Images/apple.png";
	//}
	////BGM�̓ǂݍ���
	//if ((TitleBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	//{
	//	throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	//}
	////BGM�̉��ʕύX
	//ChangeVolumeSoundMem(140, TitleBGM);

	////SE�̓ǂݍ���
	//if ((MenuSE = LoadSoundMem("Resource/sounds/SE/select01.wav")) == -1) //�I��SE
	//{
	//	throw "Resource/sounds/SE/select01.wav";
	//}
	////SE�̉��ʕύX
	//ChangeVolumeSoundMem(110, MenuSE);

	////BGM�̍Đ�
	//if (CheckSoundMem(TitleBGM) == 0)
	//{
	//	PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP);
	//}

}

Title::~Title()
{

	StopSoundMem(TitleBGM);
	//�T�E���h�̍폜
	DeleteSoundMem(TitleBGM);
	DeleteSoundMem(MenuSE);
}

AbstractScene* Title::Update()
{
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

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		switch (static_cast<TITLE_MENU>(Select))
		{
			//�Q�[����ʂ�
		case TITLE_MENU::GAME_START:

			return new GameMain();
			break;
			//�����L���O��ʂ�
		case TITLE_MENU::GAME_RANKING:
			return new DrawRankingScene(100);
			//StopSoundMem(TitleBGM);
			break;
			//�w���v���
		case TITLE_MENU::GAME_HELP:
			return new GameMain();
			//StopSoundMem(TitleBGM);
			break;
			//�G���h��ʂ�
		case TITLE_MENU::GAME_END:
			return new ResultScene();
			//StopSoundMem(TitleBGM);
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

	//DrawCircle(Select, Select, 10, GetColor(0, 255, 0), TRUE);

	//�^�C�g���̕`��
	DrawGraph(0, 0, TitleImg, FALSE);
	DrawFormatString(370, 100, 0xffffff, "Russian Roulette", 0xffffff);

	SetFontSize(48);

	//���j���[�̕`��
	DrawFormatString(520, 380, 0xffffff, "START");
	DrawFormatString(520, 460, 0xffffff, "HELP");
	DrawFormatString(520, 540, 0xffffff, "RANKING");
	DrawFormatString(520, 620, 0xffffff, "END");

	//�J�[�\���̕`��
	int select_y = 400 + Select * 80;
	//DrawGraph(650, select_y, CursorImg, TRUE);

	DrawCircle(480, select_y, 10, GetColor(0, 255, 0), TRUE);
}