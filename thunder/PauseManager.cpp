#include "main.h"
#include "Stage01Manager.h"
#include "TutorialManager.h"
#include "PauseBackground.h"
#include "PlayerBulletManager.h"
#include "PauseSelect.h"
#include "PauseUI.h"
#include "PauseManager.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPauseManager(int InitType)
{
	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{	// ������
		InitPauseBackground(FIRST_INIT);
		InitPauseUI(FIRST_INIT);
		InitPauseSelect(FIRST_INIT);
	}

	else
	{	// �ď�����
		InitPauseBackground(RE_INIT);
		InitPauseUI(RE_INIT);
		InitPauseSelect(RE_INIT);
	}

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitPauseManager(void)
{
	UninitPauseBackground();
	UninitPauseUI();
	UninitPauseSelect();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePauseManager(int STAGE)
{
	UpdatePauseBackground();
	UpdatePauseUI();
	UpdatePauseSelect(STAGE);
}

//=============================================================================
// �`�揈��
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