#pragma once
#include"../GameObject/Object.h"
#include"../GameObject/Manager/ManagerBase.h"
#include<memory>



/* 説明書

①Objectクラスを継承する。

②ObjectManagerを仮引数に書く。

③ObjectManagerを実引数に入れる。

②Entry関数でオブジェクトを登録する。

生成と削除は下の関数を使う
Entry関数 = ObjectクラスにObjectを継承した物を登録する。
Exit関数 = 指定したint型番号の配列を消す。

*/


// オブジェクト管理クラス
class ObjectManager {
public:

	ObjectManager();

	// 更新
	void Update();
	// 描画
	void Draw();

	// 要素の追加
	void Entry(Object*obj);
	// 配列の削除(メモリの削除ではない)
	void Exit(int id);

private:

	// ここは管理クラスをまとめる所
	std::vector<std::unique_ptr<ManagerBase>>m_mng_lists;
	// オブジェクト管理クラス(更新時にアドレスを入れる)
	std::vector<std::unique_ptr<Object>>m_obj_lists;
};
