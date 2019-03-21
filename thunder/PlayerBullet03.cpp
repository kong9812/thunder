#include "main.h"
#include "basic.h"
#include "sound.h"
#include "PlayerBulletManager.h"
#include "PlayerBullet01.h"
#include "PlayerBullet03.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePlayerBullet03 = NULL;		// テクスチャへのポインタ
LPDIRECTSOUNDBUFFER8	g_pPlayerBullet03SE;					// SE用バッファ

VERTEX_2D				g_PlayerBullet03VertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

PLAYERBULLET			PlayerBullet03Wk[PLAYER_BULLET_03_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayerBullet03(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *playerbullet03 = GetPlayerBullet03(0);

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_PLAYER_BULLET_01,				// ファイルの名前
		&g_D3DTexturePlayerBullet03);			// 読み込むメモリー

		// SEロード
		g_pPlayerBullet03SE = LoadSound(SE_PLAYER_BULLET_01);
	}

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, playerbullet03++)
	{
		playerbullet03->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// 初期座標X,Y,Z
		playerbullet03->use = false;
	}

	// 頂点フォーマット(スタート)
	MakeVtx4PointData(g_PlayerBullet03VertexWk,				// 頂点情報格納ワーク
	D3DXVECTOR3(-100.0f, -100.0f, 0.0f), 				// 初期座標X,Y,Z
	PLAYER_BULLET_03_SIZE_X, PLAYER_BULLET_03_SIZE_Y);	// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerBullet03(void)
{
	if (g_D3DTexturePlayerBullet03 != NULL)
	{// テクスチャの開放		 
		g_D3DTexturePlayerBullet03->Release();
		g_D3DTexturePlayerBullet03 = NULL;
	}

	if (g_pPlayerBullet03SE != NULL)
	{					
		g_pPlayerBullet03SE->Release();
		g_pPlayerBullet03SE = NULL;
	}					
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerBullet03(void)
{
	PLAYERBULLET *playerbullet03 = GetPlayerBullet03(0);

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, playerbullet03++)
	{
		if (playerbullet03->use == true)
		{
			playerbullet03->pos.y -= PLAYER_BULLET_03_SPEED;
		}

		if (playerbullet03->pos.y <= 0.0f - PLAYER_BULLET_03_SIZE_Y)
		{
			playerbullet03->use = false;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerBullet03(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *playerbullet03 = GetPlayerBullet03(0);

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, playerbullet03++)
	{
		if (playerbullet03->use == true)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_D3DTexturePlayerBullet03);

			// 頂点座標の設定(頂点情報)
			SetVtx4PointData(g_PlayerBullet03VertexWk, playerbullet03->pos, PLAYER_BULLET_03_SIZE_X, PLAYER_BULLET_03_SIZE_Y);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PlayerBullet03VertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// バレットを設置
//=============================================================================
void SetPlayerBullet03(D3DXVECTOR3 PlayerPos, int BulletPos)
{
	PLAYERBULLET *playerbullet03 = GetPlayerBullet03(0);

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, playerbullet03++)
	{
		if (playerbullet03->use == false)
		{
			// SE再生
			g_pPlayerBullet03SE->SetCurrentPosition(0);
			PlaySound(g_pPlayerBullet03SE, E_DS8_FLAG_NONE);

			playerbullet03->pos = PlayerPos;

			if (BulletPos == PLAYER_BULLET_LEFT)
			{
				playerbullet03->pos.x += PLAYER_BULLET_03_PLAYER_LEFT;
			}

			else if (BulletPos == PLAYER_BULLET_RIGHT)
			{
				playerbullet03->pos.x += PLAYER_BULLET_03_PLAYER_RIGHT;
			}

			else if (BulletPos == PLAYER_BULLET_MID)
			{
				playerbullet03->pos.x += PLAYER_BULLET_03_PLAYER_MID;
			}

			playerbullet03->use = true;

			break;
		}
	}
}

//=============================================================================
// バレットの情報を取得
//=============================================================================
PLAYERBULLET *GetPlayerBullet03(int no)
{
	return&PlayerBullet03Wk[no];
}