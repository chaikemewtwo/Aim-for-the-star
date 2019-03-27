#include"TextureBord2DEX.h"
#include"TextureBoad2D.h"


// 構造体は状態を持つ
struct TextureBord2DEX {

	TextureBord2DEX();

	// テンプレート初期化関数
	void Init();

	const char*file_name;   // ファイル名
	D3DXVECTOR2 pos;		// 位置
	D3DXVECTOR2 scale;	    // 拡縮
	float angle;			// 回転
	D3DXVECTOR2 ofset;	    // センター位置(どこから描画するか)
	bool uv_cut;			// UVカットするか(する=TRUE)
	int u_x;				// 横のUVで切り取る数
	int u_y;				// 縦のUVで切り取る数
	int animation_num;	    // アニメーションナンバー
};

void TextureBord2DEX::Init() {

	file_name = NULL;
	pos.x = pos.y = 0.f;
	scale.x = scale.y = 1.f;
	angle = 0.f;
	ofset.x = ofset.y = 0.f;
	uv_cut = false;
	u_x = 0;
	u_y = 0;
	animation_num = 0;
}

TextureBord2DEX::TextureBord2DEX() {
	Init();
}


namespace Texture {

	// テクスチャ情報を取り入れるクラス
	TextureBord2DEX tb;


	// ファイル名
	void SetFileNameEX(const char*file_name) {
		tb.file_name = file_name;
	}
	void SetFileNameEX(std::string &file_name) {
		SetFileNameEX(file_name.c_str());
	}

	// 位置
	void SetPostionEX(const float&pos_x, const float&pos_y) {
		tb.pos.x = pos_x;
		tb.pos.y = pos_y;
	}

	// 拡縮
	void SetScaleEX(const float&scale_x, const float&scale_y) {
		tb.scale.x = scale_x;
		tb.scale.y = scale_y;
	}

	// 回転
	void SetAngleEX(const float&angle) {
		tb.angle = angle;
	}

	// オフセット値
	void SetOfset(const float&cx, const float&cy) {
		tb.ofset.x = cx;
		tb.ofset.y = cy;
	}

	// UV設定
	void SetUV(const int&u_cut_num, const int&v_cut_num, const bool&is_uv) {
		tb.u_x = u_cut_num;
		tb.u_y = v_cut_num;
		tb.uv_cut = is_uv;
	}

	// アニメーションナンバーを決める
	void SetAnimation(const int&animation_num) {
		tb.animation_num = animation_num;
	}

	// Templateで見やすく設定する
	void SetDraw2DTemplate1(const char*file_name,const float&pos_x,const float&pos_y) {
		SetFileNameEX(file_name);
		SetPostionEX(pos_x, pos_y);
	}

	template<typename T>

	//void SetDraw2DTemplate2(T &obj1,T&obj2,T&obj3,T&obj4,T&obj5){
	//	
	//	T index[5] = { obj1,obj2,obj3,obj4,obj5 };
	//
	//	for (int i = 0; i < 5; i++) {
	//
	//		if (index[i] == tb.file_name) {
	//			tb.file_name = index[i];
	//		}
	//
	//	}
	//}


	// 回転拡縮移動を設定する関数
	void SetTransformEX(const float&pos_x, const float&pos_y, const float&scale_x, const float&scale_y, const float&angle) {
		SetPostionEX(pos_x, pos_y);
		SetScaleEX(scale_x, scale_y);
		SetAngleEX(angle);
	}

	// 描画して初期化一旦初期化しないバージョン
	void Draw2DGraphEXAfterNoInit() {

		// 描画
		Draw2D(tb.file_name,
			tb.pos.x,tb.pos.y,
			tb.scale.x,tb.scale.y,
			tb.angle,
			tb.ofset.x, tb.ofset.y,
			tb.uv_cut,
			tb.u_x, tb.u_y,
			tb.animation_num);
	}

	// 描画して一旦初期化するバージョン
	void Draw2DGraphEX() {

		Draw2DGraphEXAfterNoInit();

		// 描画したあと一旦初期化
		tb.Init();
	}

	void Clear() {
		tb.Init();
	}
}





/*
// 通常設定
void TextureBord2DEX::SetNormalConfig(const char*file_name, const float&pos_x, const float &pos_y) {

	m_file_name = file_name;
	m_pos.x = pos_x;
	m_pos.y = pos_y;
}

// 移動回転拡縮
void TextureBord2DEX::SetTransform(const D3DXVECTOR2&pos, const D3DXVECTOR2&scale, const float&angle) {
	m_pos = pos;
	m_scale = scale;
	m_angle = angle;
}
void TextureBord2DEX::SetTransform
   (const float & pos_x, const float & pos_y,
	const float & scale_x, const float & scale_y,
	const float & angle) {
	m_pos.x = pos_x;
	m_pos.y = pos_y;
	m_scale.x = scale_x;
	m_scale.y = scale_y;
	m_angle = angle;
}


// ファイル名
void TextureBord2DEX::SetFileName(const char*file_name) {
	m_file_name = file_name;
}
void TextureBord2DEX::SetFileName(const std::string &file_name) {
	m_file_name = file_name.c_str();
}

// 位置
void TextureBord2DEX::SetPostion(const D3DXVECTOR2&pos) {
	m_pos = pos;
}
void TextureBord2DEX::SetPostion(const float&pos_x, const float&pos_y) {
	m_pos.x = pos_x;
	m_pos.y = pos_y;
}

// 拡縮
void TextureBord2DEX::SetScale(const D3DXVECTOR2&scale) {
	m_scale = scale;
}
void TextureBord2DEX::SetScale(const float&scale_x, const float&scale_y) {
	m_scale.x = scale_x;
	m_scale.y = scale_y;
}

// 回転
void TextureBord2DEX::SetAngle(const float &angle) {
	m_angle = angle;
}

void TextureBord2DEX::SetOfSetPos(const D3DXVECTOR2&ofset) {
	m_ofset = ofset;
}


void DrawUpdate() {

}*/