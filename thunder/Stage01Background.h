#ifndef _STAGE_01_BACKGROUND_H_
#define _STAGE_01_BACKGROUND_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// STAGE_01背景_01									
// 背景情報
#define	STAGE_01_BACKGROUND_01_SCROLL_SPEED	(0.001f)	// スクロールスピード

// STAGE_01背景_02
// 背景画像
#define TEXTURT_STAGE_01_BACKGROUND_02		_T("data/TEXTURE/Stage01Background.png")	// 読み込むテクスチャファイル名
// サイズ											 
#define STAGE_01_BACKGROUND_02_SIZE_X		(960)		// 背景の幅(X)
#define STAGE_01_BACKGROUND_02_SIZE_Y		(760)		// 背景の高さ(Y)
// 背景情報
#define	STAGE_01_BACKGROUND_02_SCROLL_SPEED	(0.002f)	// スクロールスピード

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitStage01Background(int InitType);
void UninitStage01Background(void);
void UpdateStage01Background(void);
void DrawStage01Background(void);

#endif