#ifndef _UI_NUMBER_EXP_H_
#define _UI_NUMBER_EXP_H_

#include "UI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define UI_NUMBER_EXP_DIGIT			(1)			// 桁数
// 座標
#define  UI_NUMBER_EXP_POS_X		(1133.0f)	// ポリゴンの初期位置X
#define  UI_NUMBER_EXP_POS_Y		(257.0f)	// 同上
// 情報
#define EXP_MAX						(9)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitUINumberExp(int InitType);
void UninitUINumberExp(void);
void UpdateUINumberExp(void);
void DrawUINumberExp(void);

UINUMBER *GetExp(void);

#endif
