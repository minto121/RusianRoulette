#pragma once
#include "AbstractScene.h"
#include "Ranking.h"

class DrawRankingScene : public AbstractScene
{
private:
	Ranking ranking;
	Ranking::RANKING_DATA rankingData[5];

	int image;
	int bgm;
	int TitleSE2;

public:
	DrawRankingScene(int _score);

public:
	virtual void Draw()const override;
	virtual AbstractScene* Update()override;
};

