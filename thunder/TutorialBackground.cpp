#include "main.h"
#include "basic.h"
#include "TutorialManager.h"
#include "BackgroundManager.h"
#include "TutorialBackground.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// 更新処理
void TutorialBackgroundScroll(void);		// 背景スクロール処理

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialBackground = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_TutorialBackgroundVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

float					g_TutorialBackgroundScrollDistance;			// マップ距離

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutorialBackground(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_BACKGROUND_01,				// ファイルの名前
		&g_D3DTextureTutorialBackground);	// 読み込むメモリー
	}

	// 頂点フォーマット(チュトリアル背景)
	MakeVtx4PointData(g_TutorialBackgroundVertexWk,		// 頂点情報格納ワーク
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),						// 座標X,Y,Z
	BACKGROUND_01_SIZE_X, BACKGROUND_01_SIZE_Y);		// サイズX,Y

	g_TutorialBackgroundScrollDistance = 0.0f;

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorialBackground(void)
{
	if (g_D3DTextureTutorialBackground != NULL)
	{
		// テクスチャの開放
		g_D3DTextureTutorialBackground->Release();
		g_D3DTextureTutorialBackground = NULL;
	}
}


//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorialBackground(void)
{
	TutorialBackgroundScroll();
}


//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorialBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTutorialBackground);

	// テクスチャ座標の設定(背景スクロール用)
	SetTextureScrollData(g_TutorialBackgroundVertexWk, g_TutorialBackgroundScrollDistance);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialBackgroundVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 背景スクロール処理
//=============================================================================
void TutorialBackgroundScroll(void)
{
	g_TutorialBackgroundScrollDistance -= BACKGROUND_01_SCROLL_SPEED;

	if (g_TutorialBackgroundScrollDistance < FLT_MIN)
	{
		g_TutorialBackgroundScrollDistance -= FLT_MIN;
	}

	SetTutorialMapScrollPos(g_TutorialBackgroundScrollDistance);
	SetDebugTutorialMapPos(g_TutorialBackgroundScrollDistance);
}
