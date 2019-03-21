#ifndef _PLAYER_BULLET_03_H_
#define _PLAYER_BULLET_03_H_

#include "main.h"
#include "PlayerBulletManager.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// サイズ
#define PLAYER_BULLET_03_SIZE_X			(10)		// 弾の幅(X)
#define PLAYER_BULLET_03_SIZE_Y			(24)		// 弾の高さ(Y)
// 情報
#define PLAYER_BULLET_03_SPEED			(20)		// 発射速度
#define PLAYER_BULLET_03_MAX			(50)		// 画面上同時に描画できる弾の数
#define PLAYER_BULLET_03_ATK			(10)		// 攻撃力
// 微調整				
#define PLAYER_BULLET_03_PLAYER_LEFT	(PLAYER_SIZE_X*0.25f+PLAYER_BULLET_03_SIZE_X/HALF)	// プレイヤーと誤差
#define PLAYER_BULLET_03_PLAYER_RIGHT	(PLAYER_SIZE_X*0.75f-PLAYER_BULLET_03_SIZE_X/HALF)	// プレイヤーと誤差
#define PLAYER_BULLET_03_PLAYER_MID		(PLAYER_SIZE_X*0.55f-PLAYER_BULLET_03_SIZE_X/HALF)	// プレイヤーと誤差

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerBullet03(int InitType);
void UninitPlayerBullet03(void);
void UpdatePlayerBullet03(void);
void DrawPlayerBullet03(void);

void SetPlayerBullet03(D3DXVECTOR3 PlayerPos, int BulletPos);

PLAYERBULLET *GetPlayerBullet03(int no);


#endif