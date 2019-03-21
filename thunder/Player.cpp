#include "main.h"
#include "basic.h"
#include "input.h"
#include "sound.h"
#include "UI.h"
#include "EffectManager.h"
#include "PlayerBulletManager.h"
#include "PlayerBomb.h"
#include "player.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void PlayerKeyboardControl(void);	// キーボード操作
void PlayerEngineEffect(void);		// エンジンエフェクト
void PlayerInScreen(void);			// スクリーンに入るアニメション

void PlayerPause(void);				// ポーズ
void PlayerShoot(void);				// 弾発射
void PlayerBomb(void);				// 爆発

void SetPlayerFlashing(void);		// 点滅処理
void SetPlayerFlashingOn(void);		// 点滅処理(点)

void CheckPlayerHP(void);			
void RespawnPlayer(void);

void PlayerLeverUp(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePlayer = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureEngineEffect = NULL;	// テクスチャへのポインタ
LPDIRECTSOUNDBUFFER8	g_pPlayerRespawnSE;					// SE用バッファ
LPDIRECTSOUNDBUFFER8	g_pPlayerStartSE;					// SE用バッファ

VERTEX_2D				g_PlayerVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_EngineEffectVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

PLAYER					PlayerWk;

//=============================================================================
// 初期化処理
//=============================================================================
//=============================================================================
HRESULT InitPlayer(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_PLAYER,							// ファイルの名前
		&g_D3DTexturePlayer);					// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_ENGINE_EFFECT,					// ファイルの名前
		&g_D3DTextureEngineEffect);				// 読み込むメモリー

		// SEロード
		g_pPlayerRespawnSE = LoadSound(SE_PLAYER_RESPAWN);
		g_pPlayerStartSE = LoadSound(SE_PLAYER_START);
	}

	player->pos = PLAYER_SPAWN_POS;
	player->alive = true;
	player->StartSE = true;
	player->MainControl = false;
	player->ReSpawnSE = true;
	player->FlashFlag = false;
	player->HP = PLAYER_HP_MAX;
	player->EXP = 0;
	player->Level = PLAYER_LEVEL_01;
	player->Life = 3;
	player->Bomb = 3;
	player->PatternAnim = 0;
	player->FlashingCount = 0;
	player->CountShoot = 0;
	player->CountAnim = 0;
	player->EffectPos = D3DXVECTOR3(player->pos.x + PLAYER_SIZE_X / 3, player->pos.y + PLAYER_SIZE_Y / HALF, 0.0f);

	// 頂点フォーマット(チュトリアルプレイヤー)
	MakeVtx4PointData(g_PlayerVertexWk,			// 頂点情報格納ワーク
	player->pos,								// 座標X,Y,Z
	PLAYER_SIZE_X, PLAYER_SIZE_Y);				// サイズX,Y

	// 頂点フォーマット(エンジンエフェクト)
	MakeVtx4PointData(g_EngineEffectVertexWk,	// 頂点情報格納ワーク
	player->EffectPos,							// 座標X,Y,Z
	ENGINE_EFFECT_SIZE_X, ENGINE_EFFECT_SIZE_Y);// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if (g_D3DTexturePlayer != NULL)
	{// テクスチャの開放
		g_D3DTexturePlayer->Release();
		g_D3DTexturePlayer = NULL;
	}

	if (g_D3DTextureEngineEffect != NULL)
	{// テクスチャの開放
		g_D3DTextureEngineEffect->Release();
		g_D3DTextureEngineEffect = NULL;
	}

	if (g_pPlayerRespawnSE != NULL)
	{
		g_pPlayerRespawnSE->Release();
		g_pPlayerRespawnSE = NULL;
	}

	if (g_pPlayerStartSE != NULL)
	{
		g_pPlayerStartSE->Release();
		g_pPlayerStartSE = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *player = GetPlayer();

	if (player->alive == true)
	{
		if (player->MainControl == true)
		{
			PlayerKeyboardControl();
			PlayerEngineEffect();
			PlayerPause();
			PlayerShoot();
			PlayerBomb();
		}

		if ((player->pos.y >= PLAYER_START_POS_Y) && (player->MainControl == false))
		{
			// SE再生
			if ((IsPlaying(g_pPlayerRespawnSE) == false) &&
				player->ReSpawnSE == true)
			{
				g_pPlayerRespawnSE->SetCurrentPosition(0);
				PlaySound(g_pPlayerRespawnSE, E_DS8_FLAG_NONE);
				player->ReSpawnSE = false;
			}

			// SE再生
			if ((IsPlaying(g_pPlayerRespawnSE) == false) &&
				player->StartSE == true)
			{
				g_pPlayerStartSE->SetCurrentPosition(0);
				PlaySound(g_pPlayerStartSE, E_DS8_FLAG_NONE);
				player->StartSE = false;
			}

			PlayerInScreen();
			player->MainControl = false;
		}

		else if ((player->pos.y < SCREEN_HEIGHT) && (player->MainControl == false))
		{
			SetPlayerFlashingOn();
			player->FlashFlag = false;
			player->MainControl = true;
			player->ReSpawnSE = true;
			player->StartSE = true;
		}

		SetPlayerFlashing();
		CheckPlayerHP();
		PlayerLeverUp();
	}

	else if (player->alive == false)
	{
		RespawnPlayer();
	}
}
//=============================================================================
// キーボード操作
//=============================================================================
void PlayerKeyboardControl()
{
	PLAYER *player = GetPlayer();

	if (GetKeyboardPress(DIK_W))	 // 上
	{
		if (GetKeyboardPress(DIK_A))	 // 左上
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // 減速
			{
				player->pos.y -= cosf(45)*PLAYER_SHIFT_SPEED;
				player->pos.x -= cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				player->pos.y -= cosf(45)*PLAYER_NORMAL_SPEED;
				player->pos.x -= cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else	 if (GetKeyboardPress(DIK_D)) // 右上
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // 減速
			{
				player->pos.y -= cosf(45)*PLAYER_SHIFT_SPEED;
				player->pos.x += cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				player->pos.y -= cosf(45)*PLAYER_NORMAL_SPEED;
				player->pos.x += cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // 減速
			{
				player->pos.y -= PLAYER_SHIFT_SPEED;
			}
			else
			{
				player->pos.y -= PLAYER_NORMAL_SPEED;
			}
		}

	}

	else if (GetKeyboardPress(DIK_S)) // 下
	{
		if (GetKeyboardPress(DIK_A)) // 左下
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // 減速
			{
				player->pos.y += cosf(45)*PLAYER_SHIFT_SPEED;
				player->pos.x -= cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				player->pos.y += cosf(45)*PLAYER_NORMAL_SPEED;
				player->pos.x -= cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else if (GetKeyboardPress(DIK_D)) // 右下
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // 減速
			{
				player->pos.y += cosf(45)*PLAYER_SHIFT_SPEED;
				player->pos.x += cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				player->pos.y += cosf(45)*PLAYER_NORMAL_SPEED;
				player->pos.x += cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // 減速
			{
				player->pos.y += PLAYER_SHIFT_SPEED;
			}
			else
			{
				player->pos.y += PLAYER_NORMAL_SPEED;
			}
		}
	}

	else if (GetKeyboardPress(DIK_A)) // 左
	{
		if (GetKeyboardPress(DIK_LSHIFT)) // 減速
		{
			player->pos.x -= PLAYER_SHIFT_SPEED;
		}
		else
		{
			player->pos.x -= PLAYER_NORMAL_SPEED;
		}
	}

	else if (GetKeyboardPress(DIK_D)) // 右
	{
		if (GetKeyboardPress(DIK_LSHIFT)) // 減速
		{
			player->pos.x += PLAYER_SHIFT_SPEED;
		}
		else
		{
			player->pos.x += PLAYER_NORMAL_SPEED;
		}
	}

	if (player->pos.x < 0.0f)
	{
		player->pos.x = 0.0f;
	}

	if (player->pos.y < 0.0f)
	{
		player->pos.y = 0.0f;
	}

	if (player->pos.x > UI_POS_X - PLAYER_SIZE_X)
	{
		player->pos.x = UI_POS_X - PLAYER_SIZE_X;
	}

	if (player->pos.y > SCREEN_HEIGHT - PLAYER_SIZE_Y)
	{
		player->pos.y = SCREEN_HEIGHT - PLAYER_SIZE_Y;
	}
}

//=============================================================================
// ポーズ
//=============================================================================
void PlayerPause(void)
{
	if (GetKeyboardTrigger(DIK_P))
	{
		SetPauseStage(STAGE_START_GAME);
		SetStage(STAGE_PAUSE);
	}
}

//=============================================================================
// 弾発射
//=============================================================================
void PlayerShoot(void)
{
	PLAYER *player = GetPlayer();

	player->CountShoot++;

	if (player->CountShoot >= INT_MAX)
	{
		player->CountShoot -= INT_MAX;
	}
	

	if (GetKeyboardPress(DIK_K)) // 弾発射
	{
		if ((player->Level == PLAYER_LEVEL_04) &&
			((player->CountShoot % PLAYER_BULLET_SHOOT_TIME * 2) == 0))
		{
			SetPlayerBullet(player->pos, PLAYER_BULLET_LEFT);
			SetPlayerBullet(player->pos, PLAYER_BULLET_RIGHT);
		}

		else if ((player->CountShoot % PLAYER_BULLET_SHOOT_TIME) == 0)
		{
			SetPlayerBullet(player->pos, PLAYER_BULLET_LEFT);
			SetPlayerBullet(player->pos, PLAYER_BULLET_RIGHT);
		}

		if ((player->CountShoot % PLAYER_BULLET_SHOOT_TIME) == PLAYER_BULLET_SHOOT_TIME / HALF)
		{
			SetPlayerBullet(player->pos, PLAYER_BULLET_MID);
		}
	}
}

//=============================================================================
// 爆発
//=============================================================================
void PlayerBomb(void)
{
	PLAYER *player = GetPlayer();

	if (GetKeyboardTrigger(DIK_J)) // 爆発
	{
		if (player->Bomb > 0)
		{
			player->Bomb--;
			SetPlayerBomb();
		}
	}
}

//=============================================================================
// プレイヤーのレベルアップ処理
//=============================================================================
void PlayerLeverUp(void)
{
	PLAYER *player = GetPlayer();

	if (player->EXP >= PLAYER_LEVEL_UP_EXP)
	{
		player->Level++;
		player->EXP = 0;
	}

	if (player->Level >= PLAYER_LEVEL_04)
	{
		player->Level = PLAYER_LEVEL_03;
	}
}

//=============================================================================
// プレイヤーノHPをチェック
//=============================================================================
void CheckPlayerHP(void)
{
	PLAYER *player = GetPlayer();

	if (player->HP <= 0)
	{
		player->Life --;
		player->MainControl = false;
		SetEffect01(player->pos);
		player->alive = false;
	}

}

//=============================================================================
// プレイヤーの再生
//=============================================================================
void RespawnPlayer(void)
{
	PLAYER *player = GetPlayer();

	if (player->Life > 0)
	{
		player->pos = PLAYER_SPAWN_POS;
		player->HP = PLAYER_HP_MAX;
		player->alive = true;
	}

	else
	{
		SetStage(STAGE_LOSE);
	}
}

//=============================================================================
// 点滅処理
//=============================================================================
void SetPlayerFlashing(void)
{
	PLAYER *player = GetPlayer();

	if (player->FlashFlag == true)
	{
		player->FlashingCount++;

		if (player->FlashingCount < PLAYER_FLASHING_HOLD_TIME)
		{
			SetAllDiffuseData(g_PlayerVertexWk,			// 点
				PLAYER_FLASHING_ALPHA_ON);
			SetAllDiffuseData(g_EngineEffectVertexWk,	// 点
				PLAYER_FLASHING_ALPHA_ON);
		}

		if (player->FlashingCount > PLAYER_FLASHING_HOLD_TIME)
		{
			SetAllDiffuseData(g_PlayerVertexWk,			// 滅
				PLAYER_FLASHING_ALPHA_OFF);
			SetAllDiffuseData(g_EngineEffectVertexWk,	// 滅
				PLAYER_FLASHING_ALPHA_OFF);
		}

		if (player->FlashingCount > PLAYER_FLASHING_RESET)
		{
			player->FlashingCount = 0;					// リセット
			player->FlashFlag = false;
			SetPlayerFlashingOn();
		}
	}
}

//=============================================================================
// 点滅処理(点)
//=============================================================================
void SetPlayerFlashingOn(void)
{
	SetAllDiffuseData(g_PlayerVertexWk,			// 点
		PLAYER_FLASHING_ALPHA_ON);
	SetAllDiffuseData(g_EngineEffectVertexWk,	// 点
		PLAYER_FLASHING_ALPHA_ON);
}


//=============================================================================
// エンジンエフェクト
//=============================================================================
void PlayerEngineEffect(void)
{
	PLAYER *player = GetPlayer();

	player->CountAnim++;

	if (player->CountAnim%TIME_ENGINE_EFFECT_ANIMATION == 0)
	{
		player->PatternAnim++;

		if (player->PatternAnim > ENGINE_EFFECT_ANIM_PATTERN_NUM)
		{
			player->PatternAnim = 0;
		}
	}

	if (player->CountAnim >= INT_MAX)
	{
		player->CountAnim -= INT_MAX;
	}

	// 微調整
	player->EffectPos = D3DXVECTOR3(player->pos.x + PLAYER_SIZE_X / 3,
	player->pos.y + PLAYER_SIZE_Y / 2,
	0.0f);

}

//=============================================================================
// スクリーンに入るアニメション
//=============================================================================
void PlayerInScreen(void)
{
	PLAYER *player = GetPlayer();

	player->pos.y -= PLAYER_SHIFT_SPEED;

	player->FlashFlag = true;

}

//=============================================================================
// 描画処理(チュトリアルプレイヤー)
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer();

	if (player->alive == true)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_D3DTexturePlayer);

		// 頂点座標の設定(頂点情報)
		SetVtx4PointData(g_PlayerVertexWk, player->pos, PLAYER_SIZE_X, PLAYER_SIZE_Y);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PlayerVertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 描画処理(チュトリアルエンジンエフェクト)
//=============================================================================
void DrawEngineEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer();

	if (player->alive == true)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_D3DTextureEngineEffect);

		// テクスチャ座標の設定(アニメーション)
		SetTextureAnimationData(g_EngineEffectVertexWk, player->PatternAnim, ENGINE_EFFECT_PATTERN_DIVIDE_X, ENGINE_EFFECT_PATTERN_DIVIDE_Y);

		// 頂点座標の設定(頂点情報)
		SetVtx4PointData(g_EngineEffectVertexWk, player->EffectPos, ENGINE_EFFECT_SIZE_X, ENGINE_EFFECT_SIZE_Y);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_EngineEffectVertexWk, sizeof(VERTEX_2D));
	}
}


//=============================================================================
// チュトリアルプレイヤーの情報を取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &PlayerWk;
}
