#include "PlayerBase.h"


PlayerBase::PlayerBase() {
	pos_x = 0.f;
	pos_y = 0.f;
}

void PlayerBase::AddGravity() {
	speed += GRAVITY;
	pos_y += speed;
}

void PlayerBase::SwimUp() {
	speed = Y_ADD;
	pos_y += speed;
}

void PlayerBase::XMove(bool move_right) {
	// X•ûŒüˆÚ“®ATRUE‚Å‰E‚ÖˆÚ“®
	pos_x += move_right ? X_ADD : -X_ADD;
}
