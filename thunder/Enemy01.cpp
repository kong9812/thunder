#include "main.h"
#include "basic.h"
#include "UI.h"
#include "UINumberStage.h"
#include "EnemyBulletManager.h"
#include "Enemy01.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void Enemy01InScreen(float MapPos, ENEMY *enemy);	// スクリーンに入るアニメション
void CheckEnemy01HP(ENEMY *enemy);					// エネミー01のHP処理
void SetEnemy01Flashing(ENEMY *enemy);				// エネミー01の点滅処理
void SetEnemy01Spin(ENEMY *enemy);					// エネミー01の回転処理

void SetEnemy01LBasePos(int no);					// エネミー01(左)の回転前の座標を設定する
void SetEnemy01RBasePos(int no);					// エネミー01(右)の回転前の座標を設定する

void SetEnemy01LOutScreen(int no);					// スクリーンから出る
void SetEnemy01ROutScreen(int no);					// スクリーンから出る

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureEnemy01 = NULL;			// テクスチャへのポインタ

VERTEX_2D				g_Enemy01LVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_Enemy01RVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

ENEMY					Enemy01LeftWk[ENEMY_01_MAX];
ENEMY					Enemy01RightWk[ENEMY_01_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy01(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy01L = GetEnemy01Left(0);
	ENEMY *enemy01R = GetEnemy01Right(0);

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_ENEMY_01,						// ファイルの名前
		&g_D3DTextureEnemy01);					// 読み込むメモリー
	}

	for (int i = 0; i < ENEMY_01_MAX; i++, enemy01L++)
	{
		enemy01L->pos = ENEMY_01L_SPAWN_POS;
		enemy01L->Duffuse = ENEMY_01_FLASHING_ALPHA_ON;
		enemy01L->pos.y -= 80 * i;
		enemy01L->BasePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy01L->rot = D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI);
		enemy01L->alive = false;
		enemy01L->FlashFlag = false;
		enemy01L->ShootCount = 0;
		enemy01L->FlashingCount = 0;
		enemy01L->ShootCount = 0;
		enemy01L->state = ENEMY_MOVE;
		enemy01L->rotAngle = 0;
		enemy01L->HP = ENEMY_01_HP_MAX;
		enemy01L->BaseAngle = atan2f(ENEMY_01_SIZE_Y, ENEMY_01_SIZE_X);	// 角度を初期化
		enemy01L->Radius = D3DXVec2Length(&D3DXVECTOR2(		// 半径
										ENEMY_01_SIZE_X / HALF,
										ENEMY_01_SIZE_Y / HALF));
	}

	for (int i = 0; i < ENEMY_01_MAX; i++, enemy01R++)
	{
		enemy01R->pos = ENEMY_01R_SPAWN_POS;
		enemy01R->Duffuse = ENEMY_01_FLASHING_ALPHA_ON;
		enemy01R->pos.y -= 80 * i;
		enemy01R->BasePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy01R->rot = D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI);
		enemy01R->alive = false;
		enemy01R->FlashFlag = false;
		enemy01R->ShootCount = 0;
		enemy01R->FlashingCount = 0;
		enemy01R->ShootCount = 0;
		enemy01R->state = ENEMY_MOVE;
		enemy01R->rotAngle = 0;
		enemy01R->HP = ENEMY_01_HP_MAX;
		enemy01R->BaseAngle = atan2f(ENEMY_01_SIZE_Y, ENEMY_01_SIZE_X);	// 角度を初期化
		enemy01R->Radius = D3DXVec2Length(&D3DXVECTOR2(		// 半径
										ENEMY_01_SIZE_X / HALF,
										ENEMY_01_SIZE_Y / HALF));
	}

	// 頂点フォーマット(エネミー)
	// エネミー_01(左)
	MakeVtx4PointData(g_Enemy01LVertexWk,	// 頂点情報格納ワーク
	enemy01L->pos,							// 座標X,Y,Z
	ENEMY_01_SIZE_X, ENEMY_01_SIZE_Y);		// サイズX,Y

	// 頂点フォーマット(エネミー)
	// エネミー_01(右)
	MakeVtx4PointData(g_Enemy01RVertexWk,	// 頂点情報格納ワーク
	enemy01R->pos,							// 座標X,Y,Z
	ENEMY_01_SIZE_X, ENEMY_01_SIZE_Y);		// サイズX,Y


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy01(void)
{
	if (g_D3DTextureEnemy01 != NULL)
	{// テクスチャの開放
		g_D3DTextureEnemy01->Release();
		g_D3DTextureEnemy01 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy01(float MapPos)
{
	ENEMY *enemy01L = GetEnemy01Left(0);
	ENEMY *enemy01R = GetEnemy01Right(0);

	for (int i = 0; i < ENEMY_01_MAX; i++, enemy01L++)
	{
		switch (enemy01L->state)
		{
		case ENEMY_MOVE:
			Enemy01InScreen(MapPos, enemy01L);
			break;
		case ENEMY_STOP:
			SetEnemy01LBasePos(i);
			break;
		case ENEMY_ESCAPE:
			SetEnemy01LOutScreen(i);
			break;
		}
		SetEnemy01Spin(enemy01L);
		SetEnemy01Flashing(enemy01L);
		CheckEnemy01HP(enemy01L);
	}

	for (int i = 0; i < ENEMY_01_MAX; i++, enemy01R++)
	{
		switch (enemy01R->state)
		{
		case ENEMY_MOVE:
			Enemy01InScreen(MapPos, enemy01R);
			break;
		case ENEMY_STOP:
			SetEnemy01RBasePos(i);
			break;
		case ENEMY_ESCAPE:
			SetEnemy01ROutScreen(i);
			break;
		}
		SetEnemy01Spin(enemy01R);
		SetEnemy01Flashing(enemy01R);
		CheckEnemy01HP(enemy01R);
	}
}

//=============================================================================
// スクリーンに入るアニメション
//=============================================================================
void Enemy01InScreen(float MapPos, ENEMY *enemy)
{
	UINUMBER *Stagewk = GetStage();

	if (MapPos <= ENEMY_01_STOP_POS_Y)
	{
		enemy->alive = true;
		enemy->pos.y += ENEMY_01_SPEED;
	}

	if (enemy->pos.y >= ENEMY_01_SIZE_Y * 3)
	{
		enemy->state = ENEMY_STOP;
	}
}

//=============================================================================
// スクリーンから出る
//=============================================================================
void SetEnemy01LOutScreen(int no)
{
	ENEMY *enemy01L = GetEnemy01Left(no);

	if (enemy01L->alive == true)
	{
		enemy01L->rotAngle += 1.0f;

		enemy01L->pos.x = enemy01L->BasePos.x + 300.0f * cosf(D3DXToRadian(enemy01L->rotAngle));
		enemy01L->pos.y = enemy01L->BasePos.y + 300.0f * sinf(D3DXToRadian(enemy01L->rotAngle));

		// 画面外出たらfalse
		if ((enemy01L->pos.x < 0.0f - ENEMY_01_SIZE_X) || (enemy01L->pos.x > SCREEN_WIDTH) ||
			(enemy01L->pos.y < 0.0f - ENEMY_01_SIZE_Y) || (enemy01L->pos.y > SCREEN_HEIGHT))
		{
			enemy01L->alive = false;
		}
	}
}

void SetEnemy01ROutScreen(int no)
{
	ENEMY *enemy01R = GetEnemy01Right(no);

	if (enemy01R->alive == true)
	{
		enemy01R->rotAngle += 1.0f;

		enemy01R->pos.x = enemy01R->BasePos.x - 300.0f * cosf(D3DXToRadian(enemy01R->rotAngle));
		enemy01R->pos.y = enemy01R->BasePos.y + 300.0f * sinf(D3DXToRadian(enemy01R->rotAngle));

		// 画面外出たらfalse
		if ((enemy01R->pos.x < 0.0f - ENEMY_01_SIZE_X) || (enemy01R->pos.x > UI_POS_X) ||
			(enemy01R->pos.y < 0.0f - ENEMY_01_SIZE_Y) || (enemy01R->pos.y > SCREEN_HEIGHT))
		{
			enemy01R->alive = false;
		}
	}
}


//=============================================================================
// 回転前の座標を設定
//=============================================================================
void SetEnemy01LBasePos(int no)
{
	ENEMY *enemy01L = GetEnemy01Left(no);
	
	if (enemy01L->alive == true)
	{
		enemy01L->BasePos = enemy01L->pos;
		enemy01L->BasePos.x -= 300.0f;

		SetEnemyBullet(enemy01L->pos, ENEMY_BULLET_01);

		enemy01L->state = ENEMY_ESCAPE;
	}
}

void SetEnemy01RBasePos(int no)
{
	ENEMY *enemy01R = GetEnemy01Right(no);
	
	if (enemy01R->alive == true)
	{
		enemy01R->BasePos = enemy01R->pos;
		enemy01R->BasePos.x += 300.0f;

		SetEnemyBullet(enemy01R->pos, ENEMY_BULLET_01);

		enemy01R->state = ENEMY_ESCAPE;
	}
}


//=============================================================================
// エネミー01の点滅処理
//=============================================================================
void SetEnemy01Flashing(ENEMY *enemy)
{
	if (enemy->alive == true)
	{
		if (enemy->FlashFlag == true)
		{
			enemy->FlashingCount++;

			if (enemy->FlashingCount < ENEMY_01_FLASHING_HOLD_TIME)
			{
				enemy->Duffuse = ENEMY_01_FLASHING_ALPHA_ON;
			}

			if (enemy->FlashingCount > ENEMY_01_FLASHING_HOLD_TIME)
			{
				enemy->Duffuse = ENEMY_01_FLASHING_ALPHA_OFF;
			}

			if (enemy->FlashingCount > ENEMY_01_FLASHING_RESET)
			{
				enemy->Duffuse = ENEMY_01_FLASHING_ALPHA_ON;

				enemy->FlashingCount = 0;					// リセット
				enemy->FlashFlag = false;

			}
		}
	}
}

//=============================================================================
// エネミー01の回転処理
//=============================================================================
void SetEnemy01Spin(ENEMY *enemy)
{
	if (enemy->alive == true)
	{
		enemy->rot.z += ENEMY_01_SPIN_Z;

		if (enemy->rot.z > FLT_MAX)
		{
			enemy->rot.z -= FLT_MAX;
		}
	}
}

//=============================================================================
// エネミー01のHP処理
//=============================================================================
void CheckEnemy01HP(ENEMY *enemy)
{
	if (enemy->HP <= 0)
	{
		enemy->alive = false;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy01(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy01L = GetEnemy01Left(0);
	ENEMY *enemy01R = GetEnemy01Right(0);

	for (int i = 0; i < ENEMY_01_MAX; i++, enemy01L++)
	{
		if (enemy01L->alive == true)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_D3DTextureEnemy01);

			// 頂点座標の設定
			SetVtxCenterData(g_Enemy01LVertexWk, enemy01L->pos, ENEMY_01_SIZE_X, ENEMY_01_SIZE_Y);

			// 反射光の設定(全色)
			SetAllDiffuseData(g_Enemy01LVertexWk,enemy01L->Duffuse);

			// 頂点座標の設定(回転用)
			SetVtxRotData(g_Enemy01LVertexWk, enemy01L->pos, enemy01L->rot, enemy01L->BaseAngle, enemy01L->Radius);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Enemy01LVertexWk, sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < ENEMY_01_MAX; i++, enemy01R++)
	{
		if (enemy01R->alive == true)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_D3DTextureEnemy01);

			// 頂点座標の設定
			SetVtxCenterData(g_Enemy01RVertexWk, enemy01R->pos, ENEMY_01_SIZE_X, ENEMY_01_SIZE_Y);

			// 反射光の設定(全色)
			SetAllDiffuseData(g_Enemy01RVertexWk, enemy01R->Duffuse);

			// 頂点座標の設定(回転用)
			SetVtxRotData(g_Enemy01RVertexWk, enemy01R->pos, enemy01R->rot, enemy01R->BaseAngle, enemy01R->Radius);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Enemy01RVertexWk, sizeof(VERTEX_2D));
		}
	}

}

//=============================================================================
// エネミー01の情報を取得
//=============================================================================
ENEMY *GetEnemy01Left(int no)
{
	return (&Enemy01LeftWk[no]);
}

//=============================================================================
// エネミー01の情報を取得
//=============================================================================
ENEMY *GetEnemy01Right(int no)
{
	return (&Enemy01RightWk[no]);
}