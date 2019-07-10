#pragma once
#include"../ChipBase/ChipBase.h"


class NormalChip : public ChipBase {
public:

	NormalChip(int chip_num) : ChipBase(){
		m_chip_num = chip_num;
		m_is_chip_active = false;
	}

	NormalChip() :ChipBase(){
		m_is_chip_active = false;
	}
};