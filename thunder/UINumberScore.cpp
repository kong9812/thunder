#include "main.h"
#include "UI.h"
#include "UINumberScore.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUINumberScore = NULL;		// テクスチャへのポリゴン

VERTEX_2D				ScoreVertexWk[UI_NUMBER_SCORE_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク

UINUMBER				ScoreWk;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUINumberScore(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	UINUMBER *scoreWk = GetScore();

	// テクスチャーの初期化を行う？
	if (InitType == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_UI_NUMBER,					// ファイルの名前
			&D3DTextureUINumberScore);				// 読み込むメモリのポインタ
	}

	scoreWk->pos = D3DXVECTOR3(UI_NUMBER_SCORE_POS_X, UI_NUMBER_SCORE_POS_Y, 0.0f);
	scoreWk->value = 0;

	// 頂点情報の作成
	MakeVertexScore();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUINumberScore(void)
{
	if (D3DTextureUINumberScore != NULL)
	{	// テクスチャの開放
		D3DTextureUINumberScore->Release();
		D3DTextureUINumberScore = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateUINumberScore(void)
{
	SetTextureScore();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUINumberScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureUINumberScore);

	// スコア
	for (int i = 0; i < UI_NUMBER_SCORE_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, ScoreVertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexScore(void)
{
	UINUMBER *score = GetScore();

	int i;
	float habaX = 20.0f;	// 数字の横幅

							// 桁数分処理する
	for (i = 0; i < UI_NUMBER_SCORE_DIGIT; i++)
	{
		// 頂点座標の設定
		ScoreVertexWk[i][0].vtx.x = -habaX * i + score->pos.x;
		ScoreVertexWk[i][0].vtx.y = score->pos.y;
		ScoreVertexWk[i][0].vtx.z = 0.0f;
		ScoreVertexWk[i][1].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		ScoreVertexWk[i][1].vtx.y = score->pos.y;
		ScoreVertexWk[i][1].vtx.z = 0.0f;
		ScoreVertexWk[i][2].vtx.x = -habaX * i + score->pos.x;
		ScoreVertexWk[i][2].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		ScoreVertexWk[i][2].vtx.z = 0.0f;
		ScoreVertexWk[i][3].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		ScoreVertexWk[i][3].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		ScoreVertexWk[i][3].vtx.z = 0.0f;

		// rhwの設定
		ScoreVertexWk[i][0].rhw =
			ScoreVertexWk[i][1].rhw =
			ScoreVertexWk[i][2].rhw =
			ScoreVertexWk[i][3].rhw = 1.0f;

		// 反射光の設定
		ScoreVertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ScoreVertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ScoreVertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ScoreVertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		ScoreVertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		ScoreVertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		ScoreVertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		ScoreVertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextureScore(void)
{
	UINUMBER *scoreWk = GetScore();

	int number = scoreWk->value;

	for (int i = 0; i < UI_NUMBER_SCORE_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);

		ScoreVertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		ScoreVertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		ScoreVertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		ScoreVertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}
//=============================================================================
// HPデータをセットする
// 引数:add :追加する点数。マイナスも可能、初期化などに。
//=============================================================================
void AddScore(int add)
{
	UINUMBER *scoreWk = GetScore();

	scoreWk->value += add;
	if (scoreWk->value > SCORE_MAX)
	{
		scoreWk->value = SCORE_MAX;
	}

	else if (scoreWk->value < 0)
	{
		scoreWk->value = 0;
	}
}

//=============================================================================
// SCOREの情報を取得
//=============================================================================
UINUMBER *GetScore(void)
{
	return&ScoreWk;
}
