#ifndef _ENEMY_BULLET_MANAGER_H_
#define _ENEMY_BULLET_MANAGER_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 情報
#define PLAYER_BULLET_SHOOT_TIME		(10)		// 発射間隔

//*****************************************************************************
// 定数定義(enum定義)
//*****************************************************************************
enum E_ENEMYBULLET		// エネミーバレット定数
{
	ENEMY_BULLET_01,
	ENEMY_BULLET_02,
	ENEMY_BULLET_03,
	ENEMY_BULLET_04
};

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// プレイヤーバレット構造体
{
	D3DXVECTOR3		pos;			// バレットの座標

	int				type;			// バレット型

	float			ShotAngle;		// 発射角度

	bool			use;			// true:使用中 false:使用していない

}ENEMYBULLET;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemyBulletManager(int InitType);
void UninitEnemyBulletManager(void);
void UpdateEnemyBulletManager(void);
void DrawEnemyBulletManager(void);

void SetEnemyBullet(D3DXVECTOR3 EnemyPos, int BulletType);
#endif