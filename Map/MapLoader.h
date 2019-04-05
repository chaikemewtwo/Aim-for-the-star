#pragma once
#include<string>
#include<vector>


class MapLoader {
public:

	// ファイル名を受け取って使う
	void Load(const std::string&map_name) {

		FILE*pf;// ファイル入出力ストリーム
		std::string fname = "sample.csv";

		// ファイルオープン
		fopen_s(&pf, fname.c_str(), "r");

		// ファイルオープン出来てない場合は強制終了
		if (pf == NULL) {
			return;
		}

		// 文字列バッファ
		char* buf;
		int *buf_int;

		// 文字列の終わりと改行ありで終わり
		while (fgets(buf, 256, pf) != NULL || fgets(buf, 256, pf) != "\0") {


			*buf_int = fscanf(pf, buf, buf_int);
		}

		// ファイルを閉じる
		fclose(pf);

	}

private:
	// 背景の名前リスト
	std::vector<std::string>bg_name_list;
	std::vector<std::vector<int>>map_chip;
};