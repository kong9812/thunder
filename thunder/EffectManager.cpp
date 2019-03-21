#include "main.h"
#include "basic.h"
#include "EffectManager.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureEffect01 = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_Effect01VertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

EFFECT					Effect01Wk[EFFECT_01_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffectManager(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT *effect01 = GetEffect01(0);

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_EFFECT_01,					// ファイルの名前
		&g_D3DTextureEffect01);				// 読み込むメモリー
	}

	for (int i = 0; i < EFFECT_01_MAX; i++, effect01++)
	{
		effect01->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// 初期座標X,Y,Z
		effect01->CountAnim = 0;
		effect01->PatternAnim = 0;
		effect01->use = false;
	}

	// 頂点フォーマット(スタート)
	MakeVtx4PointData(g_Effect01VertexWk,	// 頂点情報格納ワーク
	effect01->pos, 							// 初期座標X,Y,Z
	EFFECT_01_SIZE_X, EFFECT_01_SIZE_Y);	// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffectManager(void)
{
	if (g_D3DTextureEffect01 != NULL)
	{// テクスチャの開放		 
		g_D3DTextureEffect01->Release();
		g_D3DTextureEffect01 = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffectManager(void)
{
	EFFECT *effect01 = GetEffect01(0);

	for (int i = 0; i < EFFECT_01_MAX; i++, effect01++)
	{
		if (effect01->use == true)
		{
			effect01->CountAnim++;

			if (effect01->CountAnim%TIME_EFFECT_01_ANIMATION == 0)
			{
				effect01->PatternAnim++;
			}

			if (effect01->PatternAnim >= EFFECT_01_ANIM_PATTERN_NUM)
			{
				effect01->PatternAnim = 0;
				effect01->CountAnim = 0;
				effect01->use = false;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffectManager(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT *effect01 = GetEffect01(0);

	for (int i = 0; i < EFFECT_01_MAX; i++, effect01++)
	{
		if (effect01->use == true)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_D3DTextureEffect01);

			// テクスチャ座標の設定(アニメーション)
			SetTextureAnimationData(g_Effect01VertexWk, effect01->PatternAnim, EFFECT_01_PATTERN_DIVIDE_X, EFFECT_01_PATTERN_DIVIDE_Y);

			// 頂点座標の設定(頂点情報)
			SetVtx4PointData(g_Effect01VertexWk, effect01->pos, EFFECT_01_SIZE_X, EFFECT_01_SIZE_Y);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Effect01VertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// エフェクトを設置
//=============================================================================
void SetEffect01(D3DXVECTOR3 pos)
{
	EFFECT *effect01 = GetEffect01(0);

	for (int i = 0; i < EFFECT_01_MAX; i++, effect01++)
	{
		if (effect01->use == false)
		{
			effect01->pos = pos;
			effect01->pos.x -= EFFECT_01_SIZE_X / HALF;
			effect01->use = true;
			break;
		}
	}
}

//=============================================================================
// エフェクトの情報を取得
//=============================================================================
EFFECT *GetEffect01(int no)
{
	return&Effect01Wk[no];
}
