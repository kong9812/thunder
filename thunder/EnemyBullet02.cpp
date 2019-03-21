#include "main.h"
#include "basic.h"
#include "player.h"
#include "UI.h"
#include "EnemyBulletManager.h"
#include "EnemyBullet01.h"
#include "EnemyBullet02.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureEnemyBullet02 = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_EnemyBullet02VertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

ENEMYBULLET				EnemyBullet02Wk[ENEMY_BULLET_02_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyBullet02(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet02 = GetEnemyBullet02(0);

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_ENEMY_BULLET_01,				// ファイルの名前
		&g_D3DTextureEnemyBullet02);			// 読み込むメモリー
	}

	for (int i = 0; i < ENEMY_BULLET_02_MAX; i++, enemybullet02++)
	{
		enemybullet02->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// 初期座標X,Y,Z
		enemybullet02->use = false;
		enemybullet02->ShotAngle = 0;
	}

	// 頂点フォーマット
	MakeVtx4PointData(g_EnemyBullet02VertexWk,		// 頂点情報格納ワーク
	enemybullet02->pos, 								// 初期座標X,Y,Z
	ENEMY_BULLET_02_SIZE_X, ENEMY_BULLET_02_SIZE_Y);	// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyBullet02(void)
{
	if (g_D3DTextureEnemyBullet02 != NULL)
	{// テクスチャの開放		 
		g_D3DTextureEnemyBullet02->Release();
		g_D3DTextureEnemyBullet02 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyBullet02(void)
{
	ENEMYBULLET *enemybullet02 = GetEnemyBullet02(0);

	for (int i = 0; i < ENEMY_BULLET_02_MAX; i++, enemybullet02++)
	{
		if (enemybullet02->use == true)
		{
			enemybullet02->pos.x += ENEMY_BULLET_02_SPEED * cosf(enemybullet02->ShotAngle) + (i - 10) / 4;
			enemybullet02->pos.y += ENEMY_BULLET_02_SPEED * sinf(enemybullet02->ShotAngle);

			// 画面外出たらfalse
			if ((enemybullet02->pos.x < 0.0f - ENEMY_BULLET_02_SIZE_X) || (enemybullet02->pos.x > UI_POS_X) ||
				(enemybullet02->pos.y < 0.0f - ENEMY_BULLET_02_SIZE_Y) || (enemybullet02->pos.y > SCREEN_HEIGHT))
			{
				enemybullet02->use = false;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyBullet02(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet02 = GetEnemyBullet02(0);

	for (int i = 0; i < ENEMY_BULLET_02_MAX; i++, enemybullet02++)
	{
		if (enemybullet02->use == true)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_D3DTextureEnemyBullet02);

			// 頂点座標の設定(頂点情報)
			SetVtx4PointData(g_EnemyBullet02VertexWk, enemybullet02->pos, ENEMY_BULLET_02_SIZE_X, ENEMY_BULLET_02_SIZE_Y);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_EnemyBullet02VertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// バレットを設置
//=============================================================================
void SetEnemyBullet02(D3DXVECTOR3 EnemyPos)
{
	ENEMYBULLET *enemybullet02 = GetEnemyBullet02(0);
	PLAYER *player = GetPlayer();

	for (int i = 0; i < ENEMY_BULLET_02_MAX; i++, enemybullet02++)
	{
		if ((i = 0) && (enemybullet02->use == true))continue;

		if (enemybullet02->use == false)
		{
			enemybullet02->pos = EnemyPos;

			enemybullet02->ShotAngle = atan2f(player->pos.y - enemybullet02->pos.y,
				player->pos.x - enemybullet02->pos.x);

			enemybullet02->use = true;
			break;
		}
	}

}

//=============================================================================
// バレットの情報を取得
//=============================================================================
ENEMYBULLET *GetEnemyBullet02(int no)
{
	return&EnemyBullet02Wk[no];
}
