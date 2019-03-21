#include "main.h"
#include "basic.h"
#include "UINumberStage.h"
#include "UINumberLife.h"
#include "UINumberBomb.h"
#include "UINumberScore.h"
#include "UINumberExp.h"
#include "UINumberLevel.h"
#include "UI.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureUI = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_UIVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUI(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		InitUINumberStage(FIRST_INIT);
		InitUINumberLife(FIRST_INIT);
		InitUINumberBomb(FIRST_INIT);
		InitUINumberScore(FIRST_INIT);
		InitUINumberExp(FIRST_INIT);
		InitUINumberLevel(FIRST_INIT);

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_UI,							// ファイルの名前
		&g_D3DTextureUI);					// 読み込むメモリー
	}

	else
	{
		InitUINumberStage(RE_INIT);
		InitUINumberLife(RE_INIT);
		InitUINumberBomb(RE_INIT);
		InitUINumberScore(RE_INIT);
		InitUINumberExp(RE_INIT);
		InitUINumberLevel(RE_INIT);
	}

	// 頂点フォーマット(スタート)
	MakeVtx4PointData(g_UIVertexWk,			// 頂点情報格納ワーク
	D3DXVECTOR3(UI_POS_X, 0.0f, 0.0f),		// 座標X,Y,Z
	RIGHT_UI_SIZE_X, RIGHT_UI_SIZE_Y);		// サイズX,Y
	 
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUI(void)
{
	if (g_D3DTextureUI != NULL)
	{// テクスチャの開放
		g_D3DTextureUI->Release();
		g_D3DTextureUI = NULL;
	}

	UninitUINumberStage();
	UninitUINumberLife();
	UninitUINumberBomb();
	UninitUINumberScore();
	UninitUINumberExp();
	UninitUINumberLevel();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateUI(float MapPos)
{
	UpdateUINumberStage(MapPos);
	UpdateUINumberLife();
	UpdateUINumberBomb();
	UpdateUINumberScore();
	UpdateUINumberExp();
	UpdateUINumberLevel();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureUI);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_UIVertexWk, sizeof(VERTEX_2D));

	DrawUINumberStage();
	DrawUINumberLife();
	DrawUINumberBomb();
	DrawUINumberScore();
	DrawUINumberExp();
	DrawUINumberLevel();
}
