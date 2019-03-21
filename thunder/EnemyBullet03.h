#ifndef _ENEMY_BULLET_03_H_
#define _ENEMY_BULLET_03_H_

#include "main.h"
#include "EnemyBulletManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �T�C�Y
#define ENEMY_BULLET_03_SIZE_X		(30)		// �e�̕�(X)
#define ENEMY_BULLET_03_SIZE_Y		(30)		// �e�̍���(Y)
// ���				   
#define ENEMY_BULLET_03_SPEED		(3)			// ���ˑ��x
#define ENEMY_BULLET_03_MAX			(50)		// ��ʏ㓯���ɕ`��ł���e�̐�
#define ENEMY_BULLET_03_ATK			(20)		// �U����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemyBullet03(int InitType);
void UninitEnemyBullet03(void);
void UpdateEnemyBullet03(void);
void DrawEnemyBullet03(void);

void SetEnemyBullet03(D3DXVECTOR3 EnemyPos);

ENEMYBULLET *GetEnemyBullet03(int no);

#endif