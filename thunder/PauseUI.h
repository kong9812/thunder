#ifndef _PAUSE_UI_H_
#define _PAUSE_UI_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ポーズUI画像
#define	TEXTURE_PAUSE_UI		_T("data/TEXTURE/PauseMenu.png")	// 読み込むテクスチャファイル名
// サイズ
#define PAUSE_UI_SIZE_X			(359)	// ポーズUIの幅(X)
#define PAUSE_UI_SIZE_Y			(359)	// ポーズUIの高さ(Y)
// 座標
#define PAUSE_UI_POS_X			(SCREEN_WIDTH/HALF-PAUSE_UI_SIZE_X/HALF)	
#define PAUSE_UI_POS_Y			(SCREEN_HEIGHT/HALF-PAUSE_UI_SIZE_Y/HALF)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPauseUI(int InitType);
void UninitPauseUI(void);
void UpdatePauseUI(void);
void DrawPauseUI(void);

#endif