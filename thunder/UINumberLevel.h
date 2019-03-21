#ifndef _UI_NUMBER_LEVEL_H_
#define _UI_NUMBER_LEVEL_H_

#include "UI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define UI_NUMBER_LEVEL_DIGIT			(1)			// 桁数
// 座標
#define  UI_NUMBER_LEVEL_POS_X		(1187.0f)	// ポリゴンの初期位置X
#define  UI_NUMBER_LEVEL_POS_Y		(310.0f)	// 同上
// 情報
#define LEVEL_MAX						(9)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitUINumberLevel(int InitType);
void UninitUINumberLevel(void);
void UpdateUINumberLevel(void);
void DrawUINumberLevel(void);

UINUMBER *GetLevel(void);

#endif
