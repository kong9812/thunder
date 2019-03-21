#include "main.h"
#include "UI.h"
#include "player.h"
#include "UINumberLevel.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexLevel(void);
void SetTextureLevel(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUINumberLevel = NULL;		// テクスチャへのポリゴン

VERTEX_2D				LevelVertexWk[UI_NUMBER_LEVEL_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク

UINUMBER				LevelWk;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUINumberLevel(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	UINUMBER *levelWk = GetLevel();

	// テクスチャーの初期化を行う？
	if (InitType == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_UI_NUMBER,					// ファイルの名前
			&D3DTextureUINumberLevel);				// 読み込むメモリのポインタ
	}

	levelWk->pos = D3DXVECTOR3(UI_NUMBER_LEVEL_POS_X, UI_NUMBER_LEVEL_POS_Y, 0.0f);
	levelWk->value = 0;

	// 頂点情報の作成
	MakeVertexLevel();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUINumberLevel(void)
{
	if (D3DTextureUINumberLevel != NULL)
	{	// テクスチャの開放
		D3DTextureUINumberLevel->Release();
		D3DTextureUINumberLevel = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateUINumberLevel(void)
{
	PLAYER *player = GetPlayer();
	UINUMBER *levelWk = GetLevel();

	levelWk->value = player->Level;

	SetTextureLevel();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUINumberLevel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureUINumberLevel);

	// スコア
	for (int i = 0; i < UI_NUMBER_LEVEL_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, LevelVertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexLevel(void)
{
	UINUMBER *score = GetLevel();

	int i;
	float habaX = 20.0f;	// 数字の横幅

							// 桁数分処理する
	for (i = 0; i < UI_NUMBER_LEVEL_DIGIT; i++)
	{
		// 頂点座標の設定
		LevelVertexWk[i][0].vtx.x = -habaX * i + score->pos.x;
		LevelVertexWk[i][0].vtx.y = score->pos.y;
		LevelVertexWk[i][0].vtx.z = 0.0f;
		LevelVertexWk[i][1].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		LevelVertexWk[i][1].vtx.y = score->pos.y;
		LevelVertexWk[i][1].vtx.z = 0.0f;
		LevelVertexWk[i][2].vtx.x = -habaX * i + score->pos.x;
		LevelVertexWk[i][2].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		LevelVertexWk[i][2].vtx.z = 0.0f;
		LevelVertexWk[i][3].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		LevelVertexWk[i][3].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		LevelVertexWk[i][3].vtx.z = 0.0f;

		// rhwの設定
		LevelVertexWk[i][0].rhw =
			LevelVertexWk[i][1].rhw =
			LevelVertexWk[i][2].rhw =
			LevelVertexWk[i][3].rhw = 1.0f;

		// 反射光の設定
		LevelVertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		LevelVertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		LevelVertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		LevelVertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		LevelVertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		LevelVertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		LevelVertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		LevelVertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextureLevel(void)
{
	UINUMBER *levelWk = GetLevel();

	int number = levelWk->value;

	for (int i = 0; i < UI_NUMBER_LEVEL_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);

		LevelVertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		LevelVertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		LevelVertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		LevelVertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}

//=============================================================================
// LEVELの情報を取得
//=============================================================================
UINUMBER *GetLevel(void)
{
	return&LevelWk;
}
