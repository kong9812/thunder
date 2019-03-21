#include "main.h"
#include "UI.h"
#include "player.h"
#include "UINumberLife.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexLife(void);
void SetTextureLife(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUINumberLife = NULL;		// テクスチャへのポリゴン

VERTEX_2D				LifeVertexWk[UI_NUMBER_LIFE_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク

UINUMBER				LifeWk;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUINumberLife(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	UINUMBER *expWk = GetLife();

	// テクスチャーの初期化を行う？
	if (InitType == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_UI_NUMBER,					// ファイルの名前
			&D3DTextureUINumberLife);				// 読み込むメモリのポインタ
	}

	expWk->pos = D3DXVECTOR3(UI_NUMBER_LIFE_POS_X, UI_NUMBER_LIFE_POS_Y, 0.0f);
	expWk->value = 0;

	// 頂点情報の作成
	MakeVertexLife();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUINumberLife(void)
{
	if (D3DTextureUINumberLife != NULL)
	{	// テクスチャの開放
		D3DTextureUINumberLife->Release();
		D3DTextureUINumberLife = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateUINumberLife(void)
{
	PLAYER *player = GetPlayer();
	UINUMBER *expWk = GetLife();

	expWk->value = player->Life;

	SetTextureLife();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUINumberLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureUINumberLife);

	// スコア
	for (int i = 0; i < UI_NUMBER_LIFE_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, LifeVertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexLife(void)
{
	UINUMBER *score = GetLife();

	int i;
	float habaX = 20.0f;	// 数字の横幅

							// 桁数分処理する
	for (i = 0; i < UI_NUMBER_LIFE_DIGIT; i++)
	{
		// 頂点座標の設定
		LifeVertexWk[i][0].vtx.x = -habaX * i + score->pos.x;
		LifeVertexWk[i][0].vtx.y = score->pos.y;
		LifeVertexWk[i][0].vtx.z = 0.0f;
		LifeVertexWk[i][1].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		LifeVertexWk[i][1].vtx.y = score->pos.y;
		LifeVertexWk[i][1].vtx.z = 0.0f;
		LifeVertexWk[i][2].vtx.x = -habaX * i + score->pos.x;
		LifeVertexWk[i][2].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		LifeVertexWk[i][2].vtx.z = 0.0f;
		LifeVertexWk[i][3].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		LifeVertexWk[i][3].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		LifeVertexWk[i][3].vtx.z = 0.0f;

		// rhwの設定
		LifeVertexWk[i][0].rhw =
			LifeVertexWk[i][1].rhw =
			LifeVertexWk[i][2].rhw =
			LifeVertexWk[i][3].rhw = 1.0f;

		// 反射光の設定
		LifeVertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		LifeVertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		LifeVertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		LifeVertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		LifeVertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		LifeVertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		LifeVertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		LifeVertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextureLife(void)
{
	UINUMBER *expWk = GetLife();

	int number = expWk->value;

	for (int i = 0; i < UI_NUMBER_LIFE_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);

		LifeVertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		LifeVertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		LifeVertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		LifeVertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}

//=============================================================================
// LIFEの情報を取得
//=============================================================================
UINUMBER *GetLife(void)
{
	return&LifeWk;
}
