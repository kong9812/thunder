#include "main.h"
#include "Stage01Manager.h"
#include "TutorialManager.h"
#include "PauseBackground.h"
#include "PlayerBulletManager.h"
#include "PauseSelect.h"
#include "PauseUI.h"
#include "PauseManager.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPauseManager(int InitType)
{
	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{	// 初期化
		InitPauseBackground(FIRST_INIT);
		InitPauseUI(FIRST_INIT);
		InitPauseSelect(FIRST_INIT);
	}

	else
	{	// 再初期化
		InitPauseBackground(RE_INIT);
		InitPauseUI(RE_INIT);
		InitPauseSelect(RE_INIT);
	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitPauseManager(void)
{
	UninitPauseBackground();
	UninitPauseUI();
	UninitPauseSelect();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePauseManager(int STAGE)
{
	UpdatePauseBackground();
	UpdatePauseUI();
	UpdatePauseSelect(STAGE);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPauseManager(int STAGE)
{
	if (STAGE == STAGE_TUTORIAL)
	{
		DrawTutorialManager();
		DrawPauseBackground();
		DrawPauseUI();
		DrawPauseSelect();
	}

	else if (STAGE == STAGE_START_GAME)
	{
		DrawStage01Manager();
		DrawPauseBackground();
		DrawPauseUI();
		DrawPauseSelect();
	}
}