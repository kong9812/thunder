#ifndef _PLAYER_BULLET_MANAGER_H_
#define _PLAYER_BULLET_MANAGER_H_

#include "main.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ���
#define PLAYER_BULLET_SHOOT_TIME		(10)		// ���ˊԊu

//*****************************************************************************
// �萔��`(enum��`)
//*****************************************************************************
enum E_PLAYERBULLET		// �v���C���[�o���b�g�萔
{
	PLAYER_BULLET_01,
	PLAYER_BULLET_02,
	PLAYER_BULLET_03,
	PLAYER_BULLET_04
};

enum E_PLAYERBULLET_POS	// �v���C���[�o���b�g�ʒu�萔
{
	PLAYER_BULLET_LEFT,
	PLAYER_BULLET_RIGHT,
	PLAYER_BULLET_MID
};

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// �v���C���[�o���b�g�\����
{
	D3DXVECTOR3		pos;			// �o���b�g�̍��W

	int				type;			// �o���b�g�^

	bool			use;			// true:�g�p�� false:�g�p���Ă��Ȃ�
}PLAYERBULLET;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerBulletManager(int InitType);
void UninitPlayerBulletManager(void);
void UpdatePlayerBulletManager(void);
void DrawPlayerBulletManager(void);

void SetPlayerBullet(D3DXVECTOR3 PlayerPos, int BulletPos);
#endif