#ifndef _TUTORIAL_MANAGER_H_
#define _TUTORIAL_MANAGER_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// コントロール説明
#define	TEXTURE_CONTROL				_T("data/TEXTURE/tutorial_ctrl.png")			// 読み込むテクスチャファイル名
// サイズ		
#define CONTROL_SIZE_X					(300)	// プレイヤーの幅(X)
#define CONTROL_SIZE_Y					(300)	// プレイヤーの高さ(Y)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTutorialManager(int InitType);
void UninitTutorialManager(void);
void UpdateTutorialManager(void);
void DrawTutorialManager(void);

void SetTutorialMapScrollPos(float PosY);

#endif