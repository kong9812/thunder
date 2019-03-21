#ifndef _PLAYER_BULLET_02_H_
#define _PLAYER_BULLET_02_H_

#include "main.h"
#include "PlayerBulletManager.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// サイズ
#define PLAYER_BULLET_02_SIZE_X			(10)		// 弾の幅(X)
#define PLAYER_BULLET_02_SIZE_Y			(24)		// 弾の高さ(Y)
// 情報				 
#define PLAYER_BULLET_02_SPEED			(20)		// 発射速度
#define PLAYER_BULLET_02_MAX			(50)		// 画面上同時に描画できる弾の数
#define PLAYER_BULLET_02_ATK			(10)		// 攻撃力
// 微調整				
#define PLAYER_BULLET_02_PLAYER_LEFT	(PLAYER_SIZE_X*0.5-PLAYER_BULLET_02_SIZE_X/HALF)	// プレイヤーと誤差
#define PLAYER_BULLET_02_PLAYER_RIGHT	(PLAYER_SIZE_X*0.5+PLAYER_BULLET_02_SIZE_X/HALF)	// プレイヤーと誤差

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerBullet02(int InitType);
void UninitPlayerBullet02(void);
void UpdatePlayerBullet02(void);
void DrawPlayerBullet02(void);

void SetPlayerBullet02(D3DXVECTOR3 PlayerPos, int BulletPos);

PLAYERBULLET *GetPlayerBullet02(int no);

#endif