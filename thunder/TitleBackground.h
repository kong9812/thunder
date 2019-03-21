#ifndef _TITLE_BACKGROUND_H_
#define _TITLE_BACKGROUND_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// タイトル画面(背景)
#define	TEXTURE_TITLE				_T("data/TEXTURE/GameBackground.jpg")	// 読み込むテクスチャファイル名
// 座標
#define TITLE_POS_X					(0.0f)				// タイトル画面(背景)の表示位置(X)
#define TITLE_POS_Y					(0.0f)				// タイトル画面(背景)の表示位置(Y)
#define TITLE_POS_Z					(0.0f)				// タイトル画面(背景)の表示位置(Z)
// サイズ
#define TITLE_SIZE_X				(SCREEN_WIDTH)		// タイトル画面(背景)の幅(X)
#define TITLE_SIZE_Y				(SCREEN_HEIGHT)		// タイトル画面(背景)の高さ(Y)
// スクロール
#define TITLE_SCROLL_SPEED			(0.001f)			// タイトル画面(背景)のスクロール速度

// タイトル画面(壁)
#define	TEXTURE_TITLE_WALL			_T("data/TEXTURE/TekWall.png")	// 読み込むテクスチャファイル名
// 座標
#define TITLE_WALL_POS_X			(0.0f)				// タイトル画面(壁)の表示位置(X)
#define TITLE_WALL_POS_Y			(0.0f)				// タイトル画面(壁)の表示位置(Y)
#define TITLE_WALL_POS_Z			(0.0f)				// タイトル画面(壁)の表示位置(Z)
// サイズ															 
#define TITLE_WALL_SIZE_X			(SCREEN_WIDTH)		// タイトル画面(壁)の幅(X)
#define TITLE_WALL_SIZE_Y			(SCREEN_HEIGHT)		// タイトル画面(壁)の高さ(Y)

// タイトル画面(名前)
#define	TEXTURE_TITLE_NAME			_T("data/TEXTURE/name.png")		// 読み込むテクスチャファイル名
// 座標
#define	TITLE_NAME_POS_X			(398.5f)			// タイトル画面(名前)の表示位置(X)
#define	TITLE_NAME_POS_Y			(70.0f)				// タイトル画面(名前)の表示位置(Y)
#define TITLE_NAME_POS_Z			(0.0f)				// タイトル画面(名前)の表示位置(Z)
// サイズ
#define	TITLE_NAME_SIZE_X			(483.0f)			// タイトル画面(名前)の幅(X)
#define	TITLE_NAME_SIZE_Y			(85.0f)				// タイトル画面(名前)の高さ(Y)
// 反射光
#define	TITLE_NAME_COLOR_RED		D3DCOLOR_RGBA(255,0,0,255)		// タイトル画面(名前)の反射光(赤)
#define	TITLE_NAME_COLOR_BLACK		D3DCOLOR_RGBA(0,0,0,255)		// タイトル画面(名前)の反射光(黒)

// 著作権宣言
#define	TEXTURE_TITLE_COPYRIGHT		_T("data/TEXTURE/copyright.png")// 読み込むテクスチャファイル名
// 座標
#define	TITLE_COPYRIGHT_POS_X			(1083.0f)		// タイトル画面(名前)の表示位置(X)
#define	TITLE_COPYRIGHT_POS_Y			(708.0f)		// タイトル画面(名前)の表示位置(Y)
#define TITLE_COPYRIGHT_POS_Z			(0.0f)			// タイトル画面(名前)の表示位置(Z)
// サイズ											
#define	TITLE_COPYRIGHT_SIZE_X			(197.0f)		// 著作権宣言の幅(X)
#define	TITLE_COPYRIGHT_SIZE_Y			(12.0f)			// 著作権宣言の高さ(Y)

// タイトル画面(ドア/門)
// 門枠
#define	TEXTURE_DOOR_01			_T("data/TEXTURE/TekDoor-1.png")	// 読み込むテクスチャファイル名
// 門
#define	TEXTURE_DOOR_02			_T("data/TEXTURE/TekDoor-2.png")	// 読み込むテクスチャファイル名
// 門
#define	TEXTURE_DOOR_03			_T("data/TEXTURE/TekDoor_3.jpg")	// 読み込むテクスチャファイル名
// 座標
#define DOOR_POS_X					(280.0f)			// タイトル画面(ドア)の表示位置(X)
#define DOOR_POS_Y					(0.0f)				// タイトル画面(ドア)の表示位置(Y)
#define DOOR_POS_Z					(0.0f)				// タイトル画面(ドア)の表示位置(Z)
// サイズ															 
#define DOOR_SIZE_X					(720)				// タイトル画面(ドア)の幅(X)
#define DOOR_SIZE_Y					(720)				// タイトル画面(ドア)の高さ(Y)
// ローテーション	
#define DOOR_SCROLL_SPEED			(0.01f)				// タイトル画面(ドア)のローテーション速度
#define DOOR_SCROLL_MAX				(0.7f)				// タイトル画面(ドア)のローテーション限界
#define	DOOR_MOVIE_Z				(-0.8f)				// タイトル画面(ドア)の初期角度
// 移動
#define DOOR_MOVE_SPEED				(10)				// タイトル画面(ドア)の移動速度
// テクスチャ分割用
#define DOOR_CUT_PATTERN_X			(2)					// テクスチャ内分割数(X)
#define DOOR_CUT_PATTERN_Y			(2)					// テクスチャ内分割数(Y)
#define DOOR_CUT_01_SIZE_X			(0.5f)				// テクスチャの分割のサイズ(X)
#define DOOR_CUT_01_SIZE_Y			(0.5f)				// テクスチャの分割のサイズ(Y)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitleBackground(int InitType);
void UninitTitleBackground(void);
void UpdateTitleBackground(void);
void DrawTitleBackground(bool DrawFlag);

void SetDoorFlag(bool Flag);
void SetTitleSelectStage(int STAGE);

#endif
