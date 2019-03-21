#include "main.h"
#include "basic.h"
#include "PauseBackground.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePauseBackground = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_PauseBackgroundVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPauseBackground(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマット(背景)
	MakeVtx4PointData(g_PauseBackgroundVertexWk,			// 頂点情報格納ワーク
	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 							// 座標X,Y,Z
	SCREEN_WIDTH, SCREEN_HEIGHT);							// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPauseBackground(void)
{
	if (g_D3DTexturePauseBackground != NULL)
	{
		g_D3DTexturePauseBackground->Release();
		g_D3DTexturePauseBackground = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePauseBackground(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPauseBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTexturePauseBackground);

	// 反射光の設定(一頂点ずつ)
	SetAllDiffuseData(g_PauseBackgroundVertexWk, TITLE_NAME_COLOR_GRAY);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PauseBackgroundVertexWk, sizeof(VERTEX_2D));
}
