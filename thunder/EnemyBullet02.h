#ifndef _ENEMY_BULLET_02_H_
#define _ENEMY_BULLET_02_H_

#include "main.h"
#include "EnemyBulletManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// サイズ
#define ENEMY_BULLET_02_SIZE_X		(30)		// 弾の幅(X)
#define ENEMY_BULLET_02_SIZE_Y		(30)		// 弾の高さ(Y)
// 情報				   
#define ENEMY_BULLET_02_SPEED		(3)			// 発射速度
#define ENEMY_BULLET_02_MAX			(50)		// 画面上同時に描画できる弾の数
#define ENEMY_BULLET_02_ATK			(20)		// 攻撃力

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemyBullet02(int InitType);
void UninitEnemyBullet02(void);
void UpdateEnemyBullet02(void);
void DrawEnemyBullet02(void);

void SetEnemyBullet02(D3DXVECTOR3 EnemyPos);

ENEMYBULLET *GetEnemyBullet02(int no);

#endif