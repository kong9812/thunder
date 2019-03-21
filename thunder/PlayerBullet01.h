#ifndef _PLAYER_BULLET_01_H_
#define _PLAYER_BULLET_01_H_
						
#include "main.h"
#include "PlayerBulletManager.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// BULLET_01画像
#define	TEXTURE_PLAYER_BULLET_01		_T("data/TEXTURE/PlayerBullet02.png")	// 読み込むテクスチャファイル名
// サイズ
#define PLAYER_BULLET_01_SIZE_X			(10)		// 弾の幅(X)
#define PLAYER_BULLET_01_SIZE_Y			(24)		// 弾の高さ(Y)
// 情報				   
#define PLAYER_BULLET_01_SPEED			(20)		// 発射速度
#define PLAYER_BULLET_01_MAX			(50)		// 画面上同時に描画できる弾の数
#define PLAYER_BULLET_01_ATK			(20)		// 攻撃力
// 微調整				
#define PLAYER_BULLET_01_PLAYER_MID		((PLAYER_SIZE_X*0.55f)-(PLAYER_BULLET_01_SIZE_X/HALF))	// プレイヤーと誤差

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerBullet01(int InitType);
void UninitPlayerBullet01(void);
void UpdatePlayerBullet01(void);
void DrawPlayerBullet01(void);

void SetPlayerBullet01(D3DXVECTOR3 PlayerPos, int BulletPos);

PLAYERBULLET *GetPlayerBullet01(int no);

#endif