#ifndef _TITLEMANAGER_H_
#define _TITLEMANAGER_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTitleManager(int InitType);
void UninitTitleManager(void);
void UpdateTitleManager(void);
void DrawTitleManager(void);

void SetTitleManagerDrowFalg(bool Flag);

#endif