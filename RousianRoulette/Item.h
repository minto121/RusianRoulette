#pragma once
class Item
{
private:
	int CigarettesImg; //たばこ
	int LoupeImg;		//ルーペ
	int BeerImg;		//ビール
	int BombImg;		//爆弾
	int CorsolImg;

	

public:

	//�R���X�g���N�^
	Item();

	//�f�X�g���N�^
	~Item();

	//�`��ȊO�̍X�V���������
	void Update();

	void Draw();
};