#include "DxLib.h"
#include "ResultScene.h"
#include "GameMain.h"
#include "Padinput.h"

ResultScene::ResultScene()
{
	Select = 0;
	Once = TRUE;
}

ResultScene::~ResultScene()
{

}

AbstractScene* ResultScene::Update()
{
	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		//PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 3;
	}
	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		//PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 3)Select = 0;
	}

	//L�X�e�B�b�N�����
	if (PAD_INPUT::GetLStick().ThumbY > 10000 && Once == TRUE)
	{
		//PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 3;
		Once = FALSE;
	}

	//L�X�e�B�b�N������
	if (PAD_INPUT::GetLStick().ThumbY < -10000 && Once == TRUE)
	{
		//PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 3)Select = 0;
		Once = FALSE;
	}

	//L�X�e�B�b�N�����ɖ߂��ꂽ��Once����Z�b�g
	if (Once == FALSE && PAD_INPUT::GetLStick().ThumbY < 10000 && PAD_INPUT::GetLStick().ThumbY > -10000)
	{
		Once = TRUE;
	}

	return this;
}

void ResultScene::Draw()const
{
	int select_y = 230 + Select * 80;
	DrawGraph(650, select_y, CursorImg, TRUE);
}