#ifndef _UI_NUMBER_STAGE_H_
#define _UI_NUMBER_STAGE_H_

#include "UI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define UI_NUMBER_STAGE_DIGIT			(1)			// 桁数
// 座標
#define  UI_NUMBER_STAGE_POS_X			(1190.0f)	// ポリゴンの初期位置X
#define  UI_NUMBER_STAGE_POS_Y			(357.0f)		// 同上
// 情報
#define STAGE_MAX						(9)

enum STAGE_NUM
{
	STAGE_0,
	STAGE_1,
	STAGE_2,
	STAGE_3
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitUINumberStage(int InitType);
void UninitUINumberStage(void);
void UpdateUINumberStage(float MapPos);
void DrawUINumberStage(void);

UINUMBER *GetStage(void);

#endif
