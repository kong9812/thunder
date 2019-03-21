#ifndef _ENEMY_01_H_
#define _ENEMY_01_H_

#include "main.h"
#include "EnemyManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �G�l�~�[_01�摜
#define	TEXTURE_ENEMY_01			_T("data/TEXTURE/enemy A.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y		
#define ENEMY_01_SIZE_X					(80)	// �v���C���[�̕�(X)
#define ENEMY_01_SIZE_Y					(80)	// �v���C���[�̍���(Y)
// �G�l�~�[01���
#define ENEMY_01_HP_MAX					(10)
#define ENEMY_01_SPEED					(2)
#define ENEMY_01_START_POS_Y			(SCREEN_HEIGHT + ENEMY_01_SIZE_Y / HALF)				
#define ENEMY_01_MAX					(10)
#define ENEMY_01L_SPAWN_POS				D3DXVECTOR3(300.0f, -10.0f, 0.0f)	// �����ʒu
#define ENEMY_01R_SPAWN_POS				D3DXVECTOR3(580.0f, -10.0f, 0.0f)	// �����ʒu
#define ENEMY_01_STOP_POS_Y				(-0.2f)
#define ENEMY_01_STOP_TIME				(200)	// �X�N���[���Ɏ~�܂鎞��
#define ENEMY_01_SHOOT_TIME				(20)	// ���ˊԊu
#define ENEMY_01_EXP					(1)
#define ENEMY_01_SCORE					(10)
// �_�ŗp
#define ENEMY_01_FLASHING_ALPHA_ON		D3DCOLOR_RGBA(255, 255, 255, 255)	// �_�̏�Ԃ̃��l
#define ENEMY_01_FLASHING_ALPHA_OFF		D3DCOLOR_RGBA(255, 255, 255, 0)		// �ł̏�Ԃ̃��l
#define ENEMY_01_FLASHING_HOLD_TIME		(5)									// �_/�ł̏�Ԏ���
#define ENEMY_01_FLASHING_RESET			(ENEMY_01_FLASHING_HOLD_TIME*2)		// �_�Ń��Z�b�g
#define ENEMY_01_FLASHING_MAX			(1)									// �_�ł̉�
 // ��]
#define ENEMY_01_SPIN_Z					(0.01f)								// ��]��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy01(int InitType);
void UninitEnemy01(void);
void UpdateEnemy01(float MapPos);
void DrawEnemy01(void);

ENEMY *GetEnemy01Left(int no);
ENEMY *GetEnemy01Right(int no);

#endif