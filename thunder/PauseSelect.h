#ifndef _PAUSE_SELECT_H_
#define _PAUSE_SELECT_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ReturnToGame画像
#define	TEXTURE_PAUSE_RETURNTOGAME	_T("data/TEXTURE/ReturnToGame.png")	// 読み込むテクスチャファイル名
// サイズ
#define PAUSE_RETURNTOGAME_SIZE_X	(243)		// ポーズUIの幅(X)
#define PAUSE_RETURNTOGAME_SIZE_Y	(18.75f)	// ポーズUIの高さ(Y)
// 座標
#define PAUSE_RETURNTOGAME_POS_X	(SCREEN_WIDTH/HALF-PAUSE_RETURNTOGAME_SIZE_X/HALF)	
#define PAUSE_RETURNTOGAME_POS_Y	(350)	

// BackToTittle画像
#define	TEXTURE_PAUSE_BACKTOTITTLE	_T("data/TEXTURE/BackToTittle.png")	// 読み込むテクスチャファイル名
// サイズ
#define PAUSE_BACKTOTITTLE_SIZE_X	(243)		// ポーズUIの幅(X)
#define PAUSE_BACKTOTITTLE_SIZE_Y	(18.75f)	// ポーズUIの高さ(Y)
// 座標		
#define PAUSE_BACKTOTITTLE_POS_X	(SCREEN_WIDTH/HALF-PAUSE_BACKTOTITTLE_SIZE_X/HALF)	
#define PAUSE_BACKTOTITTLE_POS_Y	(390)	

// QuitGame画像
#define	TEXTURE_PAUSE_QUITGAME		_T("data/TEXTURE/QuitGame.png")	// 読み込むテクスチャファイル名
// サイズ
#define PAUSE_QUITGAME_SIZE_X		(108)		// ポーズUIの幅(X)
#define PAUSE_QUITGAME_SIZE_Y		(18.75f)	// ポーズUIの高さ(Y)
// 座標		
#define PAUSE_QUITGAME_POS_X		(SCREEN_WIDTH/HALF-PAUSE_QUITGAME_SIZE_X/HALF)	
#define PAUSE_QUITGAME_POS_Y		(430)	


#define PAUSE_SELECT_RGBA			D3DCOLOR_RGBA(0,0,0,255)		// 選択された状態の色

#define PAUSE_NTSELECT_RGBA			D3DCOLOR_RGBA(255,255,255,255)	// 選択されてない状態の色



//*****************************************************************************
// 定数定義(enum定義)
//*****************************************************************************
enum PAUSE_SELECT		// タイトルの選択定数
{
	PAUSE_RETURN_TO_GAME,
	PAUSE_BACK_TO_TITLE,
	PAUSE_QUIT_GAME
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPauseSelect(int InitType);
void UninitPauseSelect(void);
void UpdatePauseSelect(int STAGE);
void DrawPauseSelect(void);

#endif