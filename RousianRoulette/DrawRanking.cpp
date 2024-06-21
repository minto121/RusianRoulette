#include "DrawRanking.h"
#include "PadInput.h"
#include "DxLib.h"
#include "Title.h"

DrawRankingScene::DrawRankingScene(int round) {
	ranking.ReadRanking();
	for (int i = 0; i < 5; i++) {

		rankingData[i] = ranking.GetRankingData(i);
	}

	image = LoadGraph("Resources/images/Ranking_bg.png");
	DesideSE = LoadSoundMem("Resources/sounds/kettei.mp3");

}

AbstractScene* DrawRankingScene::Update() {
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == 1) {
		PlaySoundMem(DesideSE, DX_PLAYTYPE_BACK);

		return new Title();

	}

	return this;
}

void DrawRankingScene::Draw() const {
	DrawGraph(0, 0, image, TRUE);

	SetFontSize(100);
	DrawString(450, 100, "RANKING", 0xff0000);

	SetFontSize(60);
	for (int i = 0; i < 5; i++) {

		DrawFormatString(350, 300 + 50 * i, 0xffffff, "%d %4s ", rankingData[i].no, rankingData[i].name.c_str());
		DrawFormatString(650, 300 + 50 * i, 0xffffff, "%5ld", rankingData[i].score);
	}

	SetFontSize(40);
	DrawString(550, 610, "A  PUSH", 0xff0000);
}