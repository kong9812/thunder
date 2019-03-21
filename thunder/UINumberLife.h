#ifndef _UI_NUMBER_LIFE_H_
#define _UI_NUMBER_LIFE_H_

#include "UI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define UI_NUMBER_LIFE_DIGIT			(1)			// 桁数
// 座標
#define  UI_NUMBER_LIFE_POS_X		(1133.0f)	// ポリゴンの初期位置X
#define  UI_NUMBER_LIFE_POS_Y		(157.0f)	// 同上
// 情報
#define LIFE_MAX						(9)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitUINumberLife(int InitType);
void UninitUINumberLife(void);
void UpdateUINumberLife(void);
void DrawUINumberLife(void);

UINUMBER *GetLife(void);

#endif
