#ifndef _ENEMY_03_H_
#define _ENEMY_03_H_

#include "main.h"
#include "EnemyManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// エネミー_03画像
#define	TEXTURE_ENEMY_03			_T("data/TEXTURE/enemy C.png")			// 読み込むテクスチャファイル名
// サイズ		
#define ENEMY_03_SIZE_X					(390)	// エネミーの幅(X)
#define ENEMY_03_SIZE_Y					(226)	// エネミーの高さ(Y)
// エネミー02情報
#define ENEMY_03_HP_MAX					(10000)
#define ENEMY_03_SPEED					(2)
#define ENEMY_03_START_POS_Y				(SCREEN_HEIGHT + ENEMY_03_SIZE_Y / HALF)				
#define ENEMY_03_SPAWN_POS				D3DXVECTOR3(480.0f, -10.0f, 0.0f)	// 初期位置
#define ENEMY_03_STOP_POS_Y				(-3.0f)
#define ENEMY_03_EXP						(10)
#define ENEMY_03_SCORE					(100)
#define ENEMY_03_SHOOT_01_TIME			(20)
#define ENEMY_03_SHOOT_02_TIME			(40)
#define ENEMY_03_SHOOT_03_TIME			(5)
// 点滅用		
#define ENEMY_03_FLASHING_ALPHA_ON		D3DCOLOR_RGBA(255, 255, 255, 255)	// 点の状態のα値
#define ENEMY_03_FLASHING_ALPHA_OFF		D3DCOLOR_RGBA(255, 255, 255, 0)		// 滅の状態のα値
#define ENEMY_03_FLASHING_HOLD_TIME		(5)									// 点/滅の状態時間
#define ENEMY_03_FLASHING_RESET			(ENEMY_03_FLASHING_HOLD_TIME*2)		// 点滅リセット
#define ENEMY_03_FLASHING_MAX			(1)									// 点滅の回数
// 回転		   
#define ENEMY_03_SPIN_Z					(D3DXToRadian(90))					// 回転量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy03(int InitType);
void UninitEnemy03(void);
void UpdateEnemy03(float MapPos);
void DrawEnemy03(void);

ENEMY *GetEnemy03();

#endif