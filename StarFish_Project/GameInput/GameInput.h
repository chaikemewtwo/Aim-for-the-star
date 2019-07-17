#pragma once
#include"../../Lib/Input/KeyBord.h"
#include"../../Lib/Input/GamePad.h"


// 今回使用する入力（キー、パッド）をまとめたクラス
class GameInput {
public:
	enum INPUT_BUTTON {
		P1_LEFT_BUTTON,		// プレイヤー1の左ボタン
		P1_RIGHT_BUTTON,	// プレイヤー1の右ボタン
		P1_DECIDE_BUTTON,	// プレイヤー1の決定ボタン
		P2_LEFT_BUTTON,		// プレイヤー2の左ボタン
		P2_RIGHT_BUTTON,	// プレイヤー2の右ボタン
		P2_DECIDE_BUTTON,	// プレイヤー2の決定ボタン
		START_BUTTON		// スタートボタン
	};

	enum INPUT_STATE {
		NOT_PUSH,		// 押されてない
		PUSH_ENTER,		// 押された瞬間
		PUSH_ON,		// 押されてる
		PUSH_EXIT,		// 離された瞬間
	};

public:
	// 今回使用するボタンの入力情報を管理
	// 引数(入力情報を受け取りたいプレイヤー,入力情報を受け取りたいボタン,第一引数のボタンの入力状態)
	// 戻り値:対応する入力状態を満たしたとき（満たしているとき）trueを返す
	bool InputButton(INPUT_BUTTON button, INPUT_STATE state);

private:

	// パッドの左スティックが一定以上に倒れることでtrueを返す関数
	// 引数(左方向に倒れたときに使用する場合true)
	// 戻り値:一定以上倒れているときtrue、それ以外false
	bool LeftStickXInput(bool left);
};
