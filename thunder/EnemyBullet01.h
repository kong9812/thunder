#ifndef _ENEMY_BULLET_01_H_
#define _ENEMY_BULLET_01_H_

#include "main.h"
#include "EnemyBulletManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// BULLET_01�摜
#define	TEXTURE_ENEMY_BULLET_01		_T("data/TEXTURE/Enemy01Bullet.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y
#define ENEMY_BULLET_01_SIZE_X		(30)		// �e�̕�(X)
#define ENEMY_BULLET_01_SIZE_Y		(30)		// �e�̍���(Y)
// ���				   
#define ENEMY_BULLET_01_SPEED		(5)			// ���ˑ��x
#define ENEMY_BULLET_01_MAX			(10)		// ��ʏ㓯���ɕ`��ł���e�̐�
#define ENEMY_BULLET_01_ATK			(20)		// �U����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemyBullet01(int InitType);
void UninitEnemyBullet01(void);
void UpdateEnemyBullet01(void);
void DrawEnemyBullet01(void);

void SetEnemyBullet01(D3DXVECTOR3 EnemyPos);

ENEMYBULLET *GetEnemyBullet01(int no);

#endif