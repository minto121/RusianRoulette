#include"DxLib.h"
#include"Ranking.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define RANKING_FILE_NAME "Ranking.txt"

void Ranking::ReadRanking() {
	std::ifstream ifs(RANKING_FILE_NAME);

	std::string line;
	for (int i = 0; std::getline(ifs, line); i++) {
		std::istringstream stream(line);
		std::string str;
		for (int j = 0; std::getline(stream, str, ','); j++) {
			if (j == 0) {
				rankingData[i].no = std::stoi(str);
			}
			else if (j == 1) {
				rankingData[i].name = str;
			}
			else {
				rankingData[i].score = std::stol(str);
			}
		}
	}
}

void Ranking::WriteRanking(std::string _name, long int stage) {
	std::ofstream ofs(RANKING_FILE_NAME);

	rankingData[4].name = _name;
	rankingData[4].score = stage;
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 5; j++) {
			if (rankingData[i].score < rankingData[j].score) {
				RANKING_DATA temp = rankingData[i];
				rankingData[i] = rankingData[j];
				rankingData[j] = temp;
			}
		}
	}

	rankingData[0].no = 1;
	for (int i = 1; i < 5; i++) {
		if (rankingData[i - 1].score == rankingData[i].score) {
			rankingData[i].no = rankingData[i - 1].no;
		}
		else {
			rankingData[i].no = i + 1;
		}
	}

	for (int i = 0; i < 5; i++) {
		ofs << rankingData[i].no << "," << rankingData[i].name.c_str() << "," << rankingData[i].score << std::endl;
	}
}