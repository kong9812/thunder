#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// UI画像
#define	TEXTURE_UI	_T("data/TEXTURE/UI.png")			// 読み込むテクスチャファイル名
// サイズ
#define RIGHT_UI_SIZE_X		(320)
#define RIGHT_UI_SIZE_Y		(720)
// 座標
#define UI_POS_X			(SCREEN_WIDTH - RIGHT_UI_SIZE_X)
// 数字
#define TEXTURE_UI_NUMBER			_T("data/TEXTURE/UINumber.png")	// サンプル用画像
// サイズ	
#define UI_NUMBER_SIZE_X				(20)		// テクスチャサイズ
#define UI_NUMBER_SIZE_Y				(40)		// 同上
// アニメーションパターン
#define UI_NUMBER_PATTERN_DIVIDE_X		(5)			// アニメパターンのテクスチャ内分割数（X)
#define UI_NUMBER_PATTERN_DIVIDE_Y		(2)			// アニメパターンのテクスチャ内分割数（Y)
#define UI_NUMBER_ANIM_PATTERN_NUM		(UI_NUMBER_PATTERN_DIVIDE_X*UI_NUMBER_PATTERN_DIVIDE_Y)
#define TIME_UI_NUMBER_ANIMATION		(100)		// アニメーションの切り替わるカウント

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// UINumber構造体
{
	D3DXVECTOR3				pos;				// 座標

	int						value;				// 値

}UINUMBER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitUI(int InitType);
void UninitUI(void);
void UpdateUI(float MapPos);
void DrawUI(void);

#endif