﻿#pragma once

class PlayerBase;


// 状態基底クラス
class PlayerStateBase {
public:
	virtual void Init(PlayerBase * p) = 0;
	virtual void Update(PlayerBase * p) = 0;
	virtual ~PlayerStateBase() {};
};
