#include "main.h"
#include "player.h"
#include "PlayerBullet01.h"
#include "PlayerBullet02.h"
#include "PlayerBullet03.h"
#include "PlayerBulletManager.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayerBulletManager(int InitType)
{
	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{	// 初期化
		InitPlayerBullet01(FIRST_INIT);
		InitPlayerBullet02(FIRST_INIT);
		InitPlayerBullet03(FIRST_INIT);
	}

	else
	{	// 再初期化
		InitPlayerBullet01(RE_INIT);
		InitPlayerBullet02(RE_INIT);
		InitPlayerBullet03(RE_INIT);
	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerBulletManager(void)
{
	UninitPlayerBullet01();
	UninitPlayerBullet02();
	UninitPlayerBullet03();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerBulletManager(void)
{
	UpdatePlayerBullet01();
	UpdatePlayerBullet02();
	UpdatePlayerBullet03();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerBulletManager(void)
{
	DrawPlayerBullet01();
	DrawPlayerBullet02();
	DrawPlayerBullet03();
}

//=============================================================================
// バレットを設置
//=============================================================================
void SetPlayerBullet(D3DXVECTOR3 PlayerPos, int BulletPos)
{
	PLAYER *player = GetPlayer();

	if (player->Level == PLAYER_LEVEL_01)
	{
		SetPlayerBullet01(PlayerPos, BulletPos);
	}

	if (player->Level == PLAYER_LEVEL_02)
	{
		SetPlayerBullet02(PlayerPos, BulletPos);
	}

	if (player->Level == PLAYER_LEVEL_03)
	{
		SetPlayerBullet03(PlayerPos, BulletPos);
	}

	if (player->Level == PLAYER_LEVEL_04)
	{

	}
}