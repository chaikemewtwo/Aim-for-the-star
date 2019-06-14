﻿#pragma once
#include"../../Lib/Input/KeyBord.h"
#include"../../Lib/Input/GamePad.h"

class Player;

// 状態基底クラス
class PlayerStateBase {
public:
	virtual void Init(Player * p) = 0;
	virtual void Update(Player * p) = 0;
	virtual ~PlayerStateBase() {};
};
