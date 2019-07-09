#pragma once
#include"../ChipBase/ChipBase.h"


class NormalChip : public ChipBase {
public:

	NormalChip(int chip_num) {
		m_chip_num = chip_num;
	}
};