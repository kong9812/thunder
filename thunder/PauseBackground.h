#ifndef _PAUSE_BACKGROUND_H_
#define _PAUSE_BACKGROUND_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �|�[�Y�w�i
// ���ˌ�
#define	TITLE_NAME_COLOR_GRAY		D3DCOLOR_RGBA(128,128,128,128)		// �|�[�Y��ʂ̔��ˌ�(�D)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPauseBackground(int InitType);
void UninitPauseBackground(void);
void UpdatePauseBackground(void);
void DrawPauseBackground(void);

#endif