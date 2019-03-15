#pragma once
#include "PlayerBase.h"


// 自機2クラス
class Star2 : public PlayerBase {
public:
	Star2();
	~Star2();

	// 更新処理
	void Update() override;
	// 描画処理
	void Draw() override;

private:

};
