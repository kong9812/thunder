#ifndef _ENEMY_02_H_
#define _ENEMY_02_H_

#include "main.h"
#include "EnemyManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// エネミー_02画像
#define	TEXTURE_ENEMY_02			_T("data/TEXTURE/enemy B.png")			// 読み込むテクスチャファイル名
// サイズ		
#define ENEMY_02_SIZE_X					(80)	// プレイヤーの幅(X)
#define ENEMY_02_SIZE_Y					(80)	// プレイヤーの高さ(Y)
// エネミー02情報
#define ENEMY_02_HP_MAX					(100)
#define ENEMY_02_SPEED					(2)
#define ENEMY_02_START_POS_Y			(SCREEN_HEIGHT + ENEMY_02_SIZE_Y / HALF)				
#define ENEMY_02_MAX					(1)
#define ENEMY_02L_SPAWN_POS				D3DXVECTOR3(300.0f, -10.0f, 0.0f)	// 初期位置
#define ENEMY_02R_SPAWN_POS				D3DXVECTOR3(580.0f, -10.0f, 0.0f)	// 初期位置
#define ENEMY_02_STOP_POS_Y				(-1.6f)
#define ENEMY_02_STOP_TIME				(250)	// スクリーンに止まる時間
#define ENEMY_02_EXP					(5)
#define ENEMY_02_SCORE					(50)
// 弾発射用
#define ENEMY_02_SHOOT_TIME				(3)	// 発射間隔
// 点滅用
#define ENEMY_02_FLASHING_ALPHA_ON		D3DCOLOR_RGBA(255, 255, 255, 255)	// 点の状態のα値
#define ENEMY_02_FLASHING_ALPHA_OFF		D3DCOLOR_RGBA(255, 255, 255, 0)		// 滅の状態のα値
#define ENEMY_02_FLASHING_HOLD_TIME		(5)									// 点/滅の状態時間
#define ENEMY_02_FLASHING_RESET			(ENEMY_02_FLASHING_HOLD_TIME*2)		// 点滅リセット
#define ENEMY_02_FLASHING_MAX			(1)									// 点滅の回数
// 回転		 
#define ENEMY_02_SPIN_Z					(D3DXToRadian(90))					// 回転量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy02(int InitType);
void UninitEnemy02(void);
void UpdateEnemy02(float MapPos);
void DrawEnemy02(void);

ENEMY *GetEnemy02Left(int no);
ENEMY *GetEnemy02Right(int no);

#endif