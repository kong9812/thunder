#include "main.h"
#include "basic.h"
#include "sound.h"
#include "PlayerBulletManager.h"
#include "PlayerBullet01.h"
#include "PlayerBullet02.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePlayerBullet02 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECTSOUNDBUFFER8		g_pPlayerBullet02SE;						// SE�p�o�b�t�@

VERTEX_2D				g_PlayerBullet02VertexWk[NUM_VERTEX];	// ���_���i�[���[�N

PLAYERBULLET				PlayerBullet02Wk[PLAYER_BULLET_02_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerBullet02(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *playerbullet02 = GetPlayerBullet02(0);

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PLAYER_BULLET_01,				// �t�@�C���̖��O
		&g_D3DTexturePlayerBullet02);			// �ǂݍ��ރ������[

		// SE���[�h
		g_pPlayerBullet02SE = LoadSound(SE_PLAYER_BULLET_01);
	}

	for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet02++)
	{
		playerbullet02->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// �������WX,Y,Z
		playerbullet02->use = false;
	}

	// ���_�t�H�[�}�b�g(�X�^�[�g)
	MakeVtx4PointData(g_PlayerBullet02VertexWk,			// ���_���i�[���[�N
	D3DXVECTOR3(-100.0f, -100.0f, 0.0f), 				// �������WX,Y,Z
	PLAYER_BULLET_02_SIZE_X, PLAYER_BULLET_02_SIZE_Y);	// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerBullet02(void)
{
	if (g_D3DTexturePlayerBullet02 != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTexturePlayerBullet02->Release();
		g_D3DTexturePlayerBullet02 = NULL;
	}

	if (g_pPlayerBullet02SE != NULL)
	{
		g_pPlayerBullet02SE->Release();
		g_pPlayerBullet02SE = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerBullet02(void)
{
	PLAYERBULLET *playerbullet02 = GetPlayerBullet02(0);

	for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet02++)
	{
		if (playerbullet02->use == true)
		{
			playerbullet02->pos.y -= PLAYER_BULLET_02_SPEED;
		}

		if (playerbullet02->pos.y <= 0.0f - PLAYER_BULLET_02_SIZE_Y)
		{
			playerbullet02->use = false;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerBullet02(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *playerbullet02 = GetPlayerBullet02(0);

	for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet02++)
	{
		if (playerbullet02->use == true)
		{
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_D3DTexturePlayerBullet02);

			// ���_���W�̐ݒ�(���_���)
			SetVtx4PointData(g_PlayerBullet02VertexWk, playerbullet02->pos, PLAYER_BULLET_02_SIZE_X, PLAYER_BULLET_02_SIZE_Y);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PlayerBullet02VertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// �o���b�g��ݒu
//=============================================================================
void SetPlayerBullet02(D3DXVECTOR3 PlayerPos, int BulletPos)
{
	PLAYERBULLET *playerbullet02 = GetPlayerBullet02(0);

	for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet02++)
	{
		if (playerbullet02->use == false)
		{
			playerbullet02->pos = PlayerPos;

			if (BulletPos == PLAYER_BULLET_LEFT)
			{
				// SE�Đ�
				g_pPlayerBullet02SE->SetCurrentPosition(0);
				PlaySound(g_pPlayerBullet02SE, E_DS8_FLAG_NONE);
				playerbullet02->pos.x += PLAYER_BULLET_02_PLAYER_LEFT;
			}

			else if (BulletPos == PLAYER_BULLET_RIGHT)
			{
				// SE�Đ�
				g_pPlayerBullet02SE->SetCurrentPosition(0);
				PlaySound(g_pPlayerBullet02SE, E_DS8_FLAG_NONE);
				playerbullet02->pos.x += PLAYER_BULLET_02_PLAYER_RIGHT;
			}

			else if (BulletPos == PLAYER_BULLET_MID)continue;

			playerbullet02->use = true;

			break;
		}
	}
}

//=============================================================================
// �o���b�g�̏����擾
//=============================================================================
PLAYERBULLET *GetPlayerBullet02(int no)
{
	return&PlayerBullet02Wk[no];
}
