#include"SetRenderStateFile.h"



void SetRenderStateConfig() {
	
	// シェードモード:グラデーション
	//Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);
	// カリングモード無し
	//Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	// Zバッファオフ
	D3D9::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ZENABLE, FALSE);
	D3D9::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	D3D9::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	// ライトoff
	//Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_LIGHTING, FALSE);
	// スぺきゅら光オン
	//Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	// アルファチャンネルオン
	D3D9::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 通常ブレンディング
	D3D9::GetLpDirect3DDevice9()->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	D3D9::GetLpDirect3DDevice9()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
	// アルファテスト
	D3D9::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	D3D9::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ALPHAREF, 0x0000000);
	D3D9::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//// テクスチャαブレンド
	//Graphics::GetLpDirect3DDevice9()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//Graphics::GetLpDirect3DDevice9()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//Graphics::GetLpDirect3DDevice9()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//Graphics::GetLpDirect3DDevice9()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//Graphics::GetLpDirect3DDevice9()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//Graphics::GetLpDirect3DDevice9()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
	// tu tvが超えているかもしれない
	// ワープをクランプに変える
}