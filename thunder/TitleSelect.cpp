#include "main.h"
#include "basic.h"
#include "sound.h"
#include "input.h"
#include "TitleManager.h"
#include "TitleBackground.h"
#include "TitleSelect.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// 描画処理
void DrawTitleSelectStart(void);		// スタートの描画処理
void DrawTitleSelectTutorial(void);		// チュートリアルの描画処理
void DrawTitleSelectConfig(void);		// コンフィグの描画処理
void DrawTitleSelectEnd(void);			// エンドの描画処理
void DrawTitleSelectArrow(void);		// 矢印の描画処理

// 更新処理
void ControlTitleSelect(void);			// 選択処理(キーボード操作&ゲームパット)
void SetTitleSelectArrow(void);			// 選択処理(矢印)
void SetTitleSelectFlashing(void);		// 選択処理(点滅)
void SetTitleSelectFlashingOn(void);	// 点滅処理(点)
void SetTitleSelectFlashingOff(void);	// 点滅処理(滅)
void StageTransition(void);				// ステージ遷移処理

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECTSOUNDBUFFER8	g_pTitleSelectSE;					// SE用バッファ
LPDIRECTSOUNDBUFFER8	g_pTitleBGM;						// BGM用バッファ

LPDIRECT3DTEXTURE9		g_D3DTextureTitleStart = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureTitleTutorial = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureTitleConfig = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureTitleEnd = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureTitleSelectLeft = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureTitleSelectRight = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_TitleStartVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_TitleTutorialVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_TitleConfigVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_TitleEndVertexWk[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_TitleSelectLeftVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_TitleSelectRightVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

int						g_TitleSelect;							// 選択肢

int						g_nTitleFlashingCount;					// 点滅用タイマー
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitleSelect(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_START_LOGO,						// ファイルの名前
		&g_D3DTextureTitleStart);				// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_TUTORIAL_LOGO,					// ファイルの名前
		&g_D3DTextureTitleTutorial);				// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_CONFIG_LOGO,						// ファイルの名前
		&g_D3DTextureTitleConfig);				// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_END_LOGO,						// ファイルの名前
		&g_D3DTextureTitleEnd);					// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_SELECT_LOGO_LEFT,				// ファイルの名前
		&g_D3DTextureTitleSelectLeft);			// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_SELECT_LOGO_RIGHT,				// ファイルの名前
		&g_D3DTextureTitleSelectRight);			// 読み込むメモリー

		// BGMロード
		g_pTitleBGM = LoadSound(TITLE_BGM);

		// SEロード
		g_pTitleSelectSE = LoadSound(SE_SELECT);
		
	}

	// 頂点フォーマット(スタート)
	MakeVtx4PointData(g_TitleStartVertexWk,										// 頂点情報格納ワーク
	D3DXVECTOR3(START_LOGO_POS_X, START_LOGO_POS_Y, START_LOGO_POS_Z),			// 座標X,Y,Z
	START_LOGO_SIZE_X, START_LOGO_SIZE_Y);										// サイズX,Y

	// 頂点フォーマット(チュートリアル)
	MakeVtx4PointData(g_TitleTutorialVertexWk,									// 頂点情報格納ワーク
	D3DXVECTOR3(TUTORIAL_LOGO_POS_X, TUTORIAL_LOGO_POS_Y, TUTORIAL_LOGO_POS_Z),	// 座標X,Y,Z
	TUTORIAL_LOGO_SIZE_X, TUTORIAL_LOGO_SIZE_Y);								// サイズX,Y

	// 頂点フォーマット(コンフィグ)
	MakeVtx4PointData(g_TitleConfigVertexWk,									// 頂点情報格納ワーク
	D3DXVECTOR3(CONFIG_LOGO_POS_X, CONFIG_LOGO_POS_Y, CONFIG_LOGO_POS_Z),		// 座標X,Y,Z
	CONFIG_LOGO_SIZE_X, CONFIG_LOGO_SIZE_Y);									// サイズX,Y

	// 頂点フォーマット(エンド)
	MakeVtx4PointData(g_TitleEndVertexWk,										// 頂点情報格納ワーク
	D3DXVECTOR3(END_LOGO_POS_X, END_LOGO_POS_Y, END_LOGO_POS_Z),				// 座標X,Y,Z
	END_LOGO_SIZE_X, END_LOGO_SIZE_Y);											// サイズX,Y

	// 頂点フォーマット(矢印)
	// 矢印→
	MakeVtx4PointData(g_TitleSelectLeftVertexWk,											// 頂点情報格納ワーク
	D3DXVECTOR3(START_LOGO_POS_X - SELECT_INTERVAL, START_LOGO_POS_Y, START_LOGO_POS_Z), 	// 座標X,Y,Z
	SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);												// サイズX,Y
	// 矢印←
	MakeVtx4PointData(g_TitleSelectRightVertexWk,											// 頂点情報格納ワーク
	D3DXVECTOR3(START_LOGO_POS_X + SELECT_INTERVAL, START_LOGO_POS_Y, START_LOGO_POS_Z),	// 座標X,Y,Z
	SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);												// サイズX,Y

	g_TitleSelect = TITLE_START;

	g_nTitleFlashingCount = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitleSelect(void)
{
	if (g_D3DTextureTitleStart != NULL)
	{// テクスチャの開放
		g_D3DTextureTitleStart->Release();
		g_D3DTextureTitleStart = NULL;
	}

	if (g_D3DTextureTitleTutorial != NULL)
	{// テクスチャの開放
		g_D3DTextureTitleTutorial->Release();
		g_D3DTextureTitleTutorial = NULL;
	}

	if (g_D3DTextureTitleConfig != NULL)
	{// テクスチャの開放
		g_D3DTextureTitleConfig->Release();
		g_D3DTextureTitleConfig = NULL;
	}

	if (g_D3DTextureTitleEnd != NULL)
	{// テクスチャの開放
		g_D3DTextureTitleEnd->Release();
		g_D3DTextureTitleEnd = NULL;
	}

	if (g_D3DTextureTitleSelectLeft != NULL)
	{// テクスチャの開放
		g_D3DTextureTitleSelectLeft->Release();
		g_D3DTextureTitleSelectLeft = NULL;
	}

	if (g_D3DTextureTitleSelectRight != NULL)
	{// テクスチャの開放
		g_D3DTextureTitleSelectRight->Release();
		g_D3DTextureTitleSelectRight = NULL;
	}

	if (g_pTitleSelectSE != NULL)
	{
		g_pTitleSelectSE->Release();
		g_pTitleSelectSE = NULL;
	}

	if (g_pTitleBGM != NULL)
	{
		g_pTitleBGM->Release();
		g_pTitleBGM = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitleSelect(void)
{
	// BGM再生
	PlaySound(g_pTitleBGM, E_DS8_FLAG_LOOP);

	g_nTitleFlashingCount++;

	ControlTitleSelect();		// 操作
	SetTitleSelectArrow();		// 矢印の移動
	SetTitleSelectFlashing();	// 点滅
	StageTransition();			// ステージ遷移
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitleSelect(void)
{
		DrawTitleSelectStart();			// 描画処理(スタート)
		DrawTitleSelectTutorial();		// 描画処理(チュートリアル)
		DrawTitleSelectConfig();		// 描画処理(コンフィグ)
		DrawTitleSelectEnd();			// 描画処理(エンド)
		DrawTitleSelectArrow();			// 描画処理(矢印)
}

//=============================================================================
// 描画処理(スタート)
//=============================================================================
void DrawTitleSelectStart(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTitleStart);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleStartVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(チュートリアル)
//=============================================================================
void DrawTitleSelectTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTitleTutorial);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleTutorialVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(コンフィグ)
//=============================================================================
void DrawTitleSelectConfig(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTitleConfig);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleConfigVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(エンド)
//=============================================================================
void DrawTitleSelectEnd(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTitleEnd);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleEndVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(矢印)
//=============================================================================
void DrawTitleSelectArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTitleSelectLeft);

	// 反射光の設定(全色)
	SetAllDiffuseData(g_TitleSelectLeftVertexWk, TITLE_SELECT_COLOR_RED);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleSelectLeftVertexWk, sizeof(VERTEX_2D));

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTitleSelectRight);

	// 反射光の設定(全色)
	SetAllDiffuseData(g_TitleSelectRightVertexWk, TITLE_SELECT_COLOR_RED);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleSelectRightVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 選択処理(キーボード操作&ゲームパット)
//=============================================================================
void ControlTitleSelect(void)
{
	if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W))
	{
		// SE再生
		g_pTitleSelectSE->SetCurrentPosition(0);
		PlaySound(g_pTitleSelectSE, E_DS8_FLAG_NONE);

		g_TitleSelect--;

		// 点滅処理(点)
		SetTitleSelectFlashingOn();
	}

	else if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S))
	{
		// SE再生
		g_pTitleSelectSE->SetCurrentPosition(0);
		PlaySound(g_pTitleSelectSE, E_DS8_FLAG_NONE);

		g_TitleSelect++;

		// 点滅処理(点)
		SetTitleSelectFlashingOn();
	}

	if (g_TitleSelect > TITLE_END)
	{
		g_TitleSelect = TITLE_START;
	}

	if (g_TitleSelect < TITLE_START)
	{
		g_TitleSelect = TITLE_END;
	}
}

//=============================================================================
// 選択処理(矢印)
//=============================================================================
void SetTitleSelectArrow(void)
{
	switch (g_TitleSelect)
	{
	case TITLE_START:
		// 矢印→
		SetVtx4PointData(
		g_TitleSelectLeftVertexWk,
		D3DXVECTOR3(START_LOGO_POS_X - SELECT_INTERVAL- SELECT_LOGO_SIZE_X, START_LOGO_POS_Y, START_LOGO_POS_Z),
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		// 矢印←
		SetVtx4PointData(
		g_TitleSelectRightVertexWk,
		D3DXVECTOR3(START_LOGO_SIZE_X + START_LOGO_POS_X + SELECT_INTERVAL, START_LOGO_POS_Y, START_LOGO_POS_Z), 
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		break;
	case TITLE_TUTORIAL:
		// 矢印→
		SetVtx4PointData(
		g_TitleSelectLeftVertexWk,
		D3DXVECTOR3(TUTORIAL_LOGO_POS_X - SELECT_INTERVAL - SELECT_LOGO_SIZE_X, TUTORIAL_LOGO_POS_Y, TUTORIAL_LOGO_POS_Z),
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		// 矢印←
		SetVtx4PointData(
		g_TitleSelectRightVertexWk,
		D3DXVECTOR3(TUTORIAL_LOGO_SIZE_X +TUTORIAL_LOGO_POS_X + SELECT_INTERVAL, TUTORIAL_LOGO_POS_Y, TUTORIAL_LOGO_POS_Z),
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		break;
	case TITLE_CONFIG:
		// 矢印→
		SetVtx4PointData(
		g_TitleSelectLeftVertexWk,
		D3DXVECTOR3(CONFIG_LOGO_POS_X - SELECT_INTERVAL - SELECT_LOGO_SIZE_X, CONFIG_LOGO_POS_Y, CONFIG_LOGO_POS_Z),
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		// 矢印←
		SetVtx4PointData(
		g_TitleSelectRightVertexWk,
		D3DXVECTOR3(CONFIG_LOGO_SIZE_X + CONFIG_LOGO_POS_X + SELECT_INTERVAL, CONFIG_LOGO_POS_Y, CONFIG_LOGO_POS_Z),
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		break;
	case TITLE_END:
		// 矢印→
		SetVtx4PointData(
		g_TitleSelectLeftVertexWk,
		D3DXVECTOR3(END_LOGO_POS_X - SELECT_INTERVAL - SELECT_LOGO_SIZE_X, END_LOGO_POS_Y, END_LOGO_POS_Z),
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		// 矢印←
		SetVtx4PointData(
		g_TitleSelectRightVertexWk,
		D3DXVECTOR3(END_LOGO_SIZE_X + END_LOGO_POS_X + SELECT_INTERVAL, END_LOGO_POS_Y, END_LOGO_POS_Z), 
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		break;
	}
}

//=============================================================================
// 選択処理(点滅)
//=============================================================================
void SetTitleSelectFlashing(void)
{
	if (g_nTitleFlashingCount < SELECT_FLASHING_HOLD_TIME)
	{
		SetTitleSelectFlashingOn();		// 点
	}

	if (g_nTitleFlashingCount > SELECT_FLASHING_HOLD_TIME)
	{
		SetTitleSelectFlashingOff();	// 滅
	}

	if (g_nTitleFlashingCount > SELECT_FLASHING_RESET)
	{
		g_nTitleFlashingCount = 0;		// リセット
	}
}

//=============================================================================
// 点滅処理(点)
//=============================================================================
void SetTitleSelectFlashingOn(void)
{
	// スタート
	SetAllDiffuseData(g_TitleStartVertexWk,
	SELECT_FLASHING_ALPHA_ON);
	// チュートリアル
	SetAllDiffuseData(g_TitleTutorialVertexWk,
	SELECT_FLASHING_ALPHA_ON);
	// コンフィグ
	SetAllDiffuseData(g_TitleConfigVertexWk,
	SELECT_FLASHING_ALPHA_ON);
	// エンド
	SetAllDiffuseData(g_TitleEndVertexWk,
	SELECT_FLASHING_ALPHA_ON);
}

//=============================================================================
// 点滅処理(滅)
//=============================================================================
void SetTitleSelectFlashingOff(void)
{
	switch (g_TitleSelect)
	{
	case TITLE_START:
		SetAllDiffuseData(g_TitleStartVertexWk,
		SELECT_FLASHING_ALPHA_OFF);
		break;

	case TITLE_TUTORIAL:
		SetAllDiffuseData(g_TitleTutorialVertexWk,
		SELECT_FLASHING_ALPHA_OFF);
		break;

	case TITLE_CONFIG:
		SetAllDiffuseData(g_TitleConfigVertexWk,
		SELECT_FLASHING_ALPHA_OFF);
		break;

	case TITLE_END:
		SetAllDiffuseData(g_TitleEndVertexWk,
		SELECT_FLASHING_ALPHA_OFF);
		break;
	}
}

//=============================================================================
// ステージ遷移処理
//=============================================================================
void StageTransition(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		switch (g_TitleSelect)
		{
		case TITLE_START:
			SetTitleSelectStage(STAGE_START_GAME);
			SetTitleManagerDrowFalg(false);
			SetDoorFlag(true);
			break;
		case TITLE_TUTORIAL:
			SetTitleSelectStage(STAGE_TUTORIAL);
			SetTitleManagerDrowFalg(false);
			SetDoorFlag(true);
			break;
		case TITLE_CONFIG:

			break;
		case TITLE_END:
			SetGameLoop(false);
			break;
		}
	}
}
