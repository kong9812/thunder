#include "main.h"
#include "UI.h"
#include "player.h"
#include "UINumberExp.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexExp(void);
void SetTextureExp(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUINumberExp = NULL;		// テクスチャへのポリゴン

VERTEX_2D				ExpVertexWk[UI_NUMBER_EXP_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク

UINUMBER				ExpWk;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUINumberExp(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	UINUMBER *expWk = GetExp();

	// テクスチャーの初期化を行う？
	if (InitType == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
		TEXTURE_UI_NUMBER,					// ファイルの名前
		&D3DTextureUINumberExp);				// 読み込むメモリのポインタ
	}

	expWk->pos = D3DXVECTOR3(UI_NUMBER_EXP_POS_X, UI_NUMBER_EXP_POS_Y, 0.0f);
	expWk->value = 0;

	// 頂点情報の作成
	MakeVertexExp();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUINumberExp(void)
{
	if (D3DTextureUINumberExp != NULL)
	{	// テクスチャの開放
		D3DTextureUINumberExp->Release();
		D3DTextureUINumberExp = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateUINumberExp(void)
{
	PLAYER *player = GetPlayer();
	UINUMBER *expWk = GetExp();

	expWk->value = player->EXP;

	SetTextureExp();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUINumberExp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureUINumberExp);

	// スコア
	for (int i = 0; i < UI_NUMBER_EXP_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, ExpVertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexExp(void)
{
	UINUMBER *score = GetExp();

	int i;
	float habaX = 20.0f;	// 数字の横幅

	// 桁数分処理する
	for (i = 0; i < UI_NUMBER_EXP_DIGIT; i++)
	{
		// 頂点座標の設定
		ExpVertexWk[i][0].vtx.x = -habaX * i + score->pos.x;
		ExpVertexWk[i][0].vtx.y = score->pos.y;
		ExpVertexWk[i][0].vtx.z = 0.0f;
		ExpVertexWk[i][1].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		ExpVertexWk[i][1].vtx.y = score->pos.y;
		ExpVertexWk[i][1].vtx.z = 0.0f;
		ExpVertexWk[i][2].vtx.x = -habaX * i + score->pos.x;
		ExpVertexWk[i][2].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		ExpVertexWk[i][2].vtx.z = 0.0f;
		ExpVertexWk[i][3].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		ExpVertexWk[i][3].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		ExpVertexWk[i][3].vtx.z = 0.0f;

		// rhwの設定
		ExpVertexWk[i][0].rhw =
		ExpVertexWk[i][1].rhw =
		ExpVertexWk[i][2].rhw =
		ExpVertexWk[i][3].rhw = 1.0f;

		// 反射光の設定
		ExpVertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ExpVertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ExpVertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ExpVertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		ExpVertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		ExpVertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		ExpVertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		ExpVertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextureExp(void)
{
	UINUMBER *expWk = GetExp();

	int number = expWk->value;

	for (int i = 0; i < UI_NUMBER_EXP_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);

		ExpVertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		ExpVertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		ExpVertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		ExpVertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}

//=============================================================================
// EXPの情報を取得
//=============================================================================
UINUMBER *GetExp(void)
{
	return&ExpWk;
}
