#ifndef _TUTORIAL_UI_H_
#define _TUTORIAL_UI_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// UI背景
#define TEXTURE_TUTORIAL_UI		_T("data/TEXTURE/tutorialUI.png")			// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTutorialUI(int InitType);
void UninitTutorialUI(void);
void UpdateTutorialUI(void);
void DrawTutorialUI(void);

#endif
