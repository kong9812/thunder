#include "main.h"
#include "Enemy01.h"
#include "Enemy02.h"
#include "Enemy03.h"
#include "EnemyManager.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyManager(int InitType)
{
	if (InitType == FIRST_INIT)
	{
		InitEnemy01(FIRST_INIT);
		InitEnemy02(FIRST_INIT);
		InitEnemy03(FIRST_INIT);
	}

	else
	{
		InitEnemy01(RE_INIT);
		InitEnemy02(RE_INIT);
		InitEnemy03(RE_INIT);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyManager(void)
{
	UninitEnemy01();
	UninitEnemy02();
	UninitEnemy03();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyManager(float MapPos)
{
	UpdateEnemy01(MapPos);
	UpdateEnemy02(MapPos);
	UpdateEnemy03(MapPos);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyManager(void)
{
	DrawEnemy01();
	DrawEnemy02();
	DrawEnemy03();
}