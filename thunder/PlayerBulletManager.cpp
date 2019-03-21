#include "main.h"
#include "player.h"
#include "PlayerBullet01.h"
#include "PlayerBullet02.h"
#include "PlayerBullet03.h"
#include "PlayerBulletManager.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerBulletManager(int InitType)
{
	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{	// ������
		InitPlayerBullet01(FIRST_INIT);
		InitPlayerBullet02(FIRST_INIT);
		InitPlayerBullet03(FIRST_INIT);
	}

	else
	{	// �ď�����
		InitPlayerBullet01(RE_INIT);
		InitPlayerBullet02(RE_INIT);
		InitPlayerBullet03(RE_INIT);
	}

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitPlayerBulletManager(void)
{
	UninitPlayerBullet01();
	UninitPlayerBullet02();
	UninitPlayerBullet03();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerBulletManager(void)
{
	UpdatePlayerBullet01();
	UpdatePlayerBullet02();
	UpdatePlayerBullet03();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerBulletManager(void)
{
	DrawPlayerBullet01();
	DrawPlayerBullet02();
	DrawPlayerBullet03();
}

//=============================================================================
// �o���b�g��ݒu
//=============================================================================
void SetPlayerBullet(D3DXVECTOR3 PlayerPos, int BulletPos)
{
	PLAYER *player = GetPlayer();

	if (player->Level == PLAYER_LEVEL_01)
	{
		SetPlayerBullet01(PlayerPos, BulletPos);
	}

	if (player->Level == PLAYER_LEVEL_02)
	{
		SetPlayerBullet02(PlayerPos, BulletPos);
	}

	if (player->Level == PLAYER_LEVEL_03)
	{
		SetPlayerBullet03(PlayerPos, BulletPos);
	}

	if (player->Level == PLAYER_LEVEL_04)
	{

	}
}