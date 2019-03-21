#include "main.h"
#include "basic.h"
#include "UI.h"
#include "TutorialUI.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialUI = NULL;			// テクスチャへのポインタ

VERTEX_2D				g_TutorialUIVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutorialUI(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_TUTORIAL_UI,						// ファイルの名前
		&g_D3DTextureTutorialUI);					// 読み込むメモリー

	}

	// 頂点フォーマット(スタート)
	MakeVtx4PointData(g_TutorialUIVertexWk,			// 頂点情報格納ワーク
	D3DXVECTOR3(UI_POS_X, 0.0f, 0.0f),				// 座標X,Y,Z
	RIGHT_UI_SIZE_X, RIGHT_UI_SIZE_Y);				// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorialUI(void)
{
	if (g_D3DTextureTutorialUI != NULL)
	{// テクスチャの開放
		g_D3DTextureTutorialUI->Release();
		g_D3DTextureTutorialUI = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorialUI(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorialUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTutorialUI);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialUIVertexWk, sizeof(VERTEX_2D));

}
