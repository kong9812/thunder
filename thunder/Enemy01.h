#ifndef _ENEMY_01_H_
#define _ENEMY_01_H_

#include "main.h"
#include "EnemyManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// エネミー_01画像
#define	TEXTURE_ENEMY_01			_T("data/TEXTURE/enemy A.png")			// 読み込むテクスチャファイル名
// サイズ		
#define ENEMY_01_SIZE_X					(80)	// プレイヤーの幅(X)
#define ENEMY_01_SIZE_Y					(80)	// プレイヤーの高さ(Y)
// エネミー01情報
#define ENEMY_01_HP_MAX					(10)
#define ENEMY_01_SPEED					(2)
#define ENEMY_01_START_POS_Y			(SCREEN_HEIGHT + ENEMY_01_SIZE_Y / HALF)				
#define ENEMY_01_MAX					(10)
#define ENEMY_01L_SPAWN_POS				D3DXVECTOR3(300.0f, -10.0f, 0.0f)	// 初期位置
#define ENEMY_01R_SPAWN_POS				D3DXVECTOR3(580.0f, -10.0f, 0.0f)	// 初期位置
#define ENEMY_01_STOP_POS_Y				(-0.2f)
#define ENEMY_01_STOP_TIME				(200)	// スクリーンに止まる時間
#define ENEMY_01_SHOOT_TIME				(20)	// 発射間隔
#define ENEMY_01_EXP					(1)
#define ENEMY_01_SCORE					(10)
// 点滅用
#define ENEMY_01_FLASHING_ALPHA_ON		D3DCOLOR_RGBA(255, 255, 255, 255)	// 点の状態のα値
#define ENEMY_01_FLASHING_ALPHA_OFF		D3DCOLOR_RGBA(255, 255, 255, 0)		// 滅の状態のα値
#define ENEMY_01_FLASHING_HOLD_TIME		(5)									// 点/滅の状態時間
#define ENEMY_01_FLASHING_RESET			(ENEMY_01_FLASHING_HOLD_TIME*2)		// 点滅リセット
#define ENEMY_01_FLASHING_MAX			(1)									// 点滅の回数
 // 回転
#define ENEMY_01_SPIN_Z					(0.01f)								// 回転量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy01(int InitType);
void UninitEnemy01(void);
void UpdateEnemy01(float MapPos);
void DrawEnemy01(void);

ENEMY *GetEnemy01Left(int no);
ENEMY *GetEnemy01Right(int no);

#endif