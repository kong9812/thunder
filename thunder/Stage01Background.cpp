#include "main.h"
#include "basic.h"
#include "Stage01Manager.h"
#include "TitleBackground.h"
#include "Stage01Background.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// 描画処理
void DrawStage01Background01(void);		// 背景_01描画処理
void DrawStage01Background02(void);		// 背景_02描画処理


// 更新処理
void Stage01BackgroundScroll(void);		// 背景スクロール処理

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureStage01Background01 = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureStage01Background02 = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_Stage01Background01VertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_Stage01Background02VertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

float					g_Stage01Background01ScrollDistance;		// マップ01距離
float					g_Stage01Background02ScrollDistance;		// マップ02距離

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStage01Background(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_TITLE,						// ファイルの名前
		&g_D3DTextureStage01Background01);	// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURT_STAGE_01_BACKGROUND_02,		// ファイルの名前
		&g_D3DTextureStage01Background02);	// 読み込むメモリー
	}

	g_Stage01Background01ScrollDistance = 0;
	g_Stage01Background02ScrollDistance = 0;

	// 頂点フォーマット(STAGE_01背景_01)
	MakeVtx4PointData(g_Stage01Background01VertexWk,	// 頂点情報格納ワーク
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),						// 座標X,Y,Z
	SCREEN_WIDTH, SCREEN_HEIGHT);						// サイズX,Y

	// 頂点フォーマット(STAGE_01背景_02)
	MakeVtx4PointData(g_Stage01Background02VertexWk,				// 頂点情報格納ワーク
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),									// 座標X,Y,Z
	STAGE_01_BACKGROUND_02_SIZE_X, STAGE_01_BACKGROUND_02_SIZE_Y);	// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStage01Background(void)
{
	if (g_D3DTextureStage01Background01 != NULL)
	{
		// テクスチャの開放
		g_D3DTextureStage01Background01->Release();
		g_D3DTextureStage01Background01 = NULL;
	}

	if (g_D3DTextureStage01Background02 != NULL)
	{								  
		// テクスチャの開放			  
		g_D3DTextureStage01Background02->Release();
		g_D3DTextureStage01Background02 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStage01Background(void)
{
	Stage01BackgroundScroll();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStage01Background(void)
{
	DrawStage01Background01();
	DrawStage01Background02();
}


//=============================================================================
// 背景_01描画処理
//=============================================================================
void DrawStage01Background01(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureStage01Background01);

	// テクスチャ座標の設定(背景スクロール用)
	SetTextureScrollData(g_Stage01Background01VertexWk, g_Stage01Background01ScrollDistance);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Stage01Background01VertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 背景_02描画処理
//=============================================================================
void DrawStage01Background02(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureStage01Background02);

	// テクスチャ座標の設定(背景スクロール用)
	SetTextureScrollData(g_Stage01Background02VertexWk, g_Stage01Background02ScrollDistance);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Stage01Background02VertexWk, sizeof(VERTEX_2D));
}


//=============================================================================
// 背景スクロール処理
//=============================================================================
void Stage01BackgroundScroll(void)
{
	g_Stage01Background01ScrollDistance -= STAGE_01_BACKGROUND_01_SCROLL_SPEED;
	g_Stage01Background02ScrollDistance -= STAGE_01_BACKGROUND_02_SCROLL_SPEED;

	if (g_Stage01Background01ScrollDistance < FLT_MIN)
	{
		g_Stage01Background01ScrollDistance -= FLT_MIN;
	}

	if (g_Stage01Background02ScrollDistance < FLT_MIN)
	{
		g_Stage01Background02ScrollDistance -= FLT_MIN;
	}

	SetStage01MapScrollPos(g_Stage01Background02ScrollDistance);
	SetDebugStage01MapPos(g_Stage01Background02ScrollDistance);
}
