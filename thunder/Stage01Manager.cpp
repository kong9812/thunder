#include "main.h"
#include "basic.h"
#include "UI.h"
#include "player.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "Stage01Collider.h"
#include "EnemyBulletManager.h"
#include "PlayerBomb.h"
#include "PlayerBulletManager.h"
#include "Stage01Background.h"
#include "Stage01Manager.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
float g_fStage01MapScrollPos;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStage01Manager(int InitType)
{
	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{		
		// 初期化
		InitEffectManager(FIRST_INIT);
		InitStage01Collider(FIRST_INIT);
		InitStage01Background(FIRST_INIT);
		InitEnemyBulletManager(FIRST_INIT);
		InitPlayerBulletManager(FIRST_INIT);
		InitPlayerBomb(FIRST_INIT);
		InitEnemyManager(FIRST_INIT);
		InitPlayer(FIRST_INIT);
		InitUI(FIRST_INIT);
	}

	else
	{
		// 再初期化
		InitEffectManager(RE_INIT);
		InitStage01Collider(RE_INIT);
		InitStage01Background(RE_INIT);
		InitEnemyBulletManager(RE_INIT);
		InitPlayerBulletManager(RE_INIT);
		InitPlayerBomb(RE_INIT);
		InitEnemyManager(RE_INIT);
		InitPlayer(RE_INIT);
		InitUI(RE_INIT);
	}

	g_fStage01MapScrollPos = 0.0f;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStage01Manager(void)
{
	UninitEffectManager();
	UninitStage01Collider();
	UninitStage01Background();
	UninitEnemyBulletManager();
	UninitPlayerBulletManager();
	UninitPlayerBomb();
	UninitEnemyManager();
	UninitPlayer();
	UninitUI();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStage01Manager(void)
{
	UpdateStage01Background();
	UpdateEnemyBulletManager();
	UpdatePlayerBulletManager();
	UpdatePlayerBomb();
	UpdateEnemyManager(g_fStage01MapScrollPos);
	UpdatePlayer();
	UpdateStage01Collider();
	UpdateEffectManager();
	UpdateUI(g_fStage01MapScrollPos);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStage01Manager(void)
{

	DrawStage01Collider();
	DrawStage01Background();
	DrawPlayerBomb();
	DrawEnemyBulletManager();
	DrawPlayerBulletManager();
	DrawEnemyManager();
	DrawEngineEffect();
	DrawPlayer();
	DrawEffectManager();
	DrawUI();
}

//=============================================================================
// マップの位置を設定
//=============================================================================
void SetStage01MapScrollPos(float MapPos)
{
	g_fStage01MapScrollPos = MapPos;
}
