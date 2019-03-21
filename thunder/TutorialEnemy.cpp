#include "main.h"
#include "basic.h"
#include "Enemy01.h"
#include "TutorialBackground.h"
#include "TutorialEnemy.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void TutorialEnemyInScreen(float MapPos);		// スクリーンに入るアニメション
void CheckTutorialEnemyHP(void);				// チュトリアルエネミーのHP処理

void SetTutorialEnemyFlashing(void);			// チュトリアルエネミーの点滅処理
void SetTutorialEnemySpin(void);				// チュトリアルエネミーの回転処理
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialEnemy = NULL;			// テクスチャへのポインタ

VERTEX_2D				g_TutorialEnemyVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

ENEMY					TutorialEnemyWk;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutorialEnemy(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *tutorialenemy = GetTutorialEnemy();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_ENEMY_01,						// ファイルの名前
		&g_D3DTextureTutorialEnemy);			// 読み込むメモリー
	}

	tutorialenemy->pos = TUTORIAL_ENEMY_SPAWN_POS;
	tutorialenemy->rot = D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI);
	tutorialenemy->alive = false;
	tutorialenemy->movie = true;
	tutorialenemy->FlashFlag = false;
	tutorialenemy->ShootCount = 0;
	tutorialenemy->FlashingCount = 0;
	tutorialenemy->HP = ENEMY_01_HP_MAX;
	tutorialenemy->BaseAngle = atan2f(ENEMY_01_SIZE_Y, ENEMY_01_SIZE_X);	// 角度を初期化
	tutorialenemy->Radius = D3DXVec2Length(&D3DXVECTOR2(					// 半径
							ENEMY_01_SIZE_Y / HALF,
							ENEMY_01_SIZE_X / HALF));

	// 頂点フォーマット(チュトリアルエネミー)
	// エネミー_01
	MakeVtx4PointData(g_TutorialEnemyVertexWk,		// 頂点情報格納ワーク
	tutorialenemy->pos,								// 座標X,Y,Z
	ENEMY_01_SIZE_X, ENEMY_01_SIZE_Y);				// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorialEnemy(void)
{
	if (g_D3DTextureTutorialEnemy != NULL)
	{// テクスチャの開放
		g_D3DTextureTutorialEnemy->Release();
		g_D3DTextureTutorialEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorialEnemy(float MapPos)
{
	TutorialEnemyInScreen(MapPos);

	SetTutorialEnemySpin();

	SetTutorialEnemyFlashing();

	//CheckTutorialEnemyHP();
}

//=============================================================================
// スクリーンに入るアニメション
//=============================================================================
void TutorialEnemyInScreen(float MapPos)
{
	ENEMY *tutorialenemy = GetTutorialEnemy();

	if ((MapPos <= TUTORIAL_ENEMY_STOP_POS_Y) && (tutorialenemy->movie == true))
	{
		tutorialenemy->alive = true;
		tutorialenemy->pos.y += ENEMY_01_SPEED;
	}

	if (tutorialenemy->pos.y >= ENEMY_01_SIZE_Y)
	{
		tutorialenemy->movie = false;
	}

}

//=============================================================================
// チュトリアルエネミーの点滅処理
//=============================================================================
void SetTutorialEnemyFlashing(void)
{
	ENEMY *tutorialenemy = GetTutorialEnemy();

	if (tutorialenemy->FlashFlag == true)
	{
		tutorialenemy->FlashingCount++;

		if (tutorialenemy->FlashingCount < ENEMY_01_FLASHING_HOLD_TIME)
		{
			SetAllDiffuseData(g_TutorialEnemyVertexWk,			// 点
			ENEMY_01_FLASHING_ALPHA_ON);
		}

		if (tutorialenemy->FlashingCount > ENEMY_01_FLASHING_HOLD_TIME)
		{
			SetAllDiffuseData(g_TutorialEnemyVertexWk,			// 滅
			ENEMY_01_FLASHING_ALPHA_OFF);
		}

		if (tutorialenemy->FlashingCount > ENEMY_01_FLASHING_RESET)
		{
			SetAllDiffuseData(g_TutorialEnemyVertexWk,			// 点
			ENEMY_01_FLASHING_ALPHA_ON);

			tutorialenemy->FlashingCount = 0;					// リセット
			tutorialenemy->FlashFlag = false;

		}
	}
}

//=============================================================================
// チュトリアルエネミーの回転処理
//=============================================================================
void SetTutorialEnemySpin(void)
{
	ENEMY *tutorialenemy = GetTutorialEnemy();

	tutorialenemy->rot.z += ENEMY_01_SPIN_Z;

	if (tutorialenemy->rot.z > FLT_MAX)
	{
		tutorialenemy->rot.z -= FLT_MAX;
	}
}

//=============================================================================
// チュトリアルエネミーのHP処理
//=============================================================================
void CheckTutorialEnemyHP(void)
{
	ENEMY *tutorialenemy = GetTutorialEnemy();

	if (tutorialenemy->HP < 0)
	{
		tutorialenemy->alive = false;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorialEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *tutorialenemy = GetTutorialEnemy();

	if (tutorialenemy->alive == true)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_D3DTextureTutorialEnemy);

		// 頂点座標の設定(回転用)
		SetVtxRotData(g_TutorialEnemyVertexWk, tutorialenemy->pos, tutorialenemy->rot, tutorialenemy->BaseAngle, tutorialenemy->Radius);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialEnemyVertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// チュトリアルエネミーの情報を取得
//=============================================================================
ENEMY *GetTutorialEnemy(void)
{
	return &TutorialEnemyWk;
}