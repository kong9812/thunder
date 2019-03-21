#ifndef _UI_NUMBER_EXP_H_
#define _UI_NUMBER_EXP_H_

#include "UI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UI_NUMBER_EXP_DIGIT			(1)			// ����
// ���W
#define  UI_NUMBER_EXP_POS_X		(1133.0f)	// �|���S���̏����ʒuX
#define  UI_NUMBER_EXP_POS_Y		(257.0f)	// ����
// ���
#define EXP_MAX						(9)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUINumberExp(int InitType);
void UninitUINumberExp(void);
void UpdateUINumberExp(void);
void DrawUINumberExp(void);

UINUMBER *GetExp(void);

#endif
