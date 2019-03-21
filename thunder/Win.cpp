#include "main.h"
#include "basic.h"
#include "input.h"
#include "Win.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureWin = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_WinVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitWin(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_WIN,						// ファイルの名前
		&g_D3DTextureWin);					// 読み込むメモリー	
	}

	// 頂点フォーマット(背景)
	MakeVtx4PointData(g_WinVertexWk,		// 頂点情報格納ワーク
	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 			// 座標X,Y,Z
	SCREEN_WIDTH, SCREEN_HEIGHT);			// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWin(void)
{
	if (g_D3DTextureWin != NULL)
	{
		g_D3DTextureWin->Release();
		g_D3DTextureWin = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWin(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetStage(STAGE_TITLE);
		InitGame();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWin(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureWin);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_WinVertexWk, sizeof(VERTEX_2D));
}
