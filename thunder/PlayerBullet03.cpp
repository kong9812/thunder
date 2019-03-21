#include "main.h"
#include "basic.h"
#include "sound.h"
#include "PlayerBulletManager.h"
#include "PlayerBullet01.h"
#include "PlayerBullet03.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePlayerBullet03 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECTSOUNDBUFFER8	g_pPlayerBullet03SE;					// SE�p�o�b�t�@

VERTEX_2D				g_PlayerBullet03VertexWk[NUM_VERTEX];	// ���_���i�[���[�N

PLAYERBULLET			PlayerBullet03Wk[PLAYER_BULLET_03_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerBullet03(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *playerbullet03 = GetPlayerBullet03(0);

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PLAYER_BULLET_01,				// �t�@�C���̖��O
		&g_D3DTexturePlayerBullet03);			// �ǂݍ��ރ������[

		// SE���[�h
		g_pPlayerBullet03SE = LoadSound(SE_PLAYER_BULLET_01);
	}

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, playerbullet03++)
	{
		playerbullet03->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// �������WX,Y,Z
		playerbullet03->use = false;
	}

	// ���_�t�H�[�}�b�g(�X�^�[�g)
	MakeVtx4PointData(g_PlayerBullet03VertexWk,				// ���_���i�[���[�N
	D3DXVECTOR3(-100.0f, -100.0f, 0.0f), 				// �������WX,Y,Z
	PLAYER_BULLET_03_SIZE_X, PLAYER_BULLET_03_SIZE_Y);	// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerBullet03(void)
{
	if (g_D3DTexturePlayerBullet03 != NULL)
	{// �e�N�X�`���̊J��		 
		g_D3DTexturePlayerBullet03->Release();
		g_D3DTexturePlayerBullet03 = NULL;
	}

	if (g_pPlayerBullet03SE != NULL)
	{					
		g_pPlayerBullet03SE->Release();
		g_pPlayerBullet03SE = NULL;
	}					
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerBullet03(void)
{
	PLAYERBULLET *playerbullet03 = GetPlayerBullet03(0);

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, playerbullet03++)
	{
		if (playerbullet03->use == true)
		{
			playerbullet03->pos.y -= PLAYER_BULLET_03_SPEED;
		}

		if (playerbullet03->pos.y <= 0.0f - PLAYER_BULLET_03_SIZE_Y)
		{
			playerbullet03->use = false;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerBullet03(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *playerbullet03 = GetPlayerBullet03(0);

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, playerbullet03++)
	{
		if (playerbullet03->use == true)
		{
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_D3DTexturePlayerBullet03);

			// ���_���W�̐ݒ�(���_���)
			SetVtx4PointData(g_PlayerBullet03VertexWk, playerbullet03->pos, PLAYER_BULLET_03_SIZE_X, PLAYER_BULLET_03_SIZE_Y);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PlayerBullet03VertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// �o���b�g��ݒu
//=============================================================================
void SetPlayerBullet03(D3DXVECTOR3 PlayerPos, int BulletPos)
{
	PLAYERBULLET *playerbullet03 = GetPlayerBullet03(0);

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, playerbullet03++)
	{
		if (playerbullet03->use == false)
		{
			// SE�Đ�
			g_pPlayerBullet03SE->SetCurrentPosition(0);
			PlaySound(g_pPlayerBullet03SE, E_DS8_FLAG_NONE);

			playerbullet03->pos = PlayerPos;

			if (BulletPos == PLAYER_BULLET_LEFT)
			{
				playerbullet03->pos.x += PLAYER_BULLET_03_PLAYER_LEFT;
			}

			else if (BulletPos == PLAYER_BULLET_RIGHT)
			{
				playerbullet03->pos.x += PLAYER_BULLET_03_PLAYER_RIGHT;
			}

			else if (BulletPos == PLAYER_BULLET_MID)
			{
				playerbullet03->pos.x += PLAYER_BULLET_03_PLAYER_MID;
			}

			playerbullet03->use = true;

			break;
		}
	}
}

//=============================================================================
// �o���b�g�̏����擾
//=============================================================================
PLAYERBULLET *GetPlayerBullet03(int no)
{
	return&PlayerBullet03Wk[no];
}