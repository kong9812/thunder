#include "main.h"
#include "sound.h"
#include "EffectManager.h"
#include "PlayerBulletManager.h"
#include "TutorialPlayerBullet.h"
#include "TutorialPlayerBomb.h"
#include "TutorialEnemy.h"
#include "TutorialCollider.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// BC
bool TutorialBoundingCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float Size1, float Size2);


// 当たり判定
void PlayerBullet01TutorialEnemyCollider(void);
void PlayerBombTutorialEnemyCollider(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECTSOUNDBUFFER8	g_pTutorialHitSoundSE;				// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutorialCollider(int InitType)
{
	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// SEロード
		g_pTutorialHitSoundSE = LoadSound(SE_HIT_SOUND);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorialCollider(void)
{


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorialCollider(void)
{
	PlayerBullet01TutorialEnemyCollider();
	PlayerBombTutorialEnemyCollider();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorialCollider(void)
{

}

//=============================================================================
// [ チュトリアルプレイヤーバレット ⇔ チュトリアルエネミー ] 
// 当たり判定 (BC判定)
//============================================================================
void PlayerBullet01TutorialEnemyCollider(void)
{
	ENEMY *tutorialenemy = GetTutorialEnemy();
	PLAYERBULLET *tutorialplayerbullet = GetTutorialPlayerBullet(0);


	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, tutorialplayerbullet++)
	{
		if (tutorialplayerbullet->use == true)
		{
			if (TutorialBoundingCircle(tutorialenemy->pos, tutorialplayerbullet->pos,
				ENEMY_01_SIZE_Y / HALF, PLAYER_BULLET_03_SIZE_Y / HALF))
			{
				// SE再生
				if (IsPlaying(g_pTutorialHitSoundSE) == false)
				{
					g_pTutorialHitSoundSE->SetCurrentPosition(0);
				}
				PlaySound(g_pTutorialHitSoundSE, E_DS8_FLAG_NONE);
				SetEffect01(tutorialenemy->pos);
				tutorialenemy->FlashFlag = true;
				tutorialplayerbullet->use = false;
			}
		}
	}

}

//=============================================================================
// [ チュトリアルプレイヤー爆発 ⇔ チュトリアルエネミー ] 
// 当たり判定 (BC判定)
//============================================================================
void PlayerBombTutorialEnemyCollider(void)
{
	ENEMY *tutorialenemy = GetTutorialEnemy();
	PLAYERBOMB *tutorialplayerbomb = GetTutorialPlayerBomb();


	if (tutorialplayerbomb->use == true)
	{
		if (TutorialBoundingCircle(tutorialenemy->pos, tutorialplayerbomb->pos,
			ENEMY_01_SIZE_Y / HALF, PLAYER_BOMB_SIZE_Y / HALF))
		{
			// SE再生
			if (IsPlaying(g_pTutorialHitSoundSE) == false)
			{
				g_pTutorialHitSoundSE->SetCurrentPosition(0);
			}
			PlaySound(g_pTutorialHitSoundSE, E_DS8_FLAG_NONE);
			SetEffect01(tutorialenemy->pos);
			tutorialenemy->FlashFlag = true;
		}
	}
}


//=============================================================================
// 当たり判定 (BC判定)
//============================================================================
bool TutorialBoundingCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float Size1, float Size2)
{
	if ((Size1 + Size2)*(Size1 + Size2) >
		(pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y))
	{
		return true;
	}
	return false;
}