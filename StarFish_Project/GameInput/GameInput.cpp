#include "GameInput.h"


bool GameInput::InputCommand(INPUT_BUTTON button, INPUT_STATE state) {
	Keybord& kb = Keybord::getInterface();

	auto& pad1 = Gamepad<0>::getInterface();
	auto& pad2 = Gamepad<1>::getInterface();
	pad1.update();
	pad2.update();

	switch (button){
	case GameInput::P1_LEFT_BUTTON:
		if (kb.on('A') || pad1.on(XINPUT_GAMEPAD_DPAD_LEFT) || pad1.getLeftStickX() < -0.5f) {
			return true;
		}
		break;
	case GameInput::P1_RIGHT_BUTTON:
		if (kb.on('D') || pad1.on(XINPUT_GAMEPAD_DPAD_RIGHT) || pad1.getLeftStickX() > 0.5f) {
			return true;
		}
		break;
	case GameInput::P1_DECIDE_BUTTON:
		if (kb.on('W') || pad1.on(XINPUT_GAMEPAD_A) || pad1.on(XINPUT_GAMEPAD_B)) {
			return true;
		}
		break;
	case GameInput::P2_LEFT_BUTTON:
		if (kb.on(VK_LEFT) || pad2.on(XINPUT_GAMEPAD_DPAD_LEFT) || pad2.getLeftStickX() < -0.5f) {
			return true;
		}
		break;
	case GameInput::P2_RIGHT_BUTTON:
		if (kb.on(VK_RIGHT) || pad2.on(XINPUT_GAMEPAD_DPAD_RIGHT) || pad2.getLeftStickX() > 0.5f) {
			return true;
		}
		break;
	case GameInput::P2_DECIDE_BUTTON:
		if (kb.on(VK_UP) || pad2.on(XINPUT_GAMEPAD_A) || pad2.on(XINPUT_GAMEPAD_B)) {
			return true;
		}
		break;
	case GameInput::START_BUTTON:
		if (kb.press(VK_SPACE) || pad1.press(XINPUT_GAMEPAD_START) || pad2.press(XINPUT_GAMEPAD_START)) {
			return true;
		}
	default:
		break;
	}
	return false;
}
