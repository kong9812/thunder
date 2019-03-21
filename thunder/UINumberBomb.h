#ifndef _UI_NUMBER_BOMB_H_
#define _UI_NUMBER_BOMB_H_

#include "UI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define UI_NUMBER_BOMB_DIGIT			(1)			// 桁数
// 座標
#define  UI_NUMBER_BOMB_POS_X		(1178.0f)	// ポリゴンの初期位置X
#define  UI_NUMBER_BOMB_POS_Y		(207.0f)	// 同上
// 情報
#define BOMB_MAX						(9)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitUINumberBomb(int InitType);
void UninitUINumberBomb(void);
void UpdateUINumberBomb(void);
void DrawUINumberBomb(void);

UINUMBER *GetBomb(void);

#endif
