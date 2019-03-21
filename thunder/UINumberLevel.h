#ifndef _UI_NUMBER_LEVEL_H_
#define _UI_NUMBER_LEVEL_H_

#include "UI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UI_NUMBER_LEVEL_DIGIT			(1)			// ����
// ���W
#define  UI_NUMBER_LEVEL_POS_X		(1187.0f)	// �|���S���̏����ʒuX
#define  UI_NUMBER_LEVEL_POS_Y		(310.0f)	// ����
// ���
#define LEVEL_MAX						(9)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUINumberLevel(int InitType);
void UninitUINumberLevel(void);
void UpdateUINumberLevel(void);
void DrawUINumberLevel(void);

UINUMBER *GetLevel(void);

#endif
