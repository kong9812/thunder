#include "main.h"
#include "basic.h"
#include "sound.h"
#include "PlayerBulletManager.h"
#include "PlayerBullet01.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePlayerBullet01 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECTSOUNDBUFFER8	g_pPlayerBullet01SE;					// SE�p�o�b�t�@

VERTEX_2D				g_PlayerBullet01VertexWk[NUM_VERTEX];	// ���_���i�[���[�N

PLAYERBULLET			PlayerBullet01Wk[PLAYER_BULLET_01_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerBullet01(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *playerbullet01 = GetPlayerBullet01(0);

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PLAYER_BULLET_01,				// �t�@�C���̖��O
		&g_D3DTexturePlayerBullet01);			// �ǂݍ��ރ������[

													// SE���[�h
		g_pPlayerBullet01SE = LoadSound(SE_PLAYER_BULLET_01);
	}

	for (int i = 0; i < PLAYER_BULLET_01_MAX; i++, playerbullet01++)
	{
		playerbullet01->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// �������WX,Y,Z
		playerbullet01->use = false;
	}

	// ���_�t�H�[�}�b�g(�X�^�[�g)
	MakeVtx4PointData(g_PlayerBullet01VertexWk,			// ���_���i�[���[�N
	D3DXVECTOR3(-100.0f, -100.0f, 0.0f), 				// �������WX,Y,Z
	PLAYER_BULLET_01_SIZE_X, PLAYER_BULLET_01_SIZE_Y);	// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerBullet01(void)
{
	if (g_D3DTexturePlayerBullet01 != NULL)
	{// �e�N�X�`���̊J��		 
		g_D3DTexturePlayerBullet01->Release();
		g_D3DTexturePlayerBullet01 = NULL;
	}

	if (g_pPlayerBullet01SE != NULL)
	{					
		g_pPlayerBullet01SE->Release();
		g_pPlayerBullet01SE = NULL;
	}					
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerBullet01(void)
{
	PLAYERBULLET *playerbullet01 = GetPlayerBullet01(0);

	for (int i = 0; i < PLAYER_BULLET_01_MAX; i++, playerbullet01++)
	{
		if (playerbullet01->use == true)
		{
			playerbullet01->pos.y -= PLAYER_BULLET_01_SPEED;
		}

		if (playerbullet01->pos.y <= 0.0f - PLAYER_BULLET_01_SIZE_Y)
		{
			playerbullet01->use = false;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerBullet01(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *playerbullet01 = GetPlayerBullet01(0);

	for (int i = 0; i < PLAYER_BULLET_01_MAX; i++, playerbullet01++)
	{
		if (playerbullet01->use == true)
		{
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_D3DTexturePlayerBullet01);

			// ���_���W�̐ݒ�(���_���)
			SetVtx4PointData(g_PlayerBullet01VertexWk, playerbullet01->pos, PLAYER_BULLET_01_SIZE_X, PLAYER_BULLET_01_SIZE_Y);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PlayerBullet01VertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// �o���b�g��ݒu
//=============================================================================
void SetPlayerBullet01(D3DXVECTOR3 PlayerPos, int BulletPos)
{
	PLAYERBULLET *playerbullet01 = GetPlayerBullet01(0);

	for (int i = 0; i < PLAYER_BULLET_01_MAX; i++, playerbullet01++)
	{
		if (playerbullet01->use == false)
		{
			playerbullet01->pos = PlayerPos;

			if (BulletPos == PLAYER_BULLET_MID)
			{
				// SE�Đ�
				g_pPlayerBullet01SE->SetCurrentPosition(0);
				PlaySound(g_pPlayerBullet01SE, E_DS8_FLAG_NONE);
				playerbullet01->pos.x += PLAYER_BULLET_01_PLAYER_MID;
			}

			else if ((BulletPos == PLAYER_BULLET_LEFT) ||
					(BulletPos == PLAYER_BULLET_RIGHT))continue;

			playerbullet01->use = true;

			break;
		}
	}
}

//=============================================================================
// �o���b�g�̏����擾
//=============================================================================
PLAYERBULLET *GetPlayerBullet01(int no)
{
	return&PlayerBullet01Wk[no];
}
