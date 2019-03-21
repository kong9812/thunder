#ifndef _PAUSE_UI_H_
#define _PAUSE_UI_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �|�[�YUI�摜
#define	TEXTURE_PAUSE_UI		_T("data/TEXTURE/PauseMenu.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y
#define PAUSE_UI_SIZE_X			(359)	// �|�[�YUI�̕�(X)
#define PAUSE_UI_SIZE_Y			(359)	// �|�[�YUI�̍���(Y)
// ���W
#define PAUSE_UI_POS_X			(SCREEN_WIDTH/HALF-PAUSE_UI_SIZE_X/HALF)	
#define PAUSE_UI_POS_Y			(SCREEN_HEIGHT/HALF-PAUSE_UI_SIZE_Y/HALF)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPauseUI(int InitType);
void UninitPauseUI(void);
void UpdatePauseUI(void);
void DrawPauseUI(void);

#endif