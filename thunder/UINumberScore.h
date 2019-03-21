#ifndef _UI_NUMBER_SCORE_H_
#define _UI_NUMBER_SCORE_H_

#include "UI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UI_NUMBER_SCORE_DIGIT			(5)			// ����
// ���W
#define  UI_NUMBER_SCORE_POS_X			(1100.0f)	// �|���S���̏����ʒuX
#define  UI_NUMBER_SCORE_POS_Y			(100.0f)	// ����
// ���
#define SCORE_MAX						(99999)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUINumberScore(int InitType);
void UninitUINumberScore(void);
void UpdateUINumberScore(void);
void DrawUINumberScore(void);

UINUMBER *GetScore(void);

void AddScore(int value);


#endif
