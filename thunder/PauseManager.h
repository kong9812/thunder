#ifndef _PAUSE_MANAGER_H_
#define _PAUSE_MANAGER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPauseManager(int InitType);
void UninitPauseManager(void);
void UpdatePauseManager(int STAGE);
void DrawPauseManager(int STAGE);

#endif