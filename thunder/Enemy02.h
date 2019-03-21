#ifndef _ENEMY_02_H_
#define _ENEMY_02_H_

#include "main.h"
#include "EnemyManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �G�l�~�[_02�摜
#define	TEXTURE_ENEMY_02			_T("data/TEXTURE/enemy B.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y		
#define ENEMY_02_SIZE_X					(80)	// �v���C���[�̕�(X)
#define ENEMY_02_SIZE_Y					(80)	// �v���C���[�̍���(Y)
// �G�l�~�[02���
#define ENEMY_02_HP_MAX					(100)
#define ENEMY_02_SPEED					(2)
#define ENEMY_02_START_POS_Y			(SCREEN_HEIGHT + ENEMY_02_SIZE_Y / HALF)				
#define ENEMY_02_MAX					(1)
#define ENEMY_02L_SPAWN_POS				D3DXVECTOR3(300.0f, -10.0f, 0.0f)	// �����ʒu
#define ENEMY_02R_SPAWN_POS				D3DXVECTOR3(580.0f, -10.0f, 0.0f)	// �����ʒu
#define ENEMY_02_STOP_POS_Y				(-1.6f)
#define ENEMY_02_STOP_TIME				(250)	// �X�N���[���Ɏ~�܂鎞��
#define ENEMY_02_EXP					(5)
#define ENEMY_02_SCORE					(50)
// �e���˗p
#define ENEMY_02_SHOOT_TIME				(3)	// ���ˊԊu
// �_�ŗp
#define ENEMY_02_FLASHING_ALPHA_ON		D3DCOLOR_RGBA(255, 255, 255, 255)	// �_�̏�Ԃ̃��l
#define ENEMY_02_FLASHING_ALPHA_OFF		D3DCOLOR_RGBA(255, 255, 255, 0)		// �ł̏�Ԃ̃��l
#define ENEMY_02_FLASHING_HOLD_TIME		(5)									// �_/�ł̏�Ԏ���
#define ENEMY_02_FLASHING_RESET			(ENEMY_02_FLASHING_HOLD_TIME*2)		// �_�Ń��Z�b�g
#define ENEMY_02_FLASHING_MAX			(1)									// �_�ł̉�
// ��]		 
#define ENEMY_02_SPIN_Z					(D3DXToRadian(90))					// ��]��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy02(int InitType);
void UninitEnemy02(void);
void UpdateEnemy02(float MapPos);
void DrawEnemy02(void);

ENEMY *GetEnemy02Left(int no);
ENEMY *GetEnemy02Right(int no);

#endif