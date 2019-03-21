#ifndef _PLAYER_BULLET_03_H_
#define _PLAYER_BULLET_03_H_

#include "main.h"
#include "PlayerBulletManager.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �T�C�Y
#define PLAYER_BULLET_03_SIZE_X			(10)		// �e�̕�(X)
#define PLAYER_BULLET_03_SIZE_Y			(24)		// �e�̍���(Y)
// ���
#define PLAYER_BULLET_03_SPEED			(20)		// ���ˑ��x
#define PLAYER_BULLET_03_MAX			(50)		// ��ʏ㓯���ɕ`��ł���e�̐�
#define PLAYER_BULLET_03_ATK			(10)		// �U����
// ������				
#define PLAYER_BULLET_03_PLAYER_LEFT	(PLAYER_SIZE_X*0.25f+PLAYER_BULLET_03_SIZE_X/HALF)	// �v���C���[�ƌ덷
#define PLAYER_BULLET_03_PLAYER_RIGHT	(PLAYER_SIZE_X*0.75f-PLAYER_BULLET_03_SIZE_X/HALF)	// �v���C���[�ƌ덷
#define PLAYER_BULLET_03_PLAYER_MID		(PLAYER_SIZE_X*0.55f-PLAYER_BULLET_03_SIZE_X/HALF)	// �v���C���[�ƌ덷

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerBullet03(int InitType);
void UninitPlayerBullet03(void);
void UpdatePlayerBullet03(void);
void DrawPlayerBullet03(void);

void SetPlayerBullet03(D3DXVECTOR3 PlayerPos, int BulletPos);

PLAYERBULLET *GetPlayerBullet03(int no);


#endif