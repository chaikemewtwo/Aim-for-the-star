#include "Rope.h"
#include <cmath>


Rope::Rope(Player* p_1, Player* p_2) {
	p1 = p_1;
	p2 = p_2;
}

void Rope::Update() {
	p1_pos_x = p1->GetPosX();
	p1_pos_y = p1->GetPosY();
	p2_pos_x = p2->GetPosX();
	p2_pos_y = p2->GetPosY();
}

void Rope::Draw() {
	Texture::Draw2D(
		"Resource/Texture/Player/himo.png",
		p1_pos_x,
		p1_pos_y,
		1.f,
		1.f/*,
		RopeAngleCalc()*/
	);
}

float Rope::RopeAngleCalc() {
	float a = (p1_pos_y - p2_pos_y) / (p1_pos_x - p2_pos_x);
	float angle = atan(a);
	return angle;
}
