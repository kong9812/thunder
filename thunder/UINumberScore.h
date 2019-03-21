#ifndef _UI_NUMBER_SCORE_H_
#define _UI_NUMBER_SCORE_H_

#include "UI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define UI_NUMBER_SCORE_DIGIT			(5)			// 桁数
// 座標
#define  UI_NUMBER_SCORE_POS_X			(1100.0f)	// ポリゴンの初期位置X
#define  UI_NUMBER_SCORE_POS_Y			(100.0f)	// 同上
// 情報
#define SCORE_MAX						(99999)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitUINumberScore(int InitType);
void UninitUINumberScore(void);
void UpdateUINumberScore(void);
void DrawUINumberScore(void);

UINUMBER *GetScore(void);

void AddScore(int value);


#endif
