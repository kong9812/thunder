#ifndef _ENEMY_03_H_
#define _ENEMY_03_H_

#include "main.h"
#include "EnemyManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �G�l�~�[_03�摜
#define	TEXTURE_ENEMY_03			_T("data/TEXTURE/enemy C.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y		
#define ENEMY_03_SIZE_X					(390)	// �G�l�~�[�̕�(X)
#define ENEMY_03_SIZE_Y					(226)	// �G�l�~�[�̍���(Y)
// �G�l�~�[02���
#define ENEMY_03_HP_MAX					(10000)
#define ENEMY_03_SPEED					(2)
#define ENEMY_03_START_POS_Y				(SCREEN_HEIGHT + ENEMY_03_SIZE_Y / HALF)				
#define ENEMY_03_SPAWN_POS				D3DXVECTOR3(480.0f, -10.0f, 0.0f)	// �����ʒu
#define ENEMY_03_STOP_POS_Y				(-3.0f)
#define ENEMY_03_EXP						(10)
#define ENEMY_03_SCORE					(100)
#define ENEMY_03_SHOOT_01_TIME			(20)
#define ENEMY_03_SHOOT_02_TIME			(40)
#define ENEMY_03_SHOOT_03_TIME			(5)
// �_�ŗp		
#define ENEMY_03_FLASHING_ALPHA_ON		D3DCOLOR_RGBA(255, 255, 255, 255)	// �_�̏�Ԃ̃��l
#define ENEMY_03_FLASHING_ALPHA_OFF		D3DCOLOR_RGBA(255, 255, 255, 0)		// �ł̏�Ԃ̃��l
#define ENEMY_03_FLASHING_HOLD_TIME		(5)									// �_/�ł̏�Ԏ���
#define ENEMY_03_FLASHING_RESET			(ENEMY_03_FLASHING_HOLD_TIME*2)		// �_�Ń��Z�b�g
#define ENEMY_03_FLASHING_MAX			(1)									// �_�ł̉�
// ��]		   
#define ENEMY_03_SPIN_Z					(D3DXToRadian(90))					// ��]��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy03(int InitType);
void UninitEnemy03(void);
void UpdateEnemy03(float MapPos);
void DrawEnemy03(void);

ENEMY *GetEnemy03();

#endif