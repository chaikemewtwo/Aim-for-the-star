#pragma once


// 前方参照
class EnemyManager;
class Player;
class Map;
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
	Map GetMapInstance()const;
	float GetMaxMapPos()const;
	bool IsMaxMapRange()const;// マップが最大値になったら返す

private:

	// オブジェクトの参照
	Map *m_p_map;                              // マップの選択
	BackGround *m_p_bg1;                       // 背景
	BackGround *m_p_bg2;                       // 奥行用の背景
};
