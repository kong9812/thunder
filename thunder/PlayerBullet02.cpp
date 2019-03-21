#include "main.h"
#include "basic.h"
#include "sound.h"
#include "PlayerBulletManager.h"
#include "PlayerBullet01.h"
#include "PlayerBullet02.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePlayerBullet02 = NULL;		// テクスチャへのポインタ
LPDIRECTSOUNDBUFFER8		g_pPlayerBullet02SE;						// SE用バッファ

VERTEX_2D				g_PlayerBullet02VertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

PLAYERBULLET				PlayerBullet02Wk[PLAYER_BULLET_02_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayerBullet02(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *playerbullet02 = GetPlayerBullet02(0);

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_PLAYER_BULLET_01,				// ファイルの名前
		&g_D3DTexturePlayerBullet02);			// 読み込むメモリー

		// SEロード
		g_pPlayerBullet02SE = LoadSound(SE_PLAYER_BULLET_01);
	}

	for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet02++)
	{
		playerbullet02->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// 初期座標X,Y,Z
		playerbullet02->use = false;
	}

	// 頂点フォーマット(スタート)
	MakeVtx4PointData(g_PlayerBullet02VertexWk,			// 頂点情報格納ワーク
	D3DXVECTOR3(-100.0f, -100.0f, 0.0f), 				// 初期座標X,Y,Z
	PLAYER_BULLET_02_SIZE_X, PLAYER_BULLET_02_SIZE_Y);	// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerBullet02(void)
{
	if (g_D3DTexturePlayerBullet02 != NULL)
	{// テクスチャの開放
		g_D3DTexturePlayerBullet02->Release();
		g_D3DTexturePlayerBullet02 = NULL;
	}

	if (g_pPlayerBullet02SE != NULL)
	{
		g_pPlayerBullet02SE->Release();
		g_pPlayerBullet02SE = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerBullet02(void)
{
	PLAYERBULLET *playerbullet02 = GetPlayerBullet02(0);

	for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet02++)
	{
		if (playerbullet02->use == true)
		{
			playerbullet02->pos.y -= PLAYER_BULLET_02_SPEED;
		}

		if (playerbullet02->pos.y <= 0.0f - PLAYER_BULLET_02_SIZE_Y)
		{
			playerbullet02->use = false;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerBullet02(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *playerbullet02 = GetPlayerBullet02(0);

	for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet02++)
	{
		if (playerbullet02->use == true)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_D3DTexturePlayerBullet02);

			// 頂点座標の設定(頂点情報)
			SetVtx4PointData(g_PlayerBullet02VertexWk, playerbullet02->pos, PLAYER_BULLET_02_SIZE_X, PLAYER_BULLET_02_SIZE_Y);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PlayerBullet02VertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// バレットを設置
//=============================================================================
void SetPlayerBullet02(D3DXVECTOR3 PlayerPos, int BulletPos)
{
	PLAYERBULLET *playerbullet02 = GetPlayerBullet02(0);

	for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet02++)
	{
		if (playerbullet02->use == false)
		{
			playerbullet02->pos = PlayerPos;

			if (BulletPos == PLAYER_BULLET_LEFT)
			{
				// SE再生
				g_pPlayerBullet02SE->SetCurrentPosition(0);
				PlaySound(g_pPlayerBullet02SE, E_DS8_FLAG_NONE);
				playerbullet02->pos.x += PLAYER_BULLET_02_PLAYER_LEFT;
			}

			else if (BulletPos == PLAYER_BULLET_RIGHT)
			{
				// SE再生
				g_pPlayerBullet02SE->SetCurrentPosition(0);
				PlaySound(g_pPlayerBullet02SE, E_DS8_FLAG_NONE);
				playerbullet02->pos.x += PLAYER_BULLET_02_PLAYER_RIGHT;
			}

			else if (BulletPos == PLAYER_BULLET_MID)continue;

			playerbullet02->use = true;

			break;
		}
	}
}

//=============================================================================
// バレットの情報を取得
//=============================================================================
PLAYERBULLET *GetPlayerBullet02(int no)
{
	return&PlayerBullet02Wk[no];
}
