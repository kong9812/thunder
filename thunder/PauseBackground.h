#ifndef _PAUSE_BACKGROUND_H_
#define _PAUSE_BACKGROUND_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ポーズ背景
// 反射光
#define	TITLE_NAME_COLOR_GRAY		D3DCOLOR_RGBA(128,128,128,128)		// ポーズ画面の反射光(灰)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPauseBackground(int InitType);
void UninitPauseBackground(void);
void UpdatePauseBackground(void);
void DrawPauseBackground(void);

#endif