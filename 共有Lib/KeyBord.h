#pragma once
#define NOMINMAX
#include <Windows.h>


/*
キーボード入力処理を支援するシングルトンクラス

◆注意事項
1. ウィンドウプログラムで動作し、コマンドラインプログラムでは動作しない。
2. ウィンドウが非アクティブの場合（選択されていない場合）は検知しない。
3. 毎フレームupdate関数を一回だけ呼ぶ必要がある。
（多重に呼び出した場合はpressとreleaseが正常に動作しない。）

◆使用例
Keybord& kb = Keybord::getInterface();

while(1) {
kb.update();

if (kb.on(VK_SPACE)) {
// スペースキーが押されている間、ずっと実行される。
}

if (kb.press(VK_LBUTTON)) {
// 右クリックされた瞬間、一度だけ実行される。
}

if (kb.release('A')) {
// Aキーが離された瞬間、一度だけ実行される。
}
}
*/
struct Keybord {
	static Keybord& getInterface() {
		static Keybord kb;
		return kb;
	}

	void update() {
		memcpy(key[1], key[0], sizeof(*key));
		GetKeyboardState(key[0]);
	}

	bool on(int nVirtKey) const {
		return _test(key[0][nVirtKey]);
	}
	bool press(int nVirtKey) const {
		return _test(key[0][nVirtKey]) && !_test(key[1][nVirtKey]);
	}
	bool release(int nVirtKey) const {
		return !_test(key[0][nVirtKey]) && _test(key[1][nVirtKey]);
	}


private:
	BYTE key[2][256] = {};

	Keybord() = default;
	Keybord(const Keybord&) = delete;

	inline bool _test(const BYTE k) const {
		return ((k & 0x80) != 0);
	}
};