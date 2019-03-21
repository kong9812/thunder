#include "main.h"
#include "basic.h"
#include "PauseUI.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePauseUI = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_PauseUIVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPauseUI(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_PAUSE_UI,						// ファイルの名前
		&g_D3DTexturePauseUI);					// 読み込むメモリー
	}

	// 頂点フォーマット(背景)
	MakeVtx4PointData(g_PauseUIVertexWk,				// 頂点情報格納ワーク
	D3DXVECTOR3(PAUSE_UI_POS_X, PAUSE_UI_POS_Y, 0.0f), 	// 座標X,Y,Z
	PAUSE_UI_SIZE_X, PAUSE_UI_SIZE_Y);					// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPauseUI(void)
{
	if (g_D3DTexturePauseUI != NULL)
	{
		g_D3DTexturePauseUI->Release();
		g_D3DTexturePauseUI = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePauseUI(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPauseUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTexturePauseUI);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PauseUIVertexWk, sizeof(VERTEX_2D));
}
