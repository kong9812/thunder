#include "main.h"
#include "UI.h"
#include "player.h"
#include "UINumberBomb.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBomb(void);
void SetTextureBomb(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUINumberBomb = NULL;		// テクスチャへのポリゴン

VERTEX_2D				BombVertexWk[UI_NUMBER_BOMB_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク

UINUMBER				BombWk;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUINumberBomb(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	UINUMBER *expWk = GetBomb();

	// テクスチャーの初期化を行う？
	if (InitType == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_UI_NUMBER,					// ファイルの名前
			&D3DTextureUINumberBomb);				// 読み込むメモリのポインタ
	}

	expWk->pos = D3DXVECTOR3(UI_NUMBER_BOMB_POS_X, UI_NUMBER_BOMB_POS_Y, 0.0f);
	expWk->value = 0;

	// 頂点情報の作成
	MakeVertexBomb();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUINumberBomb(void)
{
	if (D3DTextureUINumberBomb != NULL)
	{	// テクスチャの開放
		D3DTextureUINumberBomb->Release();
		D3DTextureUINumberBomb = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateUINumberBomb(void)
{
	PLAYER *player = GetPlayer();
	UINUMBER *expWk = GetBomb();

	expWk->value = player->Bomb;

	SetTextureBomb();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUINumberBomb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureUINumberBomb);

	// スコア
	for (int i = 0; i < UI_NUMBER_BOMB_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, BombVertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBomb(void)
{
	UINUMBER *score = GetBomb();

	int i;
	float habaX = 20.0f;	// 数字の横幅

							// 桁数分処理する
	for (i = 0; i < UI_NUMBER_BOMB_DIGIT; i++)
	{
		// 頂点座標の設定
		BombVertexWk[i][0].vtx.x = -habaX * i + score->pos.x;
		BombVertexWk[i][0].vtx.y = score->pos.y;
		BombVertexWk[i][0].vtx.z = 0.0f;
		BombVertexWk[i][1].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		BombVertexWk[i][1].vtx.y = score->pos.y;
		BombVertexWk[i][1].vtx.z = 0.0f;
		BombVertexWk[i][2].vtx.x = -habaX * i + score->pos.x;
		BombVertexWk[i][2].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		BombVertexWk[i][2].vtx.z = 0.0f;
		BombVertexWk[i][3].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		BombVertexWk[i][3].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		BombVertexWk[i][3].vtx.z = 0.0f;

		// rhwの設定
		BombVertexWk[i][0].rhw =
			BombVertexWk[i][1].rhw =
			BombVertexWk[i][2].rhw =
			BombVertexWk[i][3].rhw = 1.0f;

		// 反射光の設定
		BombVertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		BombVertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		BombVertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		BombVertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		BombVertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		BombVertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		BombVertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		BombVertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextureBomb(void)
{
	UINUMBER *expWk = GetBomb();

	int number = expWk->value;

	for (int i = 0; i < UI_NUMBER_BOMB_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);

		BombVertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		BombVertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		BombVertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		BombVertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}

//=============================================================================
// BOMBの情報を取得
//=============================================================================
UINUMBER *GetBomb(void)
{
	return&BombWk;
}
