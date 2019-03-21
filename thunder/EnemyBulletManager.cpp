#include "main.h"
#include "EnemyBullet01.h"
#include "EnemyBullet02.h"
#include "EnemyBullet03.h"
#include "EnemyBulletManager.h"

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyBulletManager(int InitType)
{
	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{	// 初期化
		InitEnemyBullet01(FIRST_INIT);
		InitEnemyBullet02(FIRST_INIT);
		InitEnemyBullet03(FIRST_INIT);
	}

	else
	{	// 再初期化
		InitEnemyBullet01(RE_INIT);
		InitEnemyBullet02(RE_INIT);
		InitEnemyBullet03(RE_INIT);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyBulletManager(void)
{
	UninitEnemyBullet01();
	UninitEnemyBullet02();
	UninitEnemyBullet03();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyBulletManager(void)
{
	UpdateEnemyBullet01();
	UpdateEnemyBullet02();
	UpdateEnemyBullet03();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyBulletManager(void)
{
	DrawEnemyBullet01();
	DrawEnemyBullet02();
	DrawEnemyBullet03();
}

//=============================================================================
// バレットを設置
//=============================================================================
void SetEnemyBullet(D3DXVECTOR3 EnemyPos, int BulletType)
{
	if (BulletType == ENEMY_BULLET_01)
	{
		SetEnemyBullet01(EnemyPos);
	}

	if (BulletType == ENEMY_BULLET_02)
	{
		SetEnemyBullet02(EnemyPos);
	}

	if (BulletType == ENEMY_BULLET_03)
	{
		SetEnemyBullet03(EnemyPos);
	}

}