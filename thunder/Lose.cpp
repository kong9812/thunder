#include "main.h"
#include "basic.h"
#include "input.h"
#include "Lose.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureLose = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_LoseVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitLose(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_LOSE,						// ファイルの名前
		&g_D3DTextureLose);					// 読み込むメモリー
	}

	// 頂点フォーマット(背景)
	MakeVtx4PointData(g_LoseVertexWk,		// 頂点情報格納ワーク
	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 			// 座標X,Y,Z
	SCREEN_WIDTH, SCREEN_HEIGHT);			// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLose(void)
{
	if (g_D3DTextureLose != NULL)
	{
		g_D3DTextureLose->Release();
		g_D3DTextureLose = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLose(void)
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
void DrawLose(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureLose);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_LoseVertexWk, sizeof(VERTEX_2D));
}
