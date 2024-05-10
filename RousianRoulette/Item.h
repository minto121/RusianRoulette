#pragma once
#include"GameMain.h"
class Item
	
{
private:
	
	int CigarettesImg; //たばこ
	int LoupeImg;		//ルーペ
	int BeerImg;		//ビール
	int BombImg;		//爆弾
	int CursolImg;
	int LocationX, LocationY;
	static int ItemNo;
	int Life;
	bool isUseCigarettes;

	

public:

	//�R���X�g���N�^
	Item();

	//�f�X�g���N�^
	~Item();

	//�`��ȊO�̍X�V���������
	void Update();

	void Draw();
};