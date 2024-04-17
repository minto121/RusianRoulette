#pragma once
#include <string>

class Ranking
{
public:
	struct RANKING_DATA {
		int  no;
		std::string name;
		long int score;
	};
private:
	RANKING_DATA rankingData[5];

public:
	void ReadRanking();
	void WriteRanking(std::string _name, long int stage);

	RANKING_DATA GetRankingData(int index) { return rankingData[index]; }
};