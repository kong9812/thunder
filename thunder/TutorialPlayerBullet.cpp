#include "main.h"
#include "basic.h"
#include "PlayerBulletManager.h"
#include "PlayerBullet01.h"
#include "sound.h"
#include"TutorialPlayerBullet.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialPlayerBullet = NULL;		// テクスチャへのポインタ
LPDIRECTSOUNDBUFFER8	g_pTutorialPlayerBullet01SE;					// SE用バッファ

VERTEX_2D				g_TutorialPlayerBulletVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

PLAYERBULLET			TutorialPlayerBulletWk[PLAYER_BULLET_03_MAX];
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutorialPlayerBullet(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *tutorialplayerbullet = GetTutorialPlayerBullet(0);

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_PLAYER_BULLET_01,					// ファイルの名前
		&g_D3DTextureTutorialPlayerBullet);			// 読み込むメモリー

		// SEロード
		g_pTutorialPlayerBullet01SE = LoadSound(SE_PLAYER_BULLET_01);

	}

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, tutorialplayerbullet++)
	{
		tutorialplayerbullet->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// 初期座標X,Y,Z
		tutorialplayerbullet->use = false;
	}

	// 頂点フォーマット(スタート)
	MakeVtx4PointData(g_TutorialPlayerBulletVertexWk,				// 頂点情報格納ワーク
	D3DXVECTOR3(-100.0f, -100.0f, 0.0f), 							// 初期座標X,Y,Z
	PLAYER_BULLET_03_SIZE_X, PLAYER_BULLET_03_SIZE_Y);				// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorialPlayerBullet(void)
{
	if (g_D3DTextureTutorialPlayerBullet != NULL)
	{// テクスチャの開放
		g_D3DTextureTutorialPlayerBullet->Release();
		g_D3DTextureTutorialPlayerBullet = NULL;
	}

	if (g_pTutorialPlayerBullet01SE != NULL)
	{
		g_pTutorialPlayerBullet01SE->Release();
		g_pTutorialPlayerBullet01SE = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorialPlayerBullet(void)
{
	PLAYERBULLET *tutorialplayerbullet = GetTutorialPlayerBullet(0);

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, tutorialplayerbullet++)
	{
		if (tutorialplayerbullet->use == true)
		{
			tutorialplayerbullet->pos.y -= PLAYER_BULLET_03_SPEED;
		}

		if (tutorialplayerbullet->pos.y <= 0.0f - PLAYER_BULLET_03_SIZE_Y)
		{
			tutorialplayerbullet->use = false;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorialPlayerBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *tutorialplayerbullet = GetTutorialPlayerBullet(0);

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, tutorialplayerbullet++)
	{
		if (tutorialplayerbullet->use == true)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_D3DTextureTutorialPlayerBullet);

			// 頂点座標の設定(頂点情報)
			SetVtx4PointData(g_TutorialPlayerBulletVertexWk, tutorialplayerbullet->pos, PLAYER_BULLET_03_SIZE_X, PLAYER_BULLET_03_SIZE_Y);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialPlayerBulletVertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// バレットを設置
//=============================================================================
void SetTutorialPlayerBullet(D3DXVECTOR3 PlayerPos,int BulletPos)
{
	PLAYERBULLET *tutorialplayerbullet = GetTutorialPlayerBullet(0);

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, tutorialplayerbullet++)
	{
		if (tutorialplayerbullet->use == false)
		{
			// SE再生
			g_pTutorialPlayerBullet01SE->SetCurrentPosition(0);
			PlaySound(g_pTutorialPlayerBullet01SE, E_DS8_FLAG_NONE);

			tutorialplayerbullet->pos = PlayerPos;

			if (BulletPos == PLAYER_BULLET_LEFT)
			{
				tutorialplayerbullet->pos.x += PLAYER_BULLET_03_PLAYER_LEFT;
			}

			else if (BulletPos == PLAYER_BULLET_RIGHT)
			{
				tutorialplayerbullet->pos.x += PLAYER_BULLET_03_PLAYER_RIGHT;
			}

			else if (BulletPos == PLAYER_BULLET_MID)
			{
				tutorialplayerbullet->pos.x += PLAYER_BULLET_03_PLAYER_MID;
			}

			tutorialplayerbullet->use = true;
			break;
		}
	}
}

//=============================================================================
// バレットの情報を取得
//=============================================================================
PLAYERBULLET *GetTutorialPlayerBullet(int no)
{
	return&TutorialPlayerBulletWk[no];
}