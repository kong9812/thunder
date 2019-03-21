#include "main.h"
#include "UI.h"
#include "player.h"
#include "Enemy01.h"
#include "Enemy02.h"
#include "Enemy03.h"
#include "UINumberStage.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexStage(void);
void SetTextureStage(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUINumberStage = NULL;		// テクスチャへのポリゴン

VERTEX_2D				StageVertexWk[UI_NUMBER_STAGE_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク

UINUMBER				StageWk;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUINumberStage(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	UINUMBER *expWk = GetStage();

	// テクスチャーの初期化を行う？
	if (InitType == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_UI_NUMBER,					// ファイルの名前
			&D3DTextureUINumberStage);				// 読み込むメモリのポインタ
	}

	expWk->pos = D3DXVECTOR3(UI_NUMBER_STAGE_POS_X, UI_NUMBER_STAGE_POS_Y, 0.0f);
	expWk->value = STAGE_0;

	// 頂点情報の作成
	MakeVertexStage();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUINumberStage(void)
{
	if (D3DTextureUINumberStage != NULL)
	{	// テクスチャの開放
		D3DTextureUINumberStage->Release();
		D3DTextureUINumberStage = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateUINumberStage(float MapPos)
{
	UINUMBER *stageWk = GetStage();

	if (MapPos <= ENEMY_01_STOP_POS_Y)
	{
		stageWk->value = STAGE_1;
	}

	if (MapPos <= ENEMY_02_STOP_POS_Y)
	{
		stageWk->value = STAGE_2;
	}

	if (MapPos <= ENEMY_03_STOP_POS_Y)
	{
		stageWk->value = STAGE_3;
	}


	SetTextureStage();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUINumberStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureUINumberStage);

	// スコア
	for (int i = 0; i < UI_NUMBER_STAGE_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, StageVertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexStage(void)
{
	UINUMBER *score = GetStage();

	int i;
	float habaX = 20.0f;	// 数字の横幅

							// 桁数分処理する
	for (i = 0; i < UI_NUMBER_STAGE_DIGIT; i++)
	{
		// 頂点座標の設定
		StageVertexWk[i][0].vtx.x = -habaX * i + score->pos.x;
		StageVertexWk[i][0].vtx.y = score->pos.y;
		StageVertexWk[i][0].vtx.z = 0.0f;
		StageVertexWk[i][1].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		StageVertexWk[i][1].vtx.y = score->pos.y;
		StageVertexWk[i][1].vtx.z = 0.0f;
		StageVertexWk[i][2].vtx.x = -habaX * i + score->pos.x;
		StageVertexWk[i][2].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		StageVertexWk[i][2].vtx.z = 0.0f;
		StageVertexWk[i][3].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		StageVertexWk[i][3].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		StageVertexWk[i][3].vtx.z = 0.0f;

		// rhwの設定
		StageVertexWk[i][0].rhw =
			StageVertexWk[i][1].rhw =
			StageVertexWk[i][2].rhw =
			StageVertexWk[i][3].rhw = 1.0f;

		// 反射光の設定
		StageVertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		StageVertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		StageVertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		StageVertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		StageVertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		StageVertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		StageVertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		StageVertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextureStage(void)
{
	UINUMBER *expWk = GetStage();

	int number = expWk->value;

	for (int i = 0; i < UI_NUMBER_STAGE_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);

		StageVertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		StageVertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		StageVertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		StageVertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}

//=============================================================================
// STAGEの情報を取得
//=============================================================================
UINUMBER *GetStage(void)
{
	return&StageWk;
}
