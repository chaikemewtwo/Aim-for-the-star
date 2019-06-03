#include"../D3D/D3D9.h"
#include"../Texture/TextureBoad2D.h"
#include"./Texture.h"
#include"../UV/UV.h"


struct CUSTOM_VERTEX
{
	// 頂点座標
	float x;
	float y;
	float z;
	// 除算数
	float rhw;
	// テクスチャ座標
	float tu;
	float tv;
};



namespace Texture {


	// 描画関係
	void Draw2DGraph(const char*file_name, const float&pos_x, const float&pos_y) {
		Draw2D(file_name, pos_x, pos_y);
	}

	void Draw2DTransGraph(const char*file_name, const float&pos_x, const float&pos_y,const float &scale_x,const float&scale_y,const float&angle) {
		Draw2D(file_name, pos_x, pos_x, pos_y, scale_x, scale_y, angle);
	}

	void Draw2DRotaGraph(const char*file_name, const float&pos_x, const float &pos_y, const float&angle) {
		Draw2D(file_name, pos_x, pos_y, 1.f, 1.f, angle, 0.5f, 0.5f);
	}

	void Draw2DAnimationGraph(const char*file_name, const float&pos_x, const float&pos_y, const int &u_cut_num, const int&v_cut_num,const int&anim_num) {
		Draw2D(file_name, pos_x, pos_y, 1.f, 1.f, 0.f, 0.f, 0.f, true, u_cut_num, v_cut_num, anim_num);
	}

	void Draw2DRotaAnimation(const char*file_name, const float&pos_x, const float&pos_y, const float &angle, const int &u_cut_num, const int&v_cut_num, const int&anim_num) {
		Draw2D(file_name, pos_x, pos_y, 1.f, 1.f, angle, 0.f, 0.f, true, u_cut_num, v_cut_num, anim_num);
	}

	void Draw2DUVShift(const char*file_name, const float &pos_x, const float &pos_y, const float&shift_u, const float&shift_v) {
		Draw2D(file_name, pos_x, pos_y, 1.f, 1.f, 0.f, 0.f, 0.f, false,0,0,0,shift_u,shift_v);
	}

	namespace Size {
		// サイズ取得関数
		float GetGraphSizeX(const char*file_name) {
			TEXTURE_DATA *tex_d = &tex_list[file_name];
			return tex_d->Width;
		}
		float GetGraphSizeY(const char*file_name) {
			TEXTURE_DATA *tex_d = &tex_list[file_name];
			return tex_d->Height;
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
		float scale_w,				  // 横の拡縮
		float scale_h,				  // 縦の拡縮
		float angle,				  // 角度
		float cx,					  // オフセットx(描画頂点をずらす)
		float cy,					  // オフセットy
		bool is_graph_uv_cut,		  // 画像をカットするか
		int u_cut_num,				  // u軸のカット数
		int v_cut_num,				  // v軸のカット数
		int graph_num,				  // カットした画像のどこを使うか
		float u,					  // テクスチャ座標のu軸をずらす
		float v)					  // テクスチャ座標のv軸をずらす 
	{ 

		TEXTURE_DATA *tex_d = &tex_list[file_name];

		const float x1 = -cx;
		const float x2 = 1.f - cx;
		const float y1 = -cy;
		const float y2 = 1.f - cy;

		// ロードで読み込んだUVを加算
		u += tex_d->Uv.x;
		v += tex_d->Uv.y;

		// UVの分割
		UV uv(u_cut_num, v_cut_num);

		// uvカットがオンならば
		if (is_graph_uv_cut == true) {
			uv.ToTheRightDivGraph(graph_num);
		}

		// 頂点バッファを参照で受け取り
		D3DXVECTOR2 *up_left = &uv.GetUvUpLeftBuffer();
		D3DXVECTOR2 *up_right = &uv.GetUvUpRightBuffer();
		D3DXVECTOR2 *down_left = &uv.GetUvDownLeftBuffer();
		D3DXVECTOR2 *down_right = &uv.GetUvDownRightBuffer();


		// VERTEX3Dの初期化
		CUSTOM_VERTEX cv[] =
		{
			{ x1,y1,0.0f,1.0f,up_left->x,up_left->y },              // 左上
		{ x2,y1,0.0f,1.0f,up_right->x + u,up_right->y },         // 右上
		{ x2,y2,0.0f,1.0f,down_right->x + u,down_right->y + v }, // 右下
		{ x1,y2,0.0f,1.0f,down_left->x,down_left->y + v },       // 左下
		};

		// サンプラーステート(描画外は描画しないようにするため,デフォルト)
		dev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		dev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

		// ワールド座標変換系
		D3DXMATRIX mat_world, mat_trans, mat_scale;
		// ワールド変換回転。
		D3DXMATRIX mat_rotz;

		D3DXMatrixIdentity(&mat_world);
		D3DXMatrixIdentity(&mat_rotz);
		D3DXMatrixIdentity(&mat_trans);
		D3DXMatrixIdentity(&mat_scale);

		D3DXMatrixTranslation(&mat_trans, x, y, 0.f);
		D3DXMatrixScaling(&mat_scale, tex_d->Width * scale_w, tex_d->Height * scale_h, 0.0f);
		D3DXMatrixRotationZ(&mat_rotz, D3DXToRadian(angle));

		// 拡縮 * 回転 * 移動
		mat_world = mat_scale * mat_rotz * mat_trans;

		D3DXVec3TransformCoordArray((D3DXVECTOR3*)cv, sizeof(CUSTOM_VERTEX), (D3DXVECTOR3*)cv, sizeof(CUSTOM_VERTEX), &mat_world, std::size(cv));

		// VERTEX3Dの構造情報をDirectXへ通知。										  
		dev->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

		// デバイスにそのまま渡すことができる。
		dev->SetTexture(0, tex_list[file_name]);// これはテクスチャの指定、ポインタを渡して確認する。
												// 元はtex_list[file_name]	// 0はテクスチャステージ番号

		dev->DrawPrimitiveUP(
			D3DPT_TRIANGLEFAN,
			2,
			cv,// cv カスタムバーテックスのポインタ
			sizeof(CUSTOM_VERTEX)
		);
	}

}

// HACK リファクタ中
void SamplerStateConfig(D3DSAMPLERSTATETYPE state_type) {

	// サンプラーステート(描画外は描画しないようにするため,デフォルト)
	dev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	dev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
}
