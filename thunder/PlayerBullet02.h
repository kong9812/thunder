#ifndef _PLAYER_BULLET_02_H_
#define _PLAYER_BULLET_02_H_

#include "main.h"
#include "PlayerBulletManager.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �T�C�Y
#define PLAYER_BULLET_02_SIZE_X			(10)		// �e�̕�(X)
#define PLAYER_BULLET_02_SIZE_Y			(24)		// �e�̍���(Y)
// ���				 
#define PLAYER_BULLET_02_SPEED			(20)		// ���ˑ��x
#define PLAYER_BULLET_02_MAX			(50)		// ��ʏ㓯���ɕ`��ł���e�̐�
#define PLAYER_BULLET_02_ATK			(10)		// �U����
// ������				
#define PLAYER_BULLET_02_PLAYER_LEFT	(PLAYER_SIZE_X*0.5-PLAYER_BULLET_02_SIZE_X/HALF)	// �v���C���[�ƌ덷
#define PLAYER_BULLET_02_PLAYER_RIGHT	(PLAYER_SIZE_X*0.5+PLAYER_BULLET_02_SIZE_X/HALF)	// �v���C���[�ƌ덷

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerBullet02(int InitType);
void UninitPlayerBullet02(void);
void UpdatePlayerBullet02(void);
void DrawPlayerBullet02(void);

void SetPlayerBullet02(D3DXVECTOR3 PlayerPos, int BulletPos);

PLAYERBULLET *GetPlayerBullet02(int no);

#endif