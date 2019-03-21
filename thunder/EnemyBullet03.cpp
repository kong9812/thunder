#include "main.h"
#include "basic.h"
#include "player.h"
#include "UI.h"
#include "EnemyBulletManager.h"
#include "EnemyBullet01.h"
#include "EnemyBullet03.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureEnemyBullet03 = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_EnemyBullet03VertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

ENEMYBULLET				EnemyBullet03Wk[ENEMY_BULLET_03_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyBullet03(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet03 = GetEnemyBullet03(0);

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
			TEXTURE_ENEMY_BULLET_01,				// ファイルの名前
			&g_D3DTextureEnemyBullet03);			// 読み込むメモリー
	}

	for (int i = 0; i < ENEMY_BULLET_03_MAX; i++, enemybullet03++)
	{
		enemybullet03->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// 初期座標X,Y,Z
		enemybullet03->use = false;
		enemybullet03->ShotAngle = 0;
	}

	// 頂点フォーマット
	MakeVtx4PointData(g_EnemyBullet03VertexWk,		// 頂点情報格納ワーク
		enemybullet03->pos, 								// 初期座標X,Y,Z
		ENEMY_BULLET_03_SIZE_X, ENEMY_BULLET_03_SIZE_Y);	// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyBullet03(void)
{
	if (g_D3DTextureEnemyBullet03 != NULL)
	{// テクスチャの開放		 
		g_D3DTextureEnemyBullet03->Release();
		g_D3DTextureEnemyBullet03 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyBullet03(void)
{
	ENEMYBULLET *enemybullet03 = GetEnemyBullet03(0);

	for (int i = 0; i < ENEMY_BULLET_03_MAX; i++, enemybullet03++)
	{
		if (enemybullet03->use == true)
		{
			enemybullet03->pos.x += ENEMY_BULLET_03_SPEED * cosf(enemybullet03->ShotAngle)*2.0f;
			enemybullet03->pos.y += ENEMY_BULLET_03_SPEED * sinf(enemybullet03->ShotAngle)*2.0f;

			// 画面外出たらfalse
			if ((enemybullet03->pos.x < 0.0f - ENEMY_BULLET_03_SIZE_X) || (enemybullet03->pos.x > UI_POS_X) ||
				(enemybullet03->pos.y < 0.0f - ENEMY_BULLET_03_SIZE_Y) || (enemybullet03->pos.y > SCREEN_HEIGHT))
			{
				enemybullet03->use = false;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyBullet03(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet03 = GetEnemyBullet03(0);

	for (int i = 0; i < ENEMY_BULLET_03_MAX; i++, enemybullet03++)
	{
		if (enemybullet03->use == true)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_D3DTextureEnemyBullet03);

			// 頂点座標の設定(頂点情報)
			SetVtx4PointData(g_EnemyBullet03VertexWk, enemybullet03->pos, ENEMY_BULLET_03_SIZE_X, ENEMY_BULLET_03_SIZE_Y);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_EnemyBullet03VertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// バレットを設置
//=============================================================================
void SetEnemyBullet03(D3DXVECTOR3 EnemyPos)
{
	ENEMYBULLET *enemybullet03 = GetEnemyBullet03(0);
	PLAYER *player = GetPlayer();

	for (int i = 0; i < ENEMY_BULLET_03_MAX; i++, enemybullet03++)
	{
		if ((i = 0) && (enemybullet03->use == true))continue;

		if (enemybullet03->use == false)
		{
			enemybullet03->pos = EnemyPos;

			if (i == 0)
			{
				enemybullet03->ShotAngle = atan2f(player->pos.y - enemybullet03->pos.y,
					player->pos.x - enemybullet03->pos.x);
			}

			else
			{
				enemybullet03->ShotAngle = (enemybullet03 - i)->ShotAngle + i * (2.0f*D3DX_PI / 20.0f);
			}

			enemybullet03->use = true;
			break;
		}
	}

}

//=============================================================================
// バレットの情報を取得
//=============================================================================
ENEMYBULLET *GetEnemyBullet03(int no)
{
	return&EnemyBullet03Wk[no];
}
