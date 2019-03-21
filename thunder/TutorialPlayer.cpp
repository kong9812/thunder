#include "main.h"
#include "basic.h"
#include "player.h"
#include "input.h"
#include "sound.h"
#include "UI.h"
#include "TutorialUI.h"
#include "TutorialPlayerBomb.h"
#include "PlayerBulletManager.h"
#include "TutorialPlayerBullet.h"
#include "TutorialPlayer.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void TutorialPlayerKeyboardControl(void);	// キーボード操作
void TutorialPlayerEngineEffect(void);		// エンジンエフェクト
void TutorialPlayerInScreen(void);			// スクリーンに入るアニメション

void TutorialPlayerPause(void);				// ポーズ
void TutorialPlayerShoot(void);				// 弾発射
void TutorialPlayerBomb(void);				// 爆発

void SetTutorialPlayerFlashing(void);		// 点滅処理
void SetTutorialPlayerFlashingOn(void);		// 点滅処理(点)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialPlayer = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialEngineEffect = NULL;	// テクスチャへのポインタ
LPDIRECTSOUNDBUFFER8	g_pTutorialPlayerRespawnSE;					// SE用バッファ
LPDIRECTSOUNDBUFFER8	g_pTutorialPlayerStartSE;					// SE用バッファ

VERTEX_2D				g_TutorialPlayerVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_TutorialEngineEffectVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

PLAYER					TutorialPlayerWk;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutorialPlayer(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *tutorialplayer = GetTutorialPlayer();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_PLAYER,							// ファイルの名前
		&g_D3DTextureTutorialPlayer);			// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_ENGINE_EFFECT,					// ファイルの名前
		&g_D3DTextureTutorialEngineEffect);		// 読み込むメモリー

		// SEロード
		g_pTutorialPlayerRespawnSE = LoadSound(SE_PLAYER_RESPAWN);
		g_pTutorialPlayerStartSE = LoadSound(SE_PLAYER_START);
	}

	tutorialplayer->pos = PLAYER_SPAWN_POS;
	tutorialplayer->alive = true;
	tutorialplayer->StartSE = true;
	tutorialplayer->MainControl = false;
	tutorialplayer->ReSpawnSE = true;
	tutorialplayer->HP = PLAYER_HP_MAX;
	tutorialplayer->EXP = 0;
	tutorialplayer->PatternAnim = 0;
	tutorialplayer->FlashingCount = 0;
	tutorialplayer->CountShoot = 0;
	tutorialplayer->CountAnim = 0;
	tutorialplayer->EffectPos = D3DXVECTOR3(tutorialplayer->pos.x + PLAYER_SIZE_X / 3, tutorialplayer->pos.y + PLAYER_SIZE_Y / HALF, 0.0f);

	// 頂点フォーマット(チュトリアルプレイヤー)
	MakeVtx4PointData(g_TutorialPlayerVertexWk,			// 頂点情報格納ワーク
	tutorialplayer->pos,								// 座標X,Y,Z
	PLAYER_SIZE_X, PLAYER_SIZE_Y);						// サイズX,Y

	// 頂点フォーマット(エンジンエフェクト)
	MakeVtx4PointData(g_TutorialEngineEffectVertexWk,	// 頂点情報格納ワーク
	tutorialplayer->EffectPos,							// 座標X,Y,Z
	ENGINE_EFFECT_SIZE_X, ENGINE_EFFECT_SIZE_Y);		// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorialPlayer(void)
{
	if (g_D3DTextureTutorialPlayer != NULL)
	{// テクスチャの開放
		g_D3DTextureTutorialPlayer->Release();
		g_D3DTextureTutorialPlayer = NULL;
	}

	if (g_D3DTextureTutorialEngineEffect != NULL)
	{// テクスチャの開放
		g_D3DTextureTutorialEngineEffect->Release();
		g_D3DTextureTutorialEngineEffect = NULL;
	}

	if (g_pTutorialPlayerRespawnSE != NULL)
	{
		g_pTutorialPlayerRespawnSE->Release();
		g_pTutorialPlayerRespawnSE = NULL;
	}

	if (g_pTutorialPlayerStartSE != NULL)
	{
		g_pTutorialPlayerStartSE->Release();
		g_pTutorialPlayerStartSE = NULL;
	}	
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorialPlayer(void)
{
	PLAYER *tutorialplayer = GetTutorialPlayer();
	
	if (tutorialplayer->MainControl == true)
	{
		TutorialPlayerKeyboardControl();
		TutorialPlayerEngineEffect();
		TutorialPlayerPause();
		TutorialPlayerShoot();
		TutorialPlayerBomb();
	}

	if ((tutorialplayer->pos.y >= PLAYER_START_POS_Y) && (tutorialplayer->MainControl == false))
	{
		// SE再生
		if ((IsPlaying(g_pTutorialPlayerRespawnSE) == false)&&
			tutorialplayer->ReSpawnSE == true)
		{
			g_pTutorialPlayerRespawnSE->SetCurrentPosition(0);
			PlaySound(g_pTutorialPlayerRespawnSE, E_DS8_FLAG_NONE);
			tutorialplayer->ReSpawnSE = false;
		}

		// SE再生
		if ((IsPlaying(g_pTutorialPlayerRespawnSE) == false) &&
			tutorialplayer->StartSE == true)
		{
			g_pTutorialPlayerStartSE->SetCurrentPosition(0);
			PlaySound(g_pTutorialPlayerStartSE, E_DS8_FLAG_NONE);
			tutorialplayer->StartSE = false;
		}

		TutorialPlayerInScreen();
		tutorialplayer->MainControl = false;
	}

	else if (tutorialplayer->pos.y < SCREEN_HEIGHT)
	{
		

		SetTutorialPlayerFlashingOn();
		tutorialplayer->MainControl = true;
		tutorialplayer->ReSpawnSE = true;
		tutorialplayer->StartSE = true;
	}
}

//=============================================================================
// キーボード操作
//=============================================================================
void TutorialPlayerKeyboardControl()
{
	PLAYER *tutorialplayer = GetTutorialPlayer();

	if (GetKeyboardPress(DIK_W))	 // 上
	{
		if (GetKeyboardPress(DIK_A))	 // 左上
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // 減速
			{
				tutorialplayer->pos.y -= cosf(45)*PLAYER_SHIFT_SPEED;
				tutorialplayer->pos.x -= cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				tutorialplayer->pos.y -= cosf(45)*PLAYER_NORMAL_SPEED;
				tutorialplayer->pos.x -= cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else	 if (GetKeyboardPress(DIK_D)) // 右上
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // 減速
			{
				tutorialplayer->pos.y -= cosf(45)*PLAYER_SHIFT_SPEED;
				tutorialplayer->pos.x += cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				tutorialplayer->pos.y -= cosf(45)*PLAYER_NORMAL_SPEED;
				tutorialplayer->pos.x += cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // 減速
			{
				tutorialplayer->pos.y -= PLAYER_SHIFT_SPEED;
			}
			else
			{
				tutorialplayer->pos.y -= PLAYER_NORMAL_SPEED;
			}
		}
		
	}

	else if (GetKeyboardPress(DIK_S)) // 下
	{
		if (GetKeyboardPress(DIK_A)) // 左下
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // 減速
			{
				tutorialplayer->pos.y += cosf(45)*PLAYER_SHIFT_SPEED;
				tutorialplayer->pos.x -= cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				tutorialplayer->pos.y += cosf(45)*PLAYER_NORMAL_SPEED;
				tutorialplayer->pos.x -= cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else if (GetKeyboardPress(DIK_D)) // 右下
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // 減速
			{
				tutorialplayer->pos.y += cosf(45)*PLAYER_SHIFT_SPEED;
				tutorialplayer->pos.x += cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				tutorialplayer->pos.y += cosf(45)*PLAYER_NORMAL_SPEED;
				tutorialplayer->pos.x += cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // 減速
			{
				tutorialplayer->pos.y += PLAYER_SHIFT_SPEED;
			}
			else
			{
				tutorialplayer->pos.y += PLAYER_NORMAL_SPEED;
			}
		}
	}

	else if (GetKeyboardPress(DIK_A)) // 左
	{
		if (GetKeyboardPress(DIK_LSHIFT)) // 減速
		{
			tutorialplayer->pos.x -= PLAYER_SHIFT_SPEED;
		}
		else
		{
			tutorialplayer->pos.x -= PLAYER_NORMAL_SPEED;
		}
	}

	else if (GetKeyboardPress(DIK_D)) // 右
	{
		if (GetKeyboardPress(DIK_LSHIFT)) // 減速
		{
			tutorialplayer->pos.x += PLAYER_SHIFT_SPEED;
		}
		else
		{
			tutorialplayer->pos.x += PLAYER_NORMAL_SPEED;
		}
	}

	if (tutorialplayer->pos.x < 0.0f)
	{
		tutorialplayer->pos.x = 0.0f;
	}

	if (tutorialplayer->pos.y < 0.0f)
	{
		tutorialplayer->pos.y = 0.0f;
	}

	if (tutorialplayer->pos.x > UI_POS_X - PLAYER_SIZE_X)
	{
		tutorialplayer->pos.x = UI_POS_X - PLAYER_SIZE_X;
	}

	if (tutorialplayer->pos.y > SCREEN_HEIGHT - PLAYER_SIZE_Y)
	{
		tutorialplayer->pos.y = SCREEN_HEIGHT - PLAYER_SIZE_Y;
	}
}

//=============================================================================
// ポーズ
//=============================================================================
void TutorialPlayerPause(void)
{
	if (GetKeyboardTrigger(DIK_P))
	{
		SetPauseStage(STAGE_TUTORIAL);
		SetStage(STAGE_PAUSE);
	}
}

//=============================================================================
// 弾発射
//=============================================================================
void TutorialPlayerShoot(void)
{
	PLAYER *tutorialplayer = GetTutorialPlayer();

	tutorialplayer->CountShoot++;

	if (tutorialplayer->CountShoot >= INT_MAX)
	{
		tutorialplayer->CountShoot -= INT_MAX;
	}


	if (GetKeyboardPress(DIK_K)) // 弾発射
	{
		if ((tutorialplayer->CountShoot % PLAYER_BULLET_SHOOT_TIME) == 0)
		{
			SetTutorialPlayerBullet(tutorialplayer->pos, PLAYER_BULLET_LEFT);
			SetTutorialPlayerBullet(tutorialplayer->pos, PLAYER_BULLET_RIGHT);

		}

		if ((tutorialplayer->CountShoot % PLAYER_BULLET_SHOOT_TIME) == PLAYER_BULLET_SHOOT_TIME / HALF)
		{
			SetTutorialPlayerBullet(tutorialplayer->pos, PLAYER_BULLET_MID);
		}
	}
}

//=============================================================================
// 爆発
//=============================================================================
void TutorialPlayerBomb(void)
{
	if (GetKeyboardTrigger(DIK_J)) // 爆発
	{
		SetTutorialPlayerBomb();
	}
}

//=============================================================================
// 点滅処理
//=============================================================================
void SetTutorialPlayerFlashing(void)
{
	PLAYER *tutorialplayer = GetTutorialPlayer();

	tutorialplayer->FlashingCount++;

	if (tutorialplayer->FlashingCount < PLAYER_FLASHING_HOLD_TIME)
	{
		SetAllDiffuseData(g_TutorialPlayerVertexWk,			// 点
		PLAYER_FLASHING_ALPHA_ON);		
		SetAllDiffuseData(g_TutorialEngineEffectVertexWk,	// 点
		PLAYER_FLASHING_ALPHA_ON);
	}

	if (tutorialplayer->FlashingCount > PLAYER_FLASHING_HOLD_TIME)
	{
		SetAllDiffuseData(g_TutorialPlayerVertexWk,			// 滅
		PLAYER_FLASHING_ALPHA_OFF);	
		SetAllDiffuseData(g_TutorialEngineEffectVertexWk,	// 滅
		PLAYER_FLASHING_ALPHA_OFF);
	}

	if (tutorialplayer->FlashingCount > PLAYER_FLASHING_RESET)
	{
		tutorialplayer->FlashingCount = 0;					// リセット
	}
}

//=============================================================================
// 点滅処理(点)
//=============================================================================
void SetTutorialPlayerFlashingOn(void)
{
	SetAllDiffuseData(g_TutorialPlayerVertexWk,			// 点
	PLAYER_FLASHING_ALPHA_ON);
	SetAllDiffuseData(g_TutorialEngineEffectVertexWk,	// 点
	PLAYER_FLASHING_ALPHA_ON);
}


//=============================================================================
// エンジンエフェクト
//=============================================================================
void TutorialPlayerEngineEffect(void)
{
	PLAYER *tutorialplayer = GetTutorialPlayer();

	tutorialplayer->CountAnim++;

	if (tutorialplayer->CountAnim%TIME_ENGINE_EFFECT_ANIMATION == 0)
	{
		tutorialplayer->PatternAnim++;

		if (tutorialplayer->PatternAnim > ENGINE_EFFECT_ANIM_PATTERN_NUM)
		{
			tutorialplayer->PatternAnim = 0;
		}
	}

	if (tutorialplayer->CountAnim >= INT_MAX)
	{
		tutorialplayer->CountAnim -= INT_MAX;
	}

	// 微調整
	tutorialplayer->EffectPos = D3DXVECTOR3(tutorialplayer->pos.x + PLAYER_SIZE_X / 3,
											tutorialplayer->pos.y + PLAYER_SIZE_Y / 2,
											0.0f);

}

//=============================================================================
// スクリーンに入るアニメション
//=============================================================================
void TutorialPlayerInScreen(void)
{
	PLAYER *tutorialplayer = GetTutorialPlayer();

	tutorialplayer->pos.y -= PLAYER_SHIFT_SPEED;

	SetTutorialPlayerFlashing();

}

//=============================================================================
// 描画処理(チュトリアルプレイヤー)
//=============================================================================
void DrawTutorialPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *tutorialplayer = GetTutorialPlayer();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTutorialPlayer);

	// 頂点座標の設定(頂点情報)
	SetVtx4PointData(g_TutorialPlayerVertexWk, tutorialplayer->pos, PLAYER_SIZE_X, PLAYER_SIZE_Y);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialPlayerVertexWk, sizeof(VERTEX_2D));

}

//=============================================================================
// 描画処理(チュトリアルエンジンエフェクト)
//=============================================================================
void DrawTutorialEngineEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *tutorialplayer = GetTutorialPlayer();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTutorialEngineEffect);

	// テクスチャ座標の設定(アニメーション)
	SetTextureAnimationData(g_TutorialEngineEffectVertexWk, tutorialplayer->PatternAnim, ENGINE_EFFECT_PATTERN_DIVIDE_X, ENGINE_EFFECT_PATTERN_DIVIDE_Y);

	// 頂点座標の設定(頂点情報)
	SetVtx4PointData(g_TutorialEngineEffectVertexWk, tutorialplayer->EffectPos, ENGINE_EFFECT_SIZE_X, ENGINE_EFFECT_SIZE_Y);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialEngineEffectVertexWk, sizeof(VERTEX_2D));

}

//=============================================================================
// チュトリアルプレイヤーの情報を取得
//=============================================================================
PLAYER *GetTutorialPlayer(void)
{
	return &TutorialPlayerWk;
}
