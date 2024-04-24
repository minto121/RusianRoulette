#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "PadInput.h"


//�^�C�g�����j���[
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

	//�t�H���g�̒ǉ�
	MenuFont = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 64, 8, DX_FONTTYPE_ANTIALIASING);

	//�^�C�g���摜�̓ǂݍ���
	if ((TitleImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	// �J�[�\���摜�̓ǂݍ���
	if ((CursorImg = LoadGraph("Resource/Images/Apple_Red.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}
	//BGM�̓ǂݍ���
	if ((TitleBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(140, TitleBGM);

	//SE�̓ǂݍ���
	if ((MenuSE = LoadSoundMem("Resource/sounds/SE/select01.wav")) == -1) //�I��SE
	{
		throw "Resource/sounds/SE/select01.wav";
	}
	//SE�̉��ʕύX
	ChangeVolumeSoundMem(110, MenuSE);

	//BGM�̍Đ�
	if (CheckSoundMem(TitleBGM) == 0)
	{
		PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP);
	}

}

Title::~Title()
{
	//�t�H���g�̍폜
	DeleteFontToHandle(MenuFont);

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
		//	//�����L���O��ʂ�
		//case TITLE_MENU::GAME_RANKING:
		//	return new DrawRanking();
		//	//StopSoundMem(TitleBGM);
		//	break;
		//	//�w���v���
		//case TITLE_MENU::GAME_HELP:
		//	return new Help();
		//	//StopSoundMem(TitleBGM);
		//	break;
		//	//�G���h��ʂ�
		//case TITLE_MENU::GAME_END:
		//	return new End();
		//	//StopSoundMem(TitleBGM);
		//	break;
		default:
			break;
		}
	}
	return this;
}

void Title::Draw()const
{
	//�^�C�g���̕`��
	DrawGraph(0, 0, TitleImg, FALSE);
	DrawStringToHandle(150, 100, "��񂲂��Ƃ�", 0xffffff, MenuFont);

	//���j���[�̕`��
	DrawStringToHandle(730, 240, "�����[��", 0xffffff, MenuFont);
	DrawStringToHandle(730, 320, "��񂫂�", 0xffffff, MenuFont);
	DrawStringToHandle(730, 400, "�ւ��", 0xffffff, MenuFont);
	DrawStringToHandle(730, 480, "�����", 0xffffff, MenuFont);

	//�J�[�\���̕`��
	int select_y = 230 + Select * 80;
	DrawGraph(650, select_y, CursorImg, TRUE);
}