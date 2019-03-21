#include "main.h"
#include "basic.h"
#include "sound.h"
#include "PlayerBomb.h"
#include "TutorialPlayerBomb.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialPlayerBomb = NULL;		// テクスチャへのポインタ
LPDIRECTSOUNDBUFFER8	g_pTutorialPlayerBombSE;					// SE用バッファ

VERTEX_2D				g_TutorialPlayerBombVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

PLAYERBOMB				TutorialPlayerBombWk;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutorialPlayerBomb(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBOMB *tutorialplayerbomb = GetTutorialPlayerBomb();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_PLAYER_BOMB,					// ファイルの名前
		&g_D3DTextureTutorialPlayerBomb);		// 読み込むメモリー

		// SEロード
		g_pTutorialPlayerBombSE = LoadSound(SE_PLAYER_BOMB);
	}

	tutorialplayerbomb->CountAnim = 0;
	tutorialplayerbomb->PatternAnim = 0;
	tutorialplayerbomb->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	tutorialplayerbomb->use = false;

	// 頂点フォーマット(エンジンエフェクト)
	MakeVtx4PointData(g_TutorialPlayerBombVertexWk,	// 頂点情報格納ワーク
	tutorialplayerbomb->pos,						// 座標X,Y,Z
	ENGINE_EFFECT_SIZE_X, ENGINE_EFFECT_SIZE_Y);	// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorialPlayerBomb(void)
{
	if (g_D3DTextureTutorialPlayerBomb != NULL)
	{// テクスチャの開放
		g_D3DTextureTutorialPlayerBomb->Release();
		g_D3DTextureTutorialPlayerBomb = NULL;
	}

	if (g_pTutorialPlayerBombSE != NULL)
	{// テクスチャの開放
		g_pTutorialPlayerBombSE->Release();
		g_pTutorialPlayerBombSE = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorialPlayerBomb(void)
{
	PLAYERBOMB *tutorialplayerbomb = GetTutorialPlayerBomb();

	if (tutorialplayerbomb->use == true)
	{
		tutorialplayerbomb->CountAnim++;

		if (tutorialplayerbomb->CountAnim >= INT_MAX)
		{
			tutorialplayerbomb->CountAnim -= INT_MAX;
		}

		if (tutorialplayerbomb->CountAnim%TIME_PLAYER_BOMB_ANIMATION == 0)
		{
			tutorialplayerbomb->PatternAnim++;

			if (tutorialplayerbomb->PatternAnim > ENGINE_EFFECT_ANIM_PATTERN_NUM)
			{
				tutorialplayerbomb->use = false;
				tutorialplayerbomb->PatternAnim = 0;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorialPlayerBomb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBOMB *tutorialplayerbomb = GetTutorialPlayerBomb();

	if (tutorialplayerbomb->use == true)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_D3DTextureTutorialPlayerBomb);

		// テクスチャ座標の設定(アニメーション)
		SetTextureAnimationData(g_TutorialPlayerBombVertexWk, tutorialplayerbomb->PatternAnim, PLAYER_BOMB_PATTERN_DIVIDE_X, PLAYER_BOMB_PATTERN_DIVIDE_Y);

		// 頂点座標の設定(頂点情報)
		SetVtx4PointData(g_TutorialPlayerBombVertexWk, tutorialplayerbomb->pos, PLAYER_BOMB_SIZE_X, PLAYER_BOMB_SIZE_Y);

		// 反射光の設定(全色)
		SetAllDiffuseData(g_TutorialPlayerBombVertexWk, PLAYER_BOMB_COLOR);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialPlayerBombVertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 爆発を設置
//=============================================================================
void SetTutorialPlayerBomb(void)
{
	PLAYERBOMB *tutorialplayerbomb = GetTutorialPlayerBomb();

	if (tutorialplayerbomb->use == false)
	{
		// SE再生
		g_pTutorialPlayerBombSE->SetCurrentPosition(0);
		PlaySound(g_pTutorialPlayerBombSE, E_DS8_FLAG_NONE);

		tutorialplayerbomb->use = true;
	}
}

//=============================================================================
// 爆発の情報を取得
//=============================================================================
PLAYERBOMB *GetTutorialPlayerBomb(void)
{
	return &TutorialPlayerBombWk;
}
