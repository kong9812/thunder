#include "main.h"
#include "basic.h"
#include "UI.h"
#include "EnemyBulletManager.h"
#include "Enemy02.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void Enemy02InScreen(float MapPos, ENEMY *enemy);	// スクリーンに入るアニメション
void CheckEnemy02HP(ENEMY *enemy);					// エネミー02のHP処理
void SetEnemy02Flashing(ENEMY *enemy);				// エネミー02の点滅処理
void SetEnemy02Spin(ENEMY *enemy);					// エネミー02の回転処理

void SetEnemy02LBasePos(int no);					// エネミー02(左)の回転前の座標を設定する
void SetEnemy02RBasePos(int no);					// エネミー02(右)の回転前の座標を設定する

void SetEnemy02Shoot(ENEMY *enemy);					// エネミー02の弾発射処理

void SetEnemy02LOutScreen(int no);					// スクリーンから出る
void SetEnemy02ROutScreen(int no);					// スクリーンから出る

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureEnemy02 = NULL;			// テクスチャへのポインタ

VERTEX_2D				g_Enemy02LVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_Enemy02RVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

ENEMY					Enemy02LeftWk[ENEMY_02_MAX];
ENEMY					Enemy02RightWk[ENEMY_02_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy02(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy02L = GetEnemy02Left(0);
	ENEMY *enemy02R = GetEnemy02Right(0);

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_ENEMY_02,						// ファイルの名前
			&g_D3DTextureEnemy02);					// 読み込むメモリー
	}

	for (int i = 0; i < ENEMY_02_MAX; i++, enemy02L++)
	{
		enemy02L->pos = ENEMY_02L_SPAWN_POS;
		enemy02L->Duffuse = ENEMY_02_FLASHING_ALPHA_ON;
		enemy02L->pos.y -= 80 * i;
		enemy02L->BasePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy02L->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy02L->HoldTimeCount = 0;
		enemy02L->alive = false;
		enemy02L->FlashFlag = false;
		enemy02L->ShootCount = 0;
		enemy02L->FlashingCount = 0;
		enemy02L->state = ENEMY_MOVE;
		enemy02L->rotAngle = 0;
		enemy02L->HP = ENEMY_02_HP_MAX;
		enemy02L->BaseAngle = atan2f(ENEMY_02_SIZE_Y, ENEMY_02_SIZE_X);	// 角度を初期化
		enemy02L->Radius = D3DXVec2Length(&D3DXVECTOR2(		// 半径
			ENEMY_02_SIZE_X / HALF,
			ENEMY_02_SIZE_Y / HALF));
	}

	for (int i = 0; i < ENEMY_02_MAX; i++, enemy02R++)
	{
		enemy02R->pos = ENEMY_02R_SPAWN_POS;
		enemy02R->Duffuse = ENEMY_02_FLASHING_ALPHA_ON;
		enemy02R->pos.y -= 80 * i;
		enemy02R->BasePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy02R->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy02R->HoldTimeCount = 0;
		enemy02R->alive = false;
		enemy02R->FlashFlag = false;
		enemy02R->ShootCount = 0;
		enemy02R->FlashingCount = 0;
		enemy02R->state = ENEMY_MOVE;
		enemy02R->rotAngle = 0;
		enemy02R->HP = ENEMY_02_HP_MAX;
		enemy02R->BaseAngle = atan2f(ENEMY_02_SIZE_Y, ENEMY_02_SIZE_X);	// 角度を初期化
		enemy02R->Radius = D3DXVec2Length(&D3DXVECTOR2(		// 半径
			ENEMY_02_SIZE_X / HALF,
			ENEMY_02_SIZE_Y / HALF));
	}

	// 頂点フォーマット(エネミー)
	// エネミー_01(左)
	MakeVtx4PointData(g_Enemy02LVertexWk,	// 頂点情報格納ワーク
		enemy02L->pos,							// 座標X,Y,Z
		ENEMY_02_SIZE_X, ENEMY_02_SIZE_Y);		// サイズX,Y

												// 頂点フォーマット(エネミー)
												// エネミー_01(右)
	MakeVtx4PointData(g_Enemy02RVertexWk,	// 頂点情報格納ワーク
		enemy02R->pos,							// 座標X,Y,Z
		ENEMY_02_SIZE_X, ENEMY_02_SIZE_Y);		// サイズX,Y


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy02(void)
{
	if (g_D3DTextureEnemy02 != NULL)
	{// テクスチャの開放
		g_D3DTextureEnemy02->Release();
		g_D3DTextureEnemy02 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy02(float MapPos)
{
	ENEMY *enemy02L = GetEnemy02Left(0);
	ENEMY *enemy02R = GetEnemy02Right(0);

	for (int i = 0; i < ENEMY_02_MAX; i++, enemy02L++)
	{
		switch (enemy02L->state)
		{
		case ENEMY_MOVE:
			Enemy02InScreen(MapPos, enemy02L);
			break;
		case ENEMY_STOP:
			SetEnemy02Shoot(enemy02L);
			SetEnemy02LBasePos(i);
			break;
		case ENEMY_ESCAPE:
			SetEnemy02Spin(enemy02L);
			SetEnemy02LOutScreen(i);
			break;
		}
		SetEnemy02Flashing(enemy02L);
		CheckEnemy02HP(enemy02L);
	}

	for (int i = 0; i < ENEMY_02_MAX; i++, enemy02R++)
	{
		switch (enemy02R->state)
		{
		case ENEMY_MOVE:
			Enemy02InScreen(MapPos, enemy02R);
			break;
		case ENEMY_STOP:
			SetEnemy02Shoot(enemy02R);
			SetEnemy02RBasePos(i);
			break;
		case ENEMY_ESCAPE:
			SetEnemy02Spin(enemy02R);
			SetEnemy02ROutScreen(i);
			break;
		}
		SetEnemy02Flashing(enemy02R);
		CheckEnemy02HP(enemy02R);
	}
}

//=============================================================================
// スクリーンに入るアニメション
//=============================================================================
void Enemy02InScreen(float MapPos, ENEMY *enemy)
{
	if (MapPos <= ENEMY_02_STOP_POS_Y)
	{
		enemy->alive = true;
		enemy->pos.y += ENEMY_02_SPEED;
	}

	if (enemy->pos.y >= ENEMY_02_SIZE_Y * 3)
	{
		enemy->state = ENEMY_STOP;
	}

}

//=============================================================================
// スクリーンから出る
//=============================================================================
void SetEnemy02LOutScreen(int no)
{
	ENEMY *enemy02L = GetEnemy02Left(no);

	if (enemy02L->alive == true)
	{
		enemy02L->pos.x -= ENEMY_02_SPEED;

		// 画面外出たらfalse
		if ((enemy02L->pos.x < 0.0f - ENEMY_02_SIZE_X) || (enemy02L->pos.x > SCREEN_WIDTH) ||
			(enemy02L->pos.y < 0.0f - ENEMY_02_SIZE_Y) || (enemy02L->pos.y > SCREEN_HEIGHT))
		{
			enemy02L->alive = false;
		}
	}
}

void SetEnemy02ROutScreen(int no)
{
	ENEMY *enemy02R = GetEnemy02Right(no);

	if (enemy02R->alive == true)
	{
		enemy02R->pos.x -= ENEMY_02_SPEED;

		// 画面外出たらfalse
		if ((enemy02R->pos.x < 0.0f - ENEMY_02_SIZE_X) || (enemy02R->pos.x > UI_POS_X) ||
			(enemy02R->pos.y < 0.0f - ENEMY_02_SIZE_Y) || (enemy02R->pos.y > SCREEN_HEIGHT))
		{
			enemy02R->alive = false;
		}
	}
}

//=============================================================================
// エネミーの弾発射処理
//=============================================================================
void SetEnemy02Shoot(ENEMY *enemy)
{
	if (enemy->alive == true)
	{
		enemy->ShootCount++;

		if ((enemy->ShootCount%ENEMY_02_SHOOT_TIME) == 0)
		{
			SetEnemyBullet(enemy->pos, ENEMY_BULLET_03);
		}

		if (enemy->ShootCount >= INT_MAX)
		{
			enemy->ShootCount -= enemy->ShootCount;
		}
	}
}

//=============================================================================
// 回転前の座標を設定
//=============================================================================
void SetEnemy02LBasePos(int no)
{
	ENEMY *enemy02L = GetEnemy02Left(no);

	if (enemy02L->alive == true)
	{
		enemy02L->HoldTimeCount++;

		if (enemy02L->HoldTimeCount%ENEMY_02_STOP_TIME == 0)
		{
			enemy02L->state = ENEMY_ESCAPE;
		}
	}
}

void SetEnemy02RBasePos(int no)
{
	ENEMY *enemy02R = GetEnemy02Right(no);

	if (enemy02R->alive == true)
	{
		enemy02R->HoldTimeCount++;

		if (enemy02R->HoldTimeCount%ENEMY_02_STOP_TIME == 0)
		{
			enemy02R->state = ENEMY_ESCAPE;
		}
	}
}


//=============================================================================
// エネミー02の点滅処理
//=============================================================================
void SetEnemy02Flashing(ENEMY *enemy)
{
	if (enemy->FlashFlag == true)
	{
		enemy->FlashingCount++;

		if (enemy->FlashingCount < ENEMY_02_FLASHING_HOLD_TIME)
		{
			enemy->Duffuse = ENEMY_02_FLASHING_ALPHA_ON;
		}

		if (enemy->FlashingCount > ENEMY_02_FLASHING_HOLD_TIME)
		{
			enemy->Duffuse = ENEMY_02_FLASHING_ALPHA_OFF;
		}

		if (enemy->FlashingCount > ENEMY_02_FLASHING_RESET)
		{
			enemy->Duffuse = ENEMY_02_FLASHING_ALPHA_ON;

			enemy->FlashingCount = 0;					// リセット
			enemy->FlashFlag = false;

		}
	}

}

//=============================================================================
// エネミー02の回転処理
//=============================================================================
void SetEnemy02Spin(ENEMY *enemy)
{
	if (enemy->alive == true)
	{
		enemy->rot.z = ENEMY_02_SPIN_Z;
	}
}

//=============================================================================
// エネミー02のHP処理
//=============================================================================
void CheckEnemy02HP(ENEMY *enemy)
{
	if (enemy->HP <= 0)
	{
		enemy->alive = false;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy02(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy02L = GetEnemy02Left(0);
	ENEMY *enemy02R = GetEnemy02Right(0);

	for (int i = 0; i < ENEMY_02_MAX; i++, enemy02L++)
	{
		if (enemy02L->alive == true)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_D3DTextureEnemy02);

			// 頂点座標の設定
			SetVtxCenterData(g_Enemy02LVertexWk, enemy02L->pos, ENEMY_02_SIZE_X, ENEMY_02_SIZE_Y);

			// 反射光の設定(全色)
			SetAllDiffuseData(g_Enemy02LVertexWk, enemy02L->Duffuse);

			// 頂点座標の設定(回転用)
			SetVtxRotData(g_Enemy02LVertexWk, enemy02L->pos, enemy02L->rot, enemy02L->BaseAngle, enemy02L->Radius);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Enemy02LVertexWk, sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < ENEMY_02_MAX; i++, enemy02R++)
	{
		if (enemy02R->alive == true)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_D3DTextureEnemy02);

			// 頂点座標の設定
			SetVtxCenterData(g_Enemy02RVertexWk, enemy02R->pos, ENEMY_02_SIZE_X, ENEMY_02_SIZE_Y);

			// 反射光の設定(全色)
			SetAllDiffuseData(g_Enemy02RVertexWk, enemy02R->Duffuse);

			// 頂点座標の設定(回転用)
			SetVtxRotData(g_Enemy02RVertexWk, enemy02R->pos, enemy02R->rot, enemy02R->BaseAngle, enemy02R->Radius);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Enemy02RVertexWk, sizeof(VERTEX_2D));
		}
	}

}

//=============================================================================
// エネミー02の情報を取得
//=============================================================================
ENEMY *GetEnemy02Left(int no)
{
	return (&Enemy02LeftWk[no]);
}

//=============================================================================
// エネミー02の情報を取得
//=============================================================================
ENEMY *GetEnemy02Right(int no)
{
	return (&Enemy02RightWk[no]);
}