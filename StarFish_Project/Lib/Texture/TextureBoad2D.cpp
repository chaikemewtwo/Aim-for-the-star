#include"../Texture/TextureBoad2D.h"
#include"Texture.h"
#include"../UV/UV.h"

// 既存
#include<d3dx9.h>
#include<unordered_map>


// ---頂点を設定する構造体---
struct CustomVertex
{
	D3DXVECTOR3 vtx;     // 頂点座標
	FLOAT rhw;           // 除算数
	DWORD color;         // カラー
	D3DXVECTOR2 tex_pos; // テクスチャ座標
};


// テンプレート2DFVF
#define FVF_2D (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE)


// 拡縮回転移動を行列計算する
D3DXMATRIX GetMatrixTransformCalc(float x, float y, float width_scale, float height_scale, float angle);
// サンプラーステートを設定
bool SetSamplerStateSelect(Texture::SamplerStateType type);

namespace Texture {


	// 描画関係
	void Draw2DGraph(
		const char*file_name,
		const float&pos_x,
		const float&pos_y
	) {
		Draw2D(
			file_name,
			pos_x,
			pos_y
		);
	}


	void Draw2DTransGraph(
		const char*file_name,
		const float&pos_x,
		const float&pos_y,
		const float&scale_x,
		const float&scale_y,
		const float&angle
	) {
		Draw2D(
			file_name,
			pos_x,
			pos_x,
			pos_y,
			scale_x,
			scale_y,
			angle
		);
	}


	void Draw2DRotaGraph(
		const char*file_name,
		const float&pos_x,
		const float &pos_y,
		const float&angle
	) {
		Draw2D(
			file_name,
			pos_x,
			pos_y,
			1.f,
			1.f,
			angle,
			0.5f,
			0.5f
		);
	}


	void Draw2DAnimationGraph(
		const char*file_name,
		const float&pos_x,
		const float&pos_y,
		const int &tu_cut_num,
		const int&tv_cut_num,
		const int&anim_num
	) {
		Draw2D(
			file_name,
			pos_x,
			pos_y,
			(float)(1.f / (float)tu_cut_num),
			(float)(1.f / (float)tv_cut_num),
			0.f,
			0.f,
			0.f,
			true,
			tu_cut_num,
			tv_cut_num,
			anim_num
		);
	}


	void Draw2DRotaAnimation(
		const char*file_name,
		const float&pos_x,
		const float&pos_y,
		const float &angle,
		const int &tu_cut_num,
		const int&tv_cut_num,
		const int&anim_num
	) {
		Draw2D(
			file_name,
			pos_x,
			pos_y,
			(float)(1.f / (float)tu_cut_num),
			(float)(1.f / (float)tv_cut_num),
			angle,
			0.f,
			0.f,
			true,
			tu_cut_num,
			tv_cut_num,
			anim_num
		);
	}


	void Draw2DUVShift(
		const char*file_name,
		const float &pos_x,
		const float &pos_y,
		const float&shift_tu,
		const float&shift_tv
	) {
		Draw2D(
			file_name,
			pos_x,
			pos_y,
			1.f,
			1.f,
			0.f,
			0.f,
			0.f,
			false,
			0,
			0,
			0,
			shift_tu, shift_tv
		);
	}


	void Draw2DAnimationUVSampler(
		const char * file_name,
		const float &pos_x,
		const float&pos_y,
		const int&tu_cut_num,
		const int&tv_cut_num,
		const int&animation_num,
		SamplerStateType sampler_state_type
	) {

		Draw2D(
			file_name,
			pos_x,
			pos_y,
			(float)(1.f / (float)tu_cut_num),
			(float)(1.f / (float)tv_cut_num),
			0.f,
			0.f,
			0.f,
			true,
			tu_cut_num,
			tv_cut_num,
			animation_num,
			0.f,
			0.f,
			sampler_state_type
		);
	}


	namespace Size {


		// サイズ取得関数
		float GetGraphSizeX(const char*file_name) {
			TextureData *tex_d = &Texture::GetData(file_name);
			return tex_d->Width;
			return 0.f;
		}


		float GetGraphSizeY(const char*file_name) {
			TextureData *tex_d = &Texture::GetData(file_name);
			return tex_d->Height;
			return 0.f;
		}


		D3DXVECTOR2 GetGraphSizeVec2(const char*file_name) {
			return D3DXVECTOR2(
				GetGraphSizeX(file_name),
				GetGraphSizeY(file_name));
		}


		// 分割画像サイズの一つ分を取得
		// div_numはXかYの分割数を入れる
		float GetDivGraphSizeXByCutSize(const char*file_name, int div_num_x) {
			return (GetGraphSizeX(file_name) / div_num_x);
		}


		float GetDivGraphSizeYByCutSize(const char*file_name, int div_num_y) {
			return (GetGraphSizeY(file_name) / div_num_y);
		}


		D3DXVECTOR2 GetGraphSizeVec2ByCutSize(const char*file_name, int div_num_x, int div_num_y) {
			return D3DXVECTOR2(
				GetDivGraphSizeXByCutSize(file_name, div_num_x),
				GetDivGraphSizeYByCutSize(file_name, div_num_y));
		}

	}

	void Draw2D(
		const char*file_name,         // ファイル名
		float x,                      // x座標
		float y,					  // y座標
		float scale_width,			  // 横の拡縮
		float scale_height,			  // 縦の拡縮
		float angle,				  // 角度
		float ofset_x,				  // オフセットx(描画頂点をずらす)
		float ofset_y,				  // オフセットy
		bool is_graph_uv_cut,		  // 画像をカットするか
		int u_cut_num,				  // u軸のカット数
		int v_cut_num,				  // v軸のカット数
		int graph_num,				  // カットした画像のどこを使うか
		float u,					  // テクスチャ座標のu軸をずらす
		float v,					  // テクスチャ座標のv軸をずらす
		SamplerStateType type         // サンプラーステートの状態
	)
	{

		// テクスチャデータの参照受け取り
		TextureData *tex_d = &Texture::GetData(file_name);
		// uvの範囲を設定する数
		float u_range_num = 0.f;

		// テクスチャ描画エラー HACK
		//if (Texture::IsTextureRedistr(file_name) == false) {
		//	MessageBoxA(0, "Draw2D...Error/Place...TextureBord2D>Draw2D", TEXT("MessageBoxA"), MB_OK);
		//	return;
		//}

		const float x1 = -ofset_x;
		const float x2 = 1.f - ofset_x;
		const float y1 = -ofset_y;
		const float y2 = 1.f - ofset_y;

		// ロードで読み込んだUVを加算
		u += tex_d->Uv.x;
		v += tex_d->Uv.y;

		// UVの分割
		UV uv(u_cut_num, v_cut_num);

		// uvカットがオンならば
		if (u_cut_num > 0 || v_cut_num > 0) {

			if (type == CLAMP) {
				uv.AnimationToTheRightDivGraph(graph_num);
			}
			else if (type == MIRROR) {
				uv.AnimationToTheLeftDivGraph(graph_num);
			}
		}

		// サンプラーステートの設定
		if (SetSamplerStateSelect(type) == true) {
			u_range_num = 1.f;
		}

		// VERTEX3Dの初期化,UV.hからUVをずらして受け取り
		CustomVertex cv[] =
		{
			// 左上
			{ { x1,y1,0.0f },1.0f,D3DCOLOR(0xfffffff),{ uv.GetUvUpLeftPos().x + u_range_num,uv.GetUvUpLeftPos().y } },
			// 右上
		{ { x2,y1,0.0f },1.0f,D3DCOLOR(0xfffffff),{ uv.GetUvUpRightPos().x + u + u_range_num,uv.GetUvUpRightPos().y } },
		// 右下
		{ { x2,y2,0.0f },1.0f,D3DCOLOR(0xfffffff),{ uv.GetUvDownRightPos().x + u + u_range_num,uv.GetUvDownRightPos().y + v } },
		// 左下
		{ { x1,y2,0.0f },1.0f,D3DCOLOR(0xfffffff),{ uv.GetUvDownLeftPos().x + u_range_num,uv.GetUvDownLeftPos().y + v } },
		};


		// サンプラーステート(描画外は描画しないようにするため,デフォルト)
		//D3D9::GetLpDirect3DDevice9()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		//D3D9::GetLpDirect3DDevice9()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);

		// 行列計算
		D3DXMATRIX mat_world = GetMatrixTransformCalc(x, y, tex_d->Width * scale_width, tex_d->Height * scale_height, angle);

		// 行列を頂点配列に変換
		D3DXVec3TransformCoordArray((D3DXVECTOR3*)cv, sizeof(CustomVertex), (D3DXVECTOR3*)cv, sizeof(CustomVertex), &mat_world, std::size(cv));

		// VERTEX3Dの構造情報をDirectXへ通知。										  
		D3D9::GetLpDirect3DDevice9()->SetFVF(FVF_2D);

		// デバイスにそのまま渡すことができる。
		D3D9::GetLpDirect3DDevice9()->SetTexture(0, Texture::GetData(file_name));// これはテクスチャの指定、ポインタを渡して確認する。

																				 // 図形を元にポリゴン作成
		D3D9::GetLpDirect3DDevice9()->DrawPrimitiveUP(
			D3DPT_TRIANGLEFAN,
			2,
			cv,// cv カスタムバーテックスのポインタ
			sizeof(CustomVertex)
		);
	}
}


D3DXMATRIX GetMatrixTransformCalc(float x, float y, float width_scale, float height_scale, float angle) {

	// ワールド座標変換系
	D3DXMATRIX mat_trans, mat_scale, mat_rotz;

	D3DXMatrixIdentity(&mat_rotz);
	D3DXMatrixIdentity(&mat_trans);
	D3DXMatrixIdentity(&mat_scale);

	D3DXMatrixTranslation(&mat_trans, x, y, 0.f);
	D3DXMatrixScaling(&mat_scale, width_scale, height_scale, 0.0f);
	D3DXMatrixRotationZ(&mat_rotz, D3DXToRadian(angle));

	// 拡縮 * 回転 * 移動
	return (mat_scale * mat_rotz * mat_trans);
}


bool SetSamplerStateSelect(Texture::SamplerStateType type) {

	switch (type) {

	case Texture::CLAMP:

		D3D9::SamplerStateClamp();

		return false;

	case Texture::MIRROR:

		D3D9::SamplerStateUMirror();

		return true;
	}

	return false;
}
