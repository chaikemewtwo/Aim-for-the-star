#pragma once
#pragma comment(lib, "xinput.lib")
#include <XInput.h>


template<DWORD index = 0>
struct Gamepad {
	bool connected = false;

	static Gamepad& getInterface() {
		static Gamepad gp;
		return gp;
	}

	bool update() {
		XINPUT_STATE s;
		if (XInputGetState(index, &s) == 0) {
			connected = true;
			data[1] = data[0];
			data[0] = s.Gamepad;
		}
		else {
			connected = false;
		}
		return connected;
	}

	bool on(WORD btn) const {
		return ((data[0].wButtons & btn) != 0);
	}
	bool press(WORD btn) const {
		return (data[0].wButtons != data[1].wButtons) && on(btn);
	}
	bool release(WORD btn) const {
		return (data[0].wButtons != data[1].wButtons) && !on(btn);
	}

	float getLeftTrigger() const {
		return data[0].bLeftTrigger / 255.f;
	}
	float getRightTrigger() const {
		return data[0].bRightTrigger / 255.f;
	}

	float getLeftStickX() const {
		return _stick(data[0].sThumbLX);
	}
	float getLeftStickY() const {
		return _stick(data[0].sThumbLY);
	}
	float getRightStickX() const {
		return _stick(data[0].sThumbRX);
	}
	float getRightStickY() const {
		return _stick(data[0].sThumbRY);
	}

	void setHifqVibration(float v) {
		if (v < 0.f) v = 0.f;
		else if (v > 1.f) v = 1.f;
		vib.wRightMotorSpeed = (WORD)(v * 65535.f);
		XInputSetState(index, &vib);
	}
	void setLofqVibration(float v) {
		if (v < 0.f) v = 0.f;
		else if (v > 1.f) v = 1.f;
		vib.wLeftMotorSpeed = (WORD)(v * 65535.f);
		XInputSetState(index, &vib);
	}


private:
	XINPUT_GAMEPAD data[2] = {};
	XINPUT_VIBRATION vib = {};

	Gamepad() {
		update();
	}
	~Gamepad() {
		XInputEnable(false);
	}

	float _stick(SHORT v) const {
		static const SHORT stick_dead_zone = 8192;
		static const float stick_div = 32768.f - (float)stick_dead_zone;

		if (v > stick_dead_zone) {
			return (v - stick_dead_zone) / stick_div;
		}
		else if (v < -stick_dead_zone) {
			return (v + stick_dead_zone) / stick_div;
		}
		return 0.f;
	}
};