#include"SetRenderStateFile.h"



void SetRenderStateConfig() {
	
	// シェードモード:グラデーション
	dev->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);
	// カリングモード無し
	dev->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	// Zバッファオフ
	dev->SetRenderState(D3DRS_ZENABLE, FALSE);
	dev->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	dev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	// ライトoff
	dev->SetRenderState(D3DRS_LIGHTING, FALSE);
	// スぺきゅら光オン
	dev->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	// アルファチャンネルオン
	dev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 通常ブレンディング
	dev->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//dev->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
	// アルファテスト
	dev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	dev->SetRenderState(D3DRS_ALPHAREF, 0x0000000);
	dev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//// テクスチャαブレンド
	//dev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//dev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//dev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//dev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//dev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//dev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
	// tu tvが超えているかもしれない
	// ワープをクランプに変える
}