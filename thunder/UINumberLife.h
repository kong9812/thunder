#ifndef _UI_NUMBER_LIFE_H_
#define _UI_NUMBER_LIFE_H_

#include "UI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UI_NUMBER_LIFE_DIGIT			(1)			// ����
// ���W
#define  UI_NUMBER_LIFE_POS_X		(1133.0f)	// �|���S���̏����ʒuX
#define  UI_NUMBER_LIFE_POS_Y		(157.0f)	// ����
// ���
#define LIFE_MAX						(9)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUINumberLife(int InitType);
void UninitUINumberLife(void);
void UpdateUINumberLife(void);
void DrawUINumberLife(void);

UINUMBER *GetLife(void);

#endif
