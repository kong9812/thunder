#ifndef _PLAYER_BULLET_MANAGER_H_
#define _PLAYER_BULLET_MANAGER_H_

#include "main.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 情報
#define PLAYER_BULLET_SHOOT_TIME		(10)		// 発射間隔

//*****************************************************************************
// 定数定義(enum定義)
//*****************************************************************************
enum E_PLAYERBULLET		// プレイヤーバレット定数
{
	PLAYER_BULLET_01,
	PLAYER_BULLET_02,
	PLAYER_BULLET_03,
	PLAYER_BULLET_04
};

enum E_PLAYERBULLET_POS	// プレイヤーバレット位置定数
{
	PLAYER_BULLET_LEFT,
	PLAYER_BULLET_RIGHT,
	PLAYER_BULLET_MID
};

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// プレイヤーバレット構造体
{
	D3DXVECTOR3		pos;			// バレットの座標

	int				type;			// バレット型

	bool			use;			// true:使用中 false:使用していない
}PLAYERBULLET;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerBulletManager(int InitType);
void UninitPlayerBulletManager(void);
void UpdatePlayerBulletManager(void);
void DrawPlayerBulletManager(void);

void SetPlayerBullet(D3DXVECTOR3 PlayerPos, int BulletPos);
#endif