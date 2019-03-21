#include "main.h"
#include "basic.h"
#include "UI.h"
#include "EnemyBulletManager.h"
#include "Enemy03.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void Enemy03InScreen(float MapPos, ENEMY *enemy);		// スクリーンに入るアニメション
void CheckEnemy03HP(ENEMY *enemy);						// エネミー03のHP処理
void SetEnemy03Flashing(ENEMY *enemy);					// エネミー03の点滅処理
void SetEnemy03Spin(ENEMY *enemy);						// エネミー03の回転処理
void SetEnemy03BasePos(void);							// エネミー03の回転前の座標を設定する
void SetEnemy03OutScreen(void);							// スクリーンから出る

void SetEnemy03Shoot(ENEMY *enemy);						// エネミー03の弾発射処理

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureEnemy03 = NULL;			// テクスチャへのポインタ

VERTEX_2D				g_Enemy03VertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

ENEMY					Enemy03Wk;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy03(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy03 = GetEnemy03();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_ENEMY_03,						// ファイルの名前
			&g_D3DTextureEnemy03);					// 読み込むメモリー
	}


	enemy03->pos = ENEMY_03_SPAWN_POS;
	enemy03->Duffuse = ENEMY_03_FLASHING_ALPHA_ON;
	enemy03->pos.y -= 80;
	enemy03->BasePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy03->rot = D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI);
	enemy03->alive = false;
	enemy03->FlashFlag = false;
	enemy03->ShootCount = 0;
	enemy03->FlashingCount = 0;
	enemy03->state = ENEMY_MOVE;
	enemy03->rotAngle = 0;
	enemy03->HP = ENEMY_03_HP_MAX;
	enemy03->BaseAngle = atan2f(ENEMY_03_SIZE_Y, ENEMY_03_SIZE_X);	// 角度を初期化
	enemy03->Radius = D3DXVec2Length(&D3DXVECTOR2(		// 半径
		ENEMY_03_SIZE_X / HALF,
		ENEMY_03_SIZE_Y / HALF));



	// 頂点フォーマット(エネミー)
	// エネミー_01(左)
	MakeVtx4PointData(g_Enemy03VertexWk,	// 頂点情報格納ワーク
		enemy03->pos,							// 座標X,Y,Z
		ENEMY_03_SIZE_X, ENEMY_03_SIZE_Y);		// サイズX,Y


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy03(void)
{
	if (g_D3DTextureEnemy03 != NULL)
	{// テクスチャの開放
		g_D3DTextureEnemy03->Release();
		g_D3DTextureEnemy03 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy03(float MapPos)
{
	ENEMY *enemy03 = GetEnemy03();


	switch (enemy03->state)
	{
	case ENEMY_MOVE:
		Enemy03InScreen(MapPos, enemy03);
		break;
	case ENEMY_STOP:
		SetEnemy03Shoot(enemy03);
		break;
	case ENEMY_ESCAPE:
		break;
	}

	SetEnemy03Flashing(enemy03);

	CheckEnemy03HP(enemy03);
}

//=============================================================================
// スクリーンに入るアニメション
//=============================================================================
void Enemy03InScreen(float MapPos, ENEMY *enemy)
{
	if (MapPos <= ENEMY_03_STOP_POS_Y)
	{
		enemy->alive = true;
		enemy->pos.y += ENEMY_03_SPEED;
	}

	if (enemy->pos.y >= ENEMY_03_SIZE_Y)
	{
		enemy->state = ENEMY_STOP;
	}

}

//=============================================================================
// エネミーの弾発射処理
//=============================================================================
void SetEnemy03Shoot(ENEMY *enemy)
{
	if (enemy->alive == true)
	{
		enemy->ShootCount++;

		if ((enemy->ShootCount%ENEMY_03_SHOOT_03_TIME) == 0)
		{
			SetEnemyBullet(enemy->pos, ENEMY_BULLET_03);
		}

		//if ((enemy->ShootCount%ENEMY_03_SHOOT_02_TIME) == 0)
		//{
		//	SetEnemyBullet(enemy->pos, ENEMY_BULLET_02);
		//}

		//if ((enemy->ShootCount%ENEMY_03_SHOOT_01_TIME) == 0)
		//{
		//	SetEnemyBullet(enemy->pos, ENEMY_BULLET_01);
		//}

		if (enemy->ShootCount >= INT_MAX)
		{
			enemy->ShootCount -= enemy->ShootCount;
		}
	}
}



//=============================================================================
// スクリーンから出る
//=============================================================================
void SetEnemy03OutScreen()
{
	ENEMY *enemy03 = GetEnemy03();

	enemy03->rotAngle += 1.0f;

	enemy03->pos.x = enemy03->BasePos.x + 300.0f * cosf(D3DXToRadian(enemy03->rotAngle));
	enemy03->pos.y = enemy03->BasePos.y + 300.0f * sinf(D3DXToRadian(enemy03->rotAngle));

	// 画面外出たらfalse
	if ((enemy03->pos.x < 0.0f - ENEMY_03_SIZE_X) || (enemy03->pos.x > SCREEN_WIDTH) ||
		(enemy03->pos.y < 0.0f - ENEMY_03_SIZE_Y) || (enemy03->pos.y > SCREEN_HEIGHT))
	{
		enemy03->alive = false;
	}
}


//=============================================================================
// 回転前の座標を設定
//=============================================================================
void SetEnemy03BasePos()
{
	ENEMY *enemy03 = GetEnemy03();

	enemy03->BasePos = enemy03->pos;
	enemy03->BasePos.x += 300.0f;

	enemy03->state = ENEMY_ESCAPE;
}


//=============================================================================
// エネミー01の点滅処理
//=============================================================================
void SetEnemy03Flashing(ENEMY *enemy)
{
	if (enemy->FlashFlag == true)
	{
		enemy->FlashingCount++;

		if (enemy->FlashingCount < ENEMY_03_FLASHING_HOLD_TIME)
		{
			enemy->Duffuse = ENEMY_03_FLASHING_ALPHA_ON;
		}

		if (enemy->FlashingCount > ENEMY_03_FLASHING_HOLD_TIME)
		{
			enemy->Duffuse = ENEMY_03_FLASHING_ALPHA_OFF;
		}

		if (enemy->FlashingCount > ENEMY_03_FLASHING_RESET)
		{
			enemy->Duffuse = ENEMY_03_FLASHING_ALPHA_ON;

			enemy->FlashingCount = 0;					// リセット
			enemy->FlashFlag = false;

		}
	}

}

//=============================================================================
// エネミー01の回転処理
//=============================================================================
void SetEnemy03Spin(ENEMY *enemy)
{
	enemy->rot.z += ENEMY_03_SPIN_Z;

	if (enemy->rot.z > FLT_MAX)
	{
		enemy->rot.z -= FLT_MAX;
	}

}

//=============================================================================
// エネミー01のHP処理
//=============================================================================
void CheckEnemy03HP(ENEMY *enemy)
{
	if (enemy->HP < 0)
	{
		enemy->alive = false;
		SetStage(STAGE_WIN);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy03(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy03 = GetEnemy03();

	if (enemy03->alive == true)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_D3DTextureEnemy03);

		// 頂点座標の設定
		SetVtxCenterData(g_Enemy03VertexWk, enemy03->pos, ENEMY_03_SIZE_X, ENEMY_03_SIZE_Y);

		// 反射光の設定(全色)
		SetAllDiffuseData(g_Enemy03VertexWk, enemy03->Duffuse);

		// 頂点座標の設定(回転用)
		SetVtxRotData(g_Enemy03VertexWk, enemy03->pos, enemy03->rot, enemy03->BaseAngle, enemy03->Radius);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Enemy03VertexWk, sizeof(VERTEX_2D));
	}
}


//=============================================================================
// エネミー03の情報を取得
//=============================================================================
ENEMY *GetEnemy03(void)
{
	return &Enemy03Wk;
}