#ifndef ___TITLESELECT_H___
#define ___TITLESELECT_H___

//*****************************************************************************
//マクロ定義
//*****************************************************************************
// タイトルの選択肢(スタート)		
#define	TEXTURE_START_LOGO			_T("data/TEXTURE/start.png")	// 読み込むテクスチャファイル名
// 座標
#define START_LOGO_POS_X		(532.5f)		// スタートロゴの表示位置(X)
#define	START_LOGO_POS_Y		(360.0f)		// スタートロゴの表示位置(Y)
#define	START_LOGO_POS_Z		(0.0f)			// スタートロゴの表示位置(Z)
// サイズ
#define	START_LOGO_SIZE_X		(215.0f)		// スタートロゴの幅(X)
#define	START_LOGO_SIZE_Y		(53.0f)			// スタートロゴの高さ(Y)

// タイトルの選択肢(チュートリアル)
#define	TEXTURE_TUTORIAL_LOGO		_T("data/TEXTURE/tutorial.png")		// 読み込むテクスチャファイル名
// 座標
#define	TUTORIAL_LOGO_POS_X		(479.5f)		// チュートリアルロゴの表示位置(X)
#define	TUTORIAL_LOGO_POS_Y		(440.0f)		// チュートリアルロゴの表示位置(Y)
#define	TUTORIAL_LOGO_POS_Z		(0.0f)			// チュートリアルロゴの表示位置(Z)
// サイズ											
#define	TUTORIAL_LOGO_SIZE_X	(321.0f)		// チュートリアルロゴの幅(X)
#define	TUTORIAL_LOGO_SIZE_Y	(53.0f)			// チュートリアルロゴの高さ(Y)

// タイトルの選択肢(コンフィグ)
#define	TEXTURE_CONFIG_LOGO		_T("data/TEXTURE/config.png")		// 読み込むテクスチャファイル名
// 座標
#define	CONFIG_LOGO_POS_X		(529.0f)		// コンフィグロゴの表示位置(X)
#define	CONFIG_LOGO_POS_Y		(520.0f)		// コンフィグロゴの表示位置(Y)
#define	CONFIG_LOGO_POS_Z		(0.0f)			// コンフィグロゴの表示位置(Z)
// サイズ											
#define	CONFIG_LOGO_SIZE_X		(222.0f)		// コンフィグロゴの幅(X)
#define	CONFIG_LOGO_SIZE_Y		(53.0f)			// コンフィグロゴの高さ(Y)

// タイトルの選択肢(エンド)
#define	TEXTURE_END_LOGO			_T("data/TEXTURE/end.png")		// 読み込むテクスチャファイル名
// 座標
#define	END_LOGO_POS_X			(576.5f)		// エンドロゴの表示位置(X)
#define	END_LOGO_POS_Y			(600.0f)		// エンドロゴの表示位置(Y)
#define	END_LOGO_POS_Z			(0.0f)			// エンドロゴの表示位置(Z)
// サイズ
#define	END_LOGO_SIZE_X			(127.0f)		// エンドロゴの幅(X)
#define	END_LOGO_SIZE_Y			(53.0f)			// エンドロゴの高さ(Y)

// タイトルの選択肢(矢印→)
#define	TEXTURE_SELECT_LOGO_LEFT	_T("data/TEXTURE/title_select_left.png")	// 読み込むテクスチャファイル名
// タイトルの選択肢(矢印←)
#define	TEXTURE_SELECT_LOGO_RIGHT	_T("data/TEXTURE/title_select_right.png")	// 読み込むテクスチャファイル名
// 座標
#define	SELECT_INTERVAL			(100.0f)		// 矢印と選択肢の間隔(X)
// サイズ
#define	SELECT_LOGO_SIZE_X		(55.42f)		// 矢印の幅(X)
#define	SELECT_LOGO_SIZE_Y		(53.86f)		// 矢印の高さ(Y)
// 反射光
#define	TITLE_SELECT_COLOR_RED	D3DCOLOR_RGBA(255,0,0,255)	// タイトル画面(名前)の反射光(赤)


// 点滅用
#define SELECT_FLASHING_ALPHA_ON		D3DCOLOR_RGBA(255, 255, 255, 255)	// 点の状態のα値
#define SELECT_FLASHING_ALPHA_OFF		D3DCOLOR_RGBA(255, 255, 255, 0)		// 滅の状態のα値
#define SELECT_FLASHING_HOLD_TIME		(10)								// 点/滅の状態時間
#define SELECT_FLASHING_RESET			(SELECT_FLASHING_HOLD_TIME*2)		// 点滅リセット

//*****************************************************************************
// 定数定義(enum定義)
//*****************************************************************************
enum TITLE_SELECT		// タイトルの選択定数
{
	TITLE_START,
	TITLE_TUTORIAL,
	TITLE_CONFIG,
	TITLE_END
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitleSelect(int InitType);
void UninitTitleSelect(void);
void UpdateTitleSelect(void);
void DrawTitleSelect(void);

#endif