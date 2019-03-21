#include "main.h"
#include "basic.h"
#include "sound.h"
#include "PlayerBomb.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePlayerBomb = NULL;		// テクスチャへのポインタ
LPDIRECTSOUNDBUFFER8	g_pPlayerBombSE;					// SE用バッファ

VERTEX_2D				g_PlayerBombVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

PLAYERBOMB				PlayerBombWk;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayerBomb(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBOMB *tutorialplayerbomb = GetPlayerBomb();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_PLAYER_BOMB,					// ファイルの名前
			&g_D3DTexturePlayerBomb);		// 読み込むメモリー

													// SEロード
		g_pPlayerBombSE = LoadSound(SE_PLAYER_BOMB);
	}

	tutorialplayerbomb->CountAnim = 0;
	tutorialplayerbomb->PatternAnim = 0;
	tutorialplayerbomb->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	tutorialplayerbomb->use = false;

	// 頂点フォーマット(エンジンエフェクト)
	MakeVtx4PointData(g_PlayerBombVertexWk,	// 頂点情報格納ワーク
		tutorialplayerbomb->pos,						// 座標X,Y,Z
		ENGINE_EFFECT_SIZE_X, ENGINE_EFFECT_SIZE_Y);	// サイズX,Y

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerBomb(void)
{
	if (g_D3DTexturePlayerBomb != NULL)
	{// テクスチャの開放
		g_D3DTexturePlayerBomb->Release();
		g_D3DTexturePlayerBomb = NULL;
	}

	if (g_pPlayerBombSE != NULL)
	{// テクスチャの開放
		g_pPlayerBombSE->Release();
		g_pPlayerBombSE = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerBomb(void)
{
	PLAYERBOMB *tutorialplayerbomb = GetPlayerBomb();

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
void DrawPlayerBomb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBOMB *tutorialplayerbomb = GetPlayerBomb();

	if (tutorialplayerbomb->use == true)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_D3DTexturePlayerBomb);

		// テクスチャ座標の設定(アニメーション)
		SetTextureAnimationData(g_PlayerBombVertexWk, tutorialplayerbomb->PatternAnim, PLAYER_BOMB_PATTERN_DIVIDE_X, PLAYER_BOMB_PATTERN_DIVIDE_Y);

		// 頂点座標の設定(頂点情報)
		SetVtx4PointData(g_PlayerBombVertexWk, tutorialplayerbomb->pos, PLAYER_BOMB_SIZE_X, PLAYER_BOMB_SIZE_Y);

		// 反射光の設定(全色)
		SetAllDiffuseData(g_PlayerBombVertexWk, PLAYER_BOMB_COLOR);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PlayerBombVertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 爆発を設置
//=============================================================================
void SetPlayerBomb(void)
{
	PLAYERBOMB *tutorialplayerbomb = GetPlayerBomb();

	if (tutorialplayerbomb->use == false)
	{
		// SE再生
		g_pPlayerBombSE->SetCurrentPosition(0);
		PlaySound(g_pPlayerBombSE, E_DS8_FLAG_NONE);

		tutorialplayerbomb->use = true;
	}
}

//=============================================================================
// 爆発の情報を取得
//=============================================================================
PLAYERBOMB *GetPlayerBomb(void)
{
	return &PlayerBombWk;
}
