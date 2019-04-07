#include"../MapClass/Map/MapLoader.h"
#include"../MapClass/Map/MapData.h"



MapData MapLoader::GetToLoadToCreateTheMapData(const std::string&map_name,const std::string&bg_name) {

	// マップの情報を生成
	MapData *md = new MapData;

	MapLoad(map_name);
	BGLoad(bg_name);

	return *md;
}


MapData MapLoader::MapLoad(const std::string&map_name) {


	FILE*fp;
	char str[256];

	fopen_s(&fp,map_name.c_str(), "r");

	if (fp == NULL) {
		
		return;
	}

	int box[50][50] = {};
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
			box[h][j] = strtol(str2, NULL, 10);
			printf("%d", box[h][j]);
		}
		printf("\n");

		// 文字列初期化
		str[0] = '\0';

		h++;
	}

	fclose(fp);// ファイルを閉じる
	return;
}

void MapLoader::BGLoad(const std::string&bg_name) {

}