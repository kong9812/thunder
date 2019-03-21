#ifndef _PLAYER_BOMB_H_
#define _PLAYER_BOMB_H_

#include "main.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 爆発画像
#define	TEXTURE_PLAYER_BOMB		_T("data/TEXTURE/PlayerBomb.png")	// 読み込むテクスチャファイル名
// サイズ
#define PLAYER_BOMB_SIZE_X		(960)		// 弾の幅(X)
#define PLAYER_BOMB_SIZE_Y		(720)		// 弾の高さ(Y)
// アニメーションパターン
#define PLAYER_BOMB_PATTERN_DIVIDE_X	(8)		// アニメパターンのテクスチャ内分割数（X)
#define PLAYER_BOMB_PATTERN_DIVIDE_Y	(2)		// アニメパターンのテクスチャ内分割数（Y)
#define PLAYER_BOMB_ANIM_PATTERN_NUM	(PLAYER_BOMB_PATTERN_DIVIDE_X*PLAYER_BOMB_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define TIME_PLAYER_BOMB_ANIMATION		(4)		// アニメーションの切り替わるカウント
// 情報
#define PLAYER_BOMB_COLOR				D3DCOLOR_RGBA(255, 255, 255, 127)	// 点の状態のα値
#define PLAYER_BOMB_ATK					(10)

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// プレイヤー爆発構造体
{
	D3DXVECTOR3		pos;			// 爆発の座標

	int				CountAnim;	// アニメーションカウンター
	int				PatternAnim;	// アニメーションパターンナンバー

	bool			use;			// true:使用中 false:使用していない

}PLAYERBOMB;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerBomb(int InitType);
void UninitPlayerBomb(void);
void UpdatePlayerBomb(void);
void DrawPlayerBomb(void);

void SetPlayerBomb(void);
PLAYERBOMB *GetPlayerBomb(void);


#endif