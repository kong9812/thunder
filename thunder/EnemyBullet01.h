#ifndef _ENEMY_BULLET_01_H_
#define _ENEMY_BULLET_01_H_

#include "main.h"
#include "EnemyBulletManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// BULLET_01画像
#define	TEXTURE_ENEMY_BULLET_01		_T("data/TEXTURE/Enemy01Bullet.png")	// 読み込むテクスチャファイル名
// サイズ
#define ENEMY_BULLET_01_SIZE_X		(30)		// 弾の幅(X)
#define ENEMY_BULLET_01_SIZE_Y		(30)		// 弾の高さ(Y)
// 情報				   
#define ENEMY_BULLET_01_SPEED		(5)			// 発射速度
#define ENEMY_BULLET_01_MAX			(10)		// 画面上同時に描画できる弾の数
#define ENEMY_BULLET_01_ATK			(20)		// 攻撃力

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemyBullet01(int InitType);
void UninitEnemyBullet01(void);
void UpdateEnemyBullet01(void);
void DrawEnemyBullet01(void);

void SetEnemyBullet01(D3DXVECTOR3 EnemyPos);

ENEMYBULLET *GetEnemyBullet01(int no);

#endif