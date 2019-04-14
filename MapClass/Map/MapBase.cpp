#include"../MapClass/Map/MapBase.h"




// マップを読み込む
void MapBase::MapLoad(const std::string&file_name) {

	FILE*fp;
	char str[256];

	fopen_s(&fp,file_name.c_str(), "r");

	if (fp == NULL) {
		return;
	}

	int h = 0;

	// 文字列読み込み、改行まで
	while (fgets(str, 256, fp) != NULL) {

		// 最初が改行と空白なら戻す
		if (str[0] == '\n' || str[0] == '\0') {
			h++;
			continue;
		}

		for (int j = 0; j < str[j] != '\0'; j++) {

			if (str[j] == ',') {
				continue;
			}

			char *str2 = &str[j];
			// 整数値変換
			chip[h][j] = strtol(str2, NULL, 10);

			printf("%d", chip[h][j]);
		}
		printf("\n");

		// 文字列初期化
		str[0] = '\0';

		h++;
	}

	fclose(fp);// ファイルを閉じる
	return;
}