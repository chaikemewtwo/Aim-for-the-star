#pragma once
#include"../../Lib/Texture/Texture.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"EnemyBase.h"

// ウニクラス
class SeaUrchin :public EnemyBase{
public:
	SeaUrchin(float x, float y);
	~SeaUrchin() {}
	void Init()override;
	void Update()override;
	void Draw()override;
	bool GetDeadFlag();

private:
	// 座標
	float m_posx;
	float m_posy;
	// true＝削除
	bool is_dead;
};
