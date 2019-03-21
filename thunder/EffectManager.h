#ifndef _EFFECT_MANAGER_H_
#define _EFFECT_MANAGER_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// EFFECT_01画像
#define	TEXTURE_EFFECT_01		_T("data/TEXTURE/HitEffect.png")	// 読み込むテクスチャファイル名
// サイズ
#define EFFECT_01_SIZE_X			(50)	// 弾の幅(X)
#define EFFECT_01_SIZE_Y			(50)	// 弾の高さ(Y)
// アニメーションパターン
#define EFFECT_01_PATTERN_DIVIDE_X	(8)		// アニメパターンのテクスチャ内分割数（X)
#define EFFECT_01_PATTERN_DIVIDE_Y	(2)		// アニメパターンのテクスチャ内分割数（Y)
#define EFFECT_01_ANIM_PATTERN_NUM	(EFFECT_01_PATTERN_DIVIDE_X*EFFECT_01_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define TIME_EFFECT_01_ANIMATION	(2)		// アニメーションの切り替わるカウント
// 情報	
#define EFFECT_01_MAX				(50)	// 画面上同時に描画できる弾の数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// エフェクト構造体
{
	D3DXVECTOR3		pos;			// エフェクトの座標

	int				CountAnim;		// アニメーションカウンター
	int				PatternAnim;	// アニメーションパターンナンバー

	bool			use;			// true:使用中 false:使用していない

}EFFECT;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffectManager(int InitType);
void UninitEffectManager(void);
void UpdateEffectManager(void);
void DrawEffectManager(void);

void SetEffect01(D3DXVECTOR3 pos);

EFFECT *GetEffect01(int no);
#endif