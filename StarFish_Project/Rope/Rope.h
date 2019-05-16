#pragma once

#include "../Player/Player.h"

class Rope:public Object {
public:
	Rope(Player* p1,Player* p2);

	void Update()override;
	void Draw()override;

private:
	Player* p1;
	Player* p2;

	float RopeAngleCalc();

	float p1_pos_x;
	float p1_pos_y;
	float p2_pos_x;
	float p2_pos_y;
};

