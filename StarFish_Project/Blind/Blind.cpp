#include"Blind.h"
#include"../Lib/Texture/TextureBoad2D.h"


Blind::Blind() {
	// 調整中
}

void Blind::Update() {
	// 確認のための処理
	m_is_active = false;
}

void Blind::Draw() {
	// ブラインドの小魚を描画(アニメーションあり)
	Texture::Draw2D(
		"Resource/uni.png",
		m_pos.x, m_pos.y,
		1, 1, 0, 0.5, 0.5, false);
}

void Blind::Create(D3DXVECTOR2 pos) {
	m_pos = pos;
}
