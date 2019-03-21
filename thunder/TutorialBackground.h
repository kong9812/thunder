#ifndef _TUTORIAL_BACKGROUND_MANAGER_H_
#define _TUTORIAL_BACKGROUND_MANAGER_H_

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTutorialBackground(int InitType);
void UninitTutorialBackground(void);
void UpdateTutorialBackground(void);
void DrawTutorialBackground(void);

#endif