#pragma once
#include<Windows.h>
#include<d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")


// =============================
/**
* @file Window.h
* @brief ウィンドウ関連の関数群
* @author maekawa
* @date 2019/06/12
*/
// =============================


namespace Window {


	// 横のウィンドウサイズ
	constexpr float WIDTH = 1920.f;
	// 縦のウィンドウサイズ
	constexpr float HEIGHT = 1080.f;


	/**
	* @brief ウィンドウの初期化
	* @param[in] width_size 横のウィンドウサイズ
	* @param[in] heignt_size 縦のウィンドウサイズ
	* @return bool 初期化に成功すればtrue,失敗すればfalseを返す
	*/
	bool Init(const int width_size = WIDTH, const int height_size = HEIGHT);


	/**
	* @brief メッセージ処理
	* @return bool メッセージの受け取りに成功すればtrue,失敗すればfalseを返す
	*/
	bool ProcessMessage();


	/**
	* @brief ウィンドウサイズを変更する
	* @param[out] width_resize 横のサイズ
	* @param[out] height_resize 縦のサイズ
	*/
	void SetReSize(const UINT&width_size, const UINT&height_size);


	/**
	* @brief ウィンドウを中央に移動させる
	*/
	void SetCenterMove();


	/**
	* @brief ウィンドウハンドルのゲッター
	* @return HWND ウィンドウハンドルを返す
	*/
	HWND GetWindowHandle();


	// HACK　まだ使えません
	// フルスクリーンに対応したウィンドウにする
	//void FullScreenWindowStyleChange();
}
