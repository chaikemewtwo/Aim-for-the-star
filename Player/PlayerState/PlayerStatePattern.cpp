#include "PlayerStatePattern.h"
#include "WaitState\WaitState.h"
#include "SwimState\SwimState.h"
#include "StandOnState\StandOnState.h"
#include "DamageState\DamageState.h"
#include "DeathState\DeathState.h"


// 初期化
PlayerStatePattern::PlayerStatePattern() :state(new WaitState){}


void PlayerStatePattern::Update() {

}


void PlayerStatePattern::Draw() {

}


void PlayerStatePattern::ChangeState(PlayerStateBase* state) {
	delete this->state;
	this->state = state;
}
