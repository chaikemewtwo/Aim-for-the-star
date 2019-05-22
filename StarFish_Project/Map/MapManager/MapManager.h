#pragma once


// 前方参照
class EnemyManager;
class Player;
class MapChip;
class BackGround;
class ObjectManager;


// マップ管理
class MapManager {
public:

	// EnemyManagerも入れる
	MapManager(Player*star1,Player*star2, EnemyManager*e_mng,ObjectManager*obj_mng);

	~MapManager();

	// 更新と描画
	void Update();
	void Draw();

	// 後の更新と描画
	MapChip GetMapInstance()const;

private:

	// 参照
	MapChip *m_pmap_tip; // マップの選択
	BackGround*m_pbg;     // 背景
	BackGround *m_pbg2;   // 奥行用の背景
	ObjectManager*m_pobj_mng;// オブジェクト管理
};
