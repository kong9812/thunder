#ifndef _PLAYER_BULLET_01_H_
#define _PLAYER_BULLET_01_H_
						
#include "main.h"
#include "PlayerBulletManager.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// BULLET_01�摜
#define	TEXTURE_PLAYER_BULLET_01		_T("data/TEXTURE/PlayerBullet02.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y
#define PLAYER_BULLET_01_SIZE_X			(10)		// �e�̕�(X)
#define PLAYER_BULLET_01_SIZE_Y			(24)		// �e�̍���(Y)
// ���				   
#define PLAYER_BULLET_01_SPEED			(20)		// ���ˑ��x
#define PLAYER_BULLET_01_MAX			(50)		// ��ʏ㓯���ɕ`��ł���e�̐�
#define PLAYER_BULLET_01_ATK			(20)		// �U����
// ������				
#define PLAYER_BULLET_01_PLAYER_MID		((PLAYER_SIZE_X*0.55f)-(PLAYER_BULLET_01_SIZE_X/HALF))	// �v���C���[�ƌ덷

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerBullet01(int InitType);
void UninitPlayerBullet01(void);
void UpdatePlayerBullet01(void);
void DrawPlayerBullet01(void);

void SetPlayerBullet01(D3DXVECTOR3 PlayerPos, int BulletPos);

PLAYERBULLET *GetPlayerBullet01(int no);

#endif