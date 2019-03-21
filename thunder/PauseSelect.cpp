#include "main.h"
#include "basic.h"
#include "input.h"
#include "sound.h"
#include "PauseSelect.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// 描画処理
void DrawPauseSelectReutrnToGame(void);	// ReturnToGameの描画処理
void DrawPauseSelectBackToTittle(void);	// BackToTittleの描画処理
void DrawPauseSelectQuitGame(void);		// QuitGameの描画処理

// 更新処理
void ControlPauseSelect(void);			// 選択処理(キーボード操作&ゲームパット)
void SetPauseSelectDiffuse(void);		// 色反転処理
void StagePauseTransition(int STAGE);	// 画面遷移

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECTSOUNDBUFFER8	g_pPauseSelectSE;							// SE用バッファ

LPDIRECT3DTEXTURE9		g_D3DTexturePauseReturnToGame = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTexturePauseBackToTittle = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTexturePauseQuitGame = NULL;			// テクスチャへのポインタ

VERTEX_2D				g_PauseReturnToGameVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_PauseBackToTittleVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_PauseQuitGameVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

int						g_PauseSelect;								// 選択肢

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPauseSelect(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_PAUSE_RETURNTOGAME,				// ファイルの名前
		&g_D3DTexturePauseReturnToGame);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_PAUSE_BACKTOTITTLE,				// ファイルの名前
		&g_D3DTexturePauseBackToTittle);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_PAUSE_QUITGAME,					// ファイルの名前
		&g_D3DTexturePauseQuitGame);			// 読み込むメモリー



		// SEロード
		g_pPauseSelectSE = LoadSound(SE_SELECT);
	}

	g_PauseSelect = PAUSE_RETURN_TO_GAME;

	// 頂点フォーマット(ReturnToGame)
	MakeVtx4PointData(g_PauseReturnToGameVertexWk,							// 頂点情報格納ワーク
	D3DXVECTOR3(PAUSE_RETURNTOGAME_POS_X, PAUSE_RETURNTOGAME_POS_Y, 0.0f),	// 座標X,Y,Z
	PAUSE_RETURNTOGAME_SIZE_X, PAUSE_RETURNTOGAME_SIZE_Y);					// サイズX,Y

	// 頂点フォーマット(BackToTittle)
	MakeVtx4PointData(g_PauseBackToTittleVertexWk,							// 頂点情報格納ワーク
	D3DXVECTOR3(PAUSE_BACKTOTITTLE_POS_X, PAUSE_BACKTOTITTLE_POS_Y, 0.0f),	// 座標X,Y,Z
	PAUSE_BACKTOTITTLE_SIZE_X, PAUSE_BACKTOTITTLE_SIZE_Y);					// サイズX,Y

	// 頂点フォーマット(QuitGame)
	MakeVtx4PointData(g_PauseQuitGameVertexWk,								// 頂点情報格納ワーク
	D3DXVECTOR3(PAUSE_QUITGAME_POS_X, PAUSE_QUITGAME_POS_Y, 0.0f),			// 座標X,Y,Z
	PAUSE_QUITGAME_SIZE_X, PAUSE_QUITGAME_SIZE_Y);							// サイズX,Y

	return S_OK;

}

//=============================================================================
// 終了処理
//==============================================================================
void UninitPauseSelect(void)
{
	if (g_D3DTexturePauseReturnToGame != NULL)
	{// テクスチャの開放
		g_D3DTexturePauseReturnToGame->Release();
		g_D3DTexturePauseReturnToGame = NULL;
	}

	if (g_D3DTexturePauseBackToTittle != NULL)
	{// テクスチャの開放
		g_D3DTexturePauseBackToTittle->Release();
		g_D3DTexturePauseBackToTittle = NULL;
	}

	if (g_D3DTexturePauseQuitGame != NULL)
	{// テクスチャの開放
		g_D3DTexturePauseQuitGame->Release();
		g_D3DTexturePauseQuitGame = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePauseSelect(int STAGE)
{
	ControlPauseSelect();
	StagePauseTransition(STAGE);
	SetPauseSelectDiffuse();

}

//=============================================================================
// 選択処理(キーボード操作&ゲームパット)
//=============================================================================
void ControlPauseSelect(void)
{
	if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W))
	{
		// SE再生
		g_pPauseSelectSE->SetCurrentPosition(0);
		PlaySound(g_pPauseSelectSE, E_DS8_FLAG_NONE);

		g_PauseSelect--;
	}

	else if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S))
	{
		// SE再生
		g_pPauseSelectSE->SetCurrentPosition(0);
		PlaySound(g_pPauseSelectSE, E_DS8_FLAG_NONE);

		g_PauseSelect++;
	}

	if (g_PauseSelect > PAUSE_QUIT_GAME)
	{
		g_PauseSelect = PAUSE_RETURN_TO_GAME;
	}

	if (g_PauseSelect < PAUSE_RETURN_TO_GAME)
	{
		g_PauseSelect = PAUSE_QUIT_GAME;
	}
}

//=============================================================================
// 色反転処理
//=============================================================================
void SetPauseSelectDiffuse(void)
{
	switch (g_PauseSelect)
	{
	case PAUSE_RETURN_TO_GAME:
		// 反射光の設定(全色)
		SetAllDiffuseData(g_PauseReturnToGameVertexWk, PAUSE_SELECT_RGBA);
		// 反射光の設定(全色)
		SetAllDiffuseData(g_PauseBackToTittleVertexWk, PAUSE_NTSELECT_RGBA);
		// 反射光の設定(全色)
		SetAllDiffuseData(g_PauseQuitGameVertexWk, PAUSE_NTSELECT_RGBA); 
		break;
	case PAUSE_BACK_TO_TITLE:
		// 反射光の設定(全色)
		SetAllDiffuseData(g_PauseBackToTittleVertexWk, PAUSE_SELECT_RGBA);
		// 反射光の設定(全色)
		SetAllDiffuseData(g_PauseReturnToGameVertexWk, PAUSE_NTSELECT_RGBA);
		// 反射光の設定(全色)
		SetAllDiffuseData(g_PauseQuitGameVertexWk, PAUSE_NTSELECT_RGBA);
		break;
	case PAUSE_QUIT_GAME:
		// 反射光の設定(全色)
		SetAllDiffuseData(g_PauseQuitGameVertexWk, PAUSE_SELECT_RGBA);
		// 反射光の設定(全色)
		SetAllDiffuseData(g_PauseReturnToGameVertexWk, PAUSE_NTSELECT_RGBA);
		// 反射光の設定(全色)
		SetAllDiffuseData(g_PauseBackToTittleVertexWk, PAUSE_NTSELECT_RGBA);
		break;
	}
}

//=============================================================================
// ステージ遷移処理
//=============================================================================
void StagePauseTransition(int STAGE)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		switch (g_PauseSelect)
		{
		case PAUSE_RETURN_TO_GAME:
			SetStage(STAGE);
			break;
		case PAUSE_BACK_TO_TITLE:
			SetStage(STAGE_TITLE);
			InitGame();
			break;
		case PAUSE_QUIT_GAME:
			SetGameLoop(false);
			break;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPauseSelect(void)
{
	DrawPauseSelectReutrnToGame();
	DrawPauseSelectBackToTittle();
	DrawPauseSelectQuitGame();
}

//=============================================================================
// 描画処理(ReturnToGame)
//=============================================================================
void DrawPauseSelectReutrnToGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTexturePauseReturnToGame);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PauseReturnToGameVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(BackToTittle)
//=============================================================================
void DrawPauseSelectBackToTittle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTexturePauseBackToTittle);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PauseBackToTittleVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(QuitGame)
//=============================================================================
void DrawPauseSelectQuitGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTexturePauseQuitGame);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PauseQuitGameVertexWk, sizeof(VERTEX_2D));
}