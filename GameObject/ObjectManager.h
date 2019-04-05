#pragma once
#include"../GameObject/Object.h"
#include"../GameObject/Manager/ManagerBase.h"
#include<memory>



/* オブジェクト登録クラス

まずObjectクラスを継承する

コンストラクタはメンバイニシャライザでObjectManagerを受け取る

Entry関数 = ObjectクラスにObjectを継承した物を登録する

Exit関数 = 指定したint型番号の配列を消す。

*/


// MEMO
// 登録を行うObject管理者という意味で付けました。
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

	// MEMO deleteの管理がめんどくさいのでunique_ptrを使いました

	// ここは管理クラスをまとめる所
	std::vector<std::unique_ptr<ManagerBase>>m_mng_lists;
	// オブジェクト管理クラス(更新時にアドレスを入れる)
	std::vector<std::unique_ptr<Object>>m_obj_lists;
};
