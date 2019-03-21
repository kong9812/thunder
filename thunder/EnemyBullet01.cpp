#include "main.h"
#include "basic.h"
#include "player.h"
#include "UI.h"
#include "EnemyBulletManager.h"
#include "EnemyBullet01.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureEnemyBullet01 = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_EnemyBullet01VertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

ENEMYBULLET				EnemyBullet01Wk[ENEMY_BULLET_01_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyBullet01(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet01 = GetEnemyBullet01(0);

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_ENEMY_BULLET_01,				// ファイルの名前
		&g_D3DTextureEnemyBullet01);			// 読み込むメモリー
	}

	for (int i = 0; i < ENEMY_BULLET_01_MAX; i++, enemybullet01++)
	{
		enemybullet01->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// 初期座標X,Y,Z
		enemybullet01->use = false;
		enemybullet01->ShotAngle = 0;
	}

	// 頂点フォーマット(スタート)
	MakeVtx4PointData(g_EnemyBullet01VertexWk,			// 頂点情報格納ワーク
	enemybullet01->pos, 								// 初期座標X,Y,Z
	ENEMY_BULLET_01_SIZE_X, ENEMY_BULLET_01_SIZE_Y);	// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyBullet01(void)
{
	if (g_D3DTextureEnemyBullet01 != NULL)
	{// テクスチャの開放		 
		g_D3DTextureEnemyBullet01->Release();
		g_D3DTextureEnemyBullet01 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyBullet01(void)
{
	ENEMYBULLET *enemybullet01 = GetEnemyBullet01(0);

	for (int i = 0; i < ENEMY_BULLET_01_MAX; i++, enemybullet01++)
	{
		if (enemybullet01->use == true)
		{
			enemybullet01->pos.x += ENEMY_BULLET_01_SPEED * cosf(enemybullet01->ShotAngle);
			enemybullet01->pos.y += ENEMY_BULLET_01_SPEED * sinf(enemybullet01->ShotAngle);

			// 画面外出たらfalse
			if ((enemybullet01->pos.x < 0.0f - ENEMY_BULLET_01_SIZE_X) || (enemybullet01->pos.x > UI_POS_X) ||
				(enemybullet01->pos.y < 0.0f - ENEMY_BULLET_01_SIZE_Y) || (enemybullet01->pos.y > SCREEN_HEIGHT))
			{
				enemybullet01->use = false;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyBullet01(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet01 = GetEnemyBullet01(0);

	for (int i = 0; i < ENEMY_BULLET_01_MAX; i++, enemybullet01++)
	{
		if (enemybullet01->use == true)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_D3DTextureEnemyBullet01);

			// 頂点座標の設定(頂点情報)
			SetVtx4PointData(g_EnemyBullet01VertexWk, enemybullet01->pos, ENEMY_BULLET_01_SIZE_X, ENEMY_BULLET_01_SIZE_Y);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_EnemyBullet01VertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// バレットを設置
//=============================================================================
void SetEnemyBullet01(D3DXVECTOR3 EnemyPos)
{
	ENEMYBULLET *enemybullet01 = GetEnemyBullet01(0);
	PLAYER *player = GetPlayer();

	for (int i = 0; i < ENEMY_BULLET_01_MAX; i++, enemybullet01++)
	{
		if (enemybullet01->use == false)
		{
			enemybullet01->pos = EnemyPos;

			enemybullet01->ShotAngle = atan2f(player->pos.y - enemybullet01->pos.y,
											player->pos.x - enemybullet01->pos.x);
			
			enemybullet01->use = true;
			break;
		}
	}

}

//=============================================================================
// バレットの情報を取得
//=============================================================================
ENEMYBULLET *GetEnemyBullet01(int no)
{
	return&EnemyBullet01Wk[no];
}
