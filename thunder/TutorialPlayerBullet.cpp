#include "main.h"
#include "basic.h"
#include "PlayerBulletManager.h"
#include "PlayerBullet01.h"
#include "sound.h"
#include"TutorialPlayerBullet.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialPlayerBullet = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECTSOUNDBUFFER8	g_pTutorialPlayerBullet01SE;					// SE�p�o�b�t�@

VERTEX_2D				g_TutorialPlayerBulletVertexWk[NUM_VERTEX];		// ���_���i�[���[�N

PLAYERBULLET			TutorialPlayerBulletWk[PLAYER_BULLET_03_MAX];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitTutorialPlayerBullet(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *tutorialplayerbullet = GetTutorialPlayerBullet(0);

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PLAYER_BULLET_01,					// �t�@�C���̖��O
		&g_D3DTextureTutorialPlayerBullet);			// �ǂݍ��ރ������[

		// SE���[�h
		g_pTutorialPlayerBullet01SE = LoadSound(SE_PLAYER_BULLET_01);

	}

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, tutorialplayerbullet++)
	{
		tutorialplayerbullet->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// �������WX,Y,Z
		tutorialplayerbullet->use = false;
	}

	// ���_�t�H�[�}�b�g(�X�^�[�g)
	MakeVtx4PointData(g_TutorialPlayerBulletVertexWk,				// ���_���i�[���[�N
	D3DXVECTOR3(-100.0f, -100.0f, 0.0f), 							// �������WX,Y,Z
	PLAYER_BULLET_03_SIZE_X, PLAYER_BULLET_03_SIZE_Y);				// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorialPlayerBullet(void)
{
	if (g_D3DTextureTutorialPlayerBullet != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTutorialPlayerBullet->Release();
		g_D3DTextureTutorialPlayerBullet = NULL;
	}

	if (g_pTutorialPlayerBullet01SE != NULL)
	{
		g_pTutorialPlayerBullet01SE->Release();
		g_pTutorialPlayerBullet01SE = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorialPlayerBullet(void)
{
	PLAYERBULLET *tutorialplayerbullet = GetTutorialPlayerBullet(0);

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, tutorialplayerbullet++)
	{
		if (tutorialplayerbullet->use == true)
		{
			tutorialplayerbullet->pos.y -= PLAYER_BULLET_03_SPEED;
		}

		if (tutorialplayerbullet->pos.y <= 0.0f - PLAYER_BULLET_03_SIZE_Y)
		{
			tutorialplayerbullet->use = false;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorialPlayerBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *tutorialplayerbullet = GetTutorialPlayerBullet(0);

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, tutorialplayerbullet++)
	{
		if (tutorialplayerbullet->use == true)
		{
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_D3DTextureTutorialPlayerBullet);

			// ���_���W�̐ݒ�(���_���)
			SetVtx4PointData(g_TutorialPlayerBulletVertexWk, tutorialplayerbullet->pos, PLAYER_BULLET_03_SIZE_X, PLAYER_BULLET_03_SIZE_Y);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialPlayerBulletVertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// �o���b�g��ݒu
//=============================================================================
void SetTutorialPlayerBullet(D3DXVECTOR3 PlayerPos,int BulletPos)
{
	PLAYERBULLET *tutorialplayerbullet = GetTutorialPlayerBullet(0);

	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, tutorialplayerbullet++)
	{
		if (tutorialplayerbullet->use == false)
		{
			// SE�Đ�
			g_pTutorialPlayerBullet01SE->SetCurrentPosition(0);
			PlaySound(g_pTutorialPlayerBullet01SE, E_DS8_FLAG_NONE);

			tutorialplayerbullet->pos = PlayerPos;

			if (BulletPos == PLAYER_BULLET_LEFT)
			{
				tutorialplayerbullet->pos.x += PLAYER_BULLET_03_PLAYER_LEFT;
			}

			else if (BulletPos == PLAYER_BULLET_RIGHT)
			{
				tutorialplayerbullet->pos.x += PLAYER_BULLET_03_PLAYER_RIGHT;
			}

			else if (BulletPos == PLAYER_BULLET_MID)
			{
				tutorialplayerbullet->pos.x += PLAYER_BULLET_03_PLAYER_MID;
			}

			tutorialplayerbullet->use = true;
			break;
		}
	}
}

//=============================================================================
// �o���b�g�̏����擾
//=============================================================================
PLAYERBULLET *GetTutorialPlayerBullet(int no)
{
	return&TutorialPlayerBulletWk[no];
}