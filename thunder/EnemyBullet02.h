#ifndef _ENEMY_BULLET_02_H_
#define _ENEMY_BULLET_02_H_

#include "main.h"
#include "EnemyBulletManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �T�C�Y
#define ENEMY_BULLET_02_SIZE_X		(30)		// �e�̕�(X)
#define ENEMY_BULLET_02_SIZE_Y		(30)		// �e�̍���(Y)
// ���				   
#define ENEMY_BULLET_02_SPEED		(3)			// ���ˑ��x
#define ENEMY_BULLET_02_MAX			(50)		// ��ʏ㓯���ɕ`��ł���e�̐�
#define ENEMY_BULLET_02_ATK			(20)		// �U����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemyBullet02(int InitType);
void UninitEnemyBullet02(void);
void UpdateEnemyBullet02(void);
void DrawEnemyBullet02(void);

void SetEnemyBullet02(D3DXVECTOR3 EnemyPos);

ENEMYBULLET *GetEnemyBullet02(int no);

#endif