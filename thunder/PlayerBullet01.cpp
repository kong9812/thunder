#include "main.h"
#include "basic.h"
#include "sound.h"
#include "PlayerBulletManager.h"
#include "PlayerBullet01.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePlayerBullet01 = NULL;		// テクスチャへのポインタ
LPDIRECTSOUNDBUFFER8	g_pPlayerBullet01SE;					// SE用バッファ

VERTEX_2D				g_PlayerBullet01VertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

PLAYERBULLET			PlayerBullet01Wk[PLAYER_BULLET_01_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayerBullet01(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *playerbullet01 = GetPlayerBullet01(0);

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_PLAYER_BULLET_01,				// ファイルの名前
		&g_D3DTexturePlayerBullet01);			// 読み込むメモリー

													// SEロード
		g_pPlayerBullet01SE = LoadSound(SE_PLAYER_BULLET_01);
	}

	for (int i = 0; i < PLAYER_BULLET_01_MAX; i++, playerbullet01++)
	{
		playerbullet01->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// 初期座標X,Y,Z
		playerbullet01->use = false;
	}

	// 頂点フォーマット(スタート)
	MakeVtx4PointData(g_PlayerBullet01VertexWk,			// 頂点情報格納ワーク
	D3DXVECTOR3(-100.0f, -100.0f, 0.0f), 				// 初期座標X,Y,Z
	PLAYER_BULLET_01_SIZE_X, PLAYER_BULLET_01_SIZE_Y);	// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerBullet01(void)
{
	if (g_D3DTexturePlayerBullet01 != NULL)
	{// テクスチャの開放		 
		g_D3DTexturePlayerBullet01->Release();
		g_D3DTexturePlayerBullet01 = NULL;
	}

	if (g_pPlayerBullet01SE != NULL)
	{					
		g_pPlayerBullet01SE->Release();
		g_pPlayerBullet01SE = NULL;
	}					
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerBullet01(void)
{
	PLAYERBULLET *playerbullet01 = GetPlayerBullet01(0);

	for (int i = 0; i < PLAYER_BULLET_01_MAX; i++, playerbullet01++)
	{
		if (playerbullet01->use == true)
		{
			playerbullet01->pos.y -= PLAYER_BULLET_01_SPEED;
		}

		if (playerbullet01->pos.y <= 0.0f - PLAYER_BULLET_01_SIZE_Y)
		{
			playerbullet01->use = false;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerBullet01(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *playerbullet01 = GetPlayerBullet01(0);

	for (int i = 0; i < PLAYER_BULLET_01_MAX; i++, playerbullet01++)
	{
		if (playerbullet01->use == true)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_D3DTexturePlayerBullet01);

			// 頂点座標の設定(頂点情報)
			SetVtx4PointData(g_PlayerBullet01VertexWk, playerbullet01->pos, PLAYER_BULLET_01_SIZE_X, PLAYER_BULLET_01_SIZE_Y);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PlayerBullet01VertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// バレットを設置
//=============================================================================
void SetPlayerBullet01(D3DXVECTOR3 PlayerPos, int BulletPos)
{
	PLAYERBULLET *playerbullet01 = GetPlayerBullet01(0);

	for (int i = 0; i < PLAYER_BULLET_01_MAX; i++, playerbullet01++)
	{
		if (playerbullet01->use == false)
		{
			playerbullet01->pos = PlayerPos;

			if (BulletPos == PLAYER_BULLET_MID)
			{
				// SE再生
				g_pPlayerBullet01SE->SetCurrentPosition(0);
				PlaySound(g_pPlayerBullet01SE, E_DS8_FLAG_NONE);
				playerbullet01->pos.x += PLAYER_BULLET_01_PLAYER_MID;
			}

			else if ((BulletPos == PLAYER_BULLET_LEFT) ||
					(BulletPos == PLAYER_BULLET_RIGHT))continue;

			playerbullet01->use = true;

			break;
		}
	}
}

//=============================================================================
// バレットの情報を取得
//=============================================================================
PLAYERBULLET *GetPlayerBullet01(int no)
{
	return&PlayerBullet01Wk[no];
}
