#ifndef _UI_NUMBER_BOMB_H_
#define _UI_NUMBER_BOMB_H_

#include "UI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UI_NUMBER_BOMB_DIGIT			(1)			// ����
// ���W
#define  UI_NUMBER_BOMB_POS_X		(1178.0f)	// �|���S���̏����ʒuX
#define  UI_NUMBER_BOMB_POS_Y		(207.0f)	// ����
// ���
#define BOMB_MAX						(9)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUINumberBomb(int InitType);
void UninitUINumberBomb(void);
void UpdateUINumberBomb(void);
void DrawUINumberBomb(void);

UINUMBER *GetBomb(void);

#endif
