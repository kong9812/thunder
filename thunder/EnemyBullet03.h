#ifndef _ENEMY_BULLET_03_H_
#define _ENEMY_BULLET_03_H_

#include "main.h"
#include "EnemyBulletManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// サイズ
#define ENEMY_BULLET_03_SIZE_X		(30)		// 弾の幅(X)
#define ENEMY_BULLET_03_SIZE_Y		(30)		// 弾の高さ(Y)
// 情報				   
#define ENEMY_BULLET_03_SPEED		(3)			// 発射速度
#define ENEMY_BULLET_03_MAX			(50)		// 画面上同時に描画できる弾の数
#define ENEMY_BULLET_03_ATK			(20)		// 攻撃力

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemyBullet03(int InitType);
void UninitEnemyBullet03(void);
void UpdateEnemyBullet03(void);
void DrawEnemyBullet03(void);

void SetEnemyBullet03(D3DXVECTOR3 EnemyPos);

ENEMYBULLET *GetEnemyBullet03(int no);

#endif