#include "main.h"
#include "basic.h"
#include "EffectManager.h"
#include "TutorialPlayer.h"
#include "TutorialEnemy.h"
#include "TutorialUI.h"
#include "TutorialBackground.h"
#include "PlayerBullet03.h"
#include "TutorialEnemy.h"
#include "TutorialCollider.h"
#include "TutorialPlayerBullet.h"
#include "TutorialPlayerBomb.h"
#include "TutorialManager.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void DrawTutoria(void);				// コントロール説明

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorial = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_TutorialVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

float g_fTutorialMapScrollPos;		// チュトリアルマップの距離

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutorialManager(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// 初期化
		InitEffectManager(FIRST_INIT);
		InitTutorialCollider(FIRST_INIT);
		InitTutorialEnemy(FIRST_INIT);
		InitTutorialPlayerBomb(FIRST_INIT);
		InitTutorialPlayerBullet(FIRST_INIT);
		InitTutorialBackground(FIRST_INIT);
		InitTutorialPlayer(FIRST_INIT);
		InitTutorialUI(FIRST_INIT);

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_CONTROL,						// ファイルの名前
		&g_D3DTextureTutorial);				// 読み込むメモリー
	}

	else
	{
		// 再初期化
		InitEffectManager(RE_INIT);
		InitTutorialCollider(RE_INIT);
		InitTutorialEnemy(RE_INIT);
		InitTutorialPlayerBomb(RE_INIT);
		InitTutorialPlayerBullet(RE_INIT);
		InitTutorialBackground(RE_INIT);
		InitTutorialPlayer(RE_INIT);
		InitTutorialUI(RE_INIT);
	}

	g_fTutorialMapScrollPos = 0.0f;

	// 頂点フォーマット(コントロール説明)
	MakeVtx4PointData(g_TutorialVertexWk,	// 頂点情報格納ワーク
	D3DXVECTOR3(600, 30, 0),					// 座標X,Y,Z
	CONTROL_SIZE_X, CONTROL_SIZE_Y);			// サイズX,Y

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorialManager(void)
{
	UninitEffectManager();
	UninitTutorialCollider();
	UninitTutorialEnemy();
	UninitTutorialPlayerBomb();
	UninitTutorialPlayerBullet();
	UninitTutorialBackground();
	UninitTutorialPlayer();
	UninitTutorialUI();

	if (g_D3DTextureTutorial != NULL)
	{// テクスチャの開放
		g_D3DTextureTutorial->Release();
		g_D3DTextureTutorial = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorialManager(void)
{
	UpdateTutorialCollider();
	UpdateEffectManager();
	UpdateTutorialPlayerBomb();
	UpdateTutorialPlayerBullet();
	UpdateTutorialBackground();
	UpdateTutorialPlayer();
	UpdateTutorialEnemy(g_fTutorialMapScrollPos);
	UpdateTutorialUI();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorialManager(void)
{
	DrawTutorialCollider();
	DrawTutorialBackground();
	DrawTutorialPlayerBomb();
	DrawTutorialEngineEffect();
	DrawTutorialPlayerBullet();
	DrawTutorialEnemy();
	DrawTutorialPlayer();
	DrawEffectManager();
	DrawTutorialUI();
	DrawTutoria();
}

//=============================================================================
// コントロール説明の描画処理
//=============================================================================
void DrawTutoria(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTutorial);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialVertexWk, sizeof(VERTEX_2D));

}


//=============================================================================
// マップの位置を設定
//=============================================================================
void SetTutorialMapScrollPos(float MapPos)
{
	g_fTutorialMapScrollPos = MapPos;
}

