#ifndef _PAUSE_MANAGER_H_
#define _PAUSE_MANAGER_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPauseManager(int InitType);
void UninitPauseManager(void);
void UpdatePauseManager(int STAGE);
void DrawPauseManager(int STAGE);

#endif