#ifndef _TUTORIAL_ENEMY_H_
#define _TUTORIAL_ENEMY_H_

#include "Enemy01.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �`���g���A���G�l�~�[�̏��
#define TUTORIAL_ENEMY_SPAWN_POS		D3DXVECTOR3(300.0f, -10.0f, 0.0f) // �����ʒu
#define TUTORIAL_ENEMY_STOP_POS_Y		(-0.2f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTutorialEnemy(int InitType);
void UninitTutorialEnemy(void);
void UpdateTutorialEnemy(float MapPos);
void DrawTutorialEnemy(void);
ENEMY *GetTutorialEnemy(void);

#endif