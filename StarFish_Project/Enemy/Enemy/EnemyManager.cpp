#include"EnemyManager.h"

EnemyManager::EnemyManager() {
	// ランダム生成のためのシード値設定
	srand((unsigned int)time(nullptr));
}
//――――――――――――――――――――――――――

EnemyManager::~EnemyManager() {
	for(auto &it:m_seaurchin){
		if (it != nullptr) {
			delete it;
		}
	}
}
//――――――――――――――――――――――――――

// 更新関数
void EnemyManager::Update() {
	Create();

	// 要素数分ループ
	for (auto it : m_seaurchin) {
		// 各要素のUpdate関数を呼ぶ
		it->Update();
	}
	
	
}
//―――――――――――――――――――――――――――

// 描画関数
void EnemyManager::Draw() {
	for (auto it : m_seaurchin) {
		// 各要素の描画処理
		it->Draw();
	}
}
//―――――――――――――――――――――――――――

// 敵生成関数
void EnemyManager::Create() {
	// 敵の最大数と配列サイズの差分を保存
	float diff = Enemy_Max_Num - m_seaurchin.size();

	// 差分だけ配列を回す
	for (int num = 0; num < diff; num++) {
		// 要素数が生成数に達していなければ
		if (m_seaurchin.size() < Enemy_Max_Num) {
			float x = (rand() % (WINDOW_W_INT - 100));
			float y = (rand() % (WINDOW_H_INT - 100));

			// 一定の確率で敵を生成
			if (rand() % 100 == 0) {
				// ランダムに割り出したxyを使用して敵を登録
				m_seaurchin.emplace_back(new SeaUrchin(x, y));
			}
		}
	}
}
//―――――――――――――――――――――――――――

void EnemyManager::Delete() {
	// 要素指定用の変数
	int num = 0;
	// 仮の削除ループ　　《要変更》
	for (auto it : m_seaurchin) {
		// デッドフラグがtrueであれば、該当の要素を削除
		if (it->IsDead() == true) {
			m_seaurchin.erase(m_seaurchin.begin() + num);
		}
		num++;
	}
}
