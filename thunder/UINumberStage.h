#ifndef _UI_NUMBER_STAGE_H_
#define _UI_NUMBER_STAGE_H_

#include "UI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UI_NUMBER_STAGE_DIGIT			(1)			// ����
// ���W
#define  UI_NUMBER_STAGE_POS_X			(1190.0f)	// �|���S���̏����ʒuX
#define  UI_NUMBER_STAGE_POS_Y			(357.0f)		// ����
// ���
#define STAGE_MAX						(9)

enum STAGE_NUM
{
	STAGE_0,
	STAGE_1,
	STAGE_2,
	STAGE_3
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUINumberStage(int InitType);
void UninitUINumberStage(void);
void UpdateUINumberStage(float MapPos);
void DrawUINumberStage(void);

UINUMBER *GetStage(void);

#endif
