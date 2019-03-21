#include "main.h"
#include "basic.h"
#include "player.h"
#include "UI.h"
#include "EnemyBulletManager.h"
#include "EnemyBullet01.h"
#include "EnemyBullet03.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureEnemyBullet03 = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_EnemyBullet03VertexWk[NUM_VERTEX];	// ���_���i�[���[�N

ENEMYBULLET				EnemyBullet03Wk[ENEMY_BULLET_03_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyBullet03(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet03 = GetEnemyBullet03(0);

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			TEXTURE_ENEMY_BULLET_01,				// �t�@�C���̖��O
			&g_D3DTextureEnemyBullet03);			// �ǂݍ��ރ������[
	}

	for (int i = 0; i < ENEMY_BULLET_03_MAX; i++, enemybullet03++)
	{
		enemybullet03->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// �������WX,Y,Z
		enemybullet03->use = false;
		enemybullet03->ShotAngle = 0;
	}

	// ���_�t�H�[�}�b�g
	MakeVtx4PointData(g_EnemyBullet03VertexWk,		// ���_���i�[���[�N
		enemybullet03->pos, 								// �������WX,Y,Z
		ENEMY_BULLET_03_SIZE_X, ENEMY_BULLET_03_SIZE_Y);	// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyBullet03(void)
{
	if (g_D3DTextureEnemyBullet03 != NULL)
	{// �e�N�X�`���̊J��		 
		g_D3DTextureEnemyBullet03->Release();
		g_D3DTextureEnemyBullet03 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyBullet03(void)
{
	ENEMYBULLET *enemybullet03 = GetEnemyBullet03(0);

	for (int i = 0; i < ENEMY_BULLET_03_MAX; i++, enemybullet03++)
	{
		if (enemybullet03->use == true)
		{
			enemybullet03->pos.x += ENEMY_BULLET_03_SPEED * cosf(enemybullet03->ShotAngle)*2.0f;
			enemybullet03->pos.y += ENEMY_BULLET_03_SPEED * sinf(enemybullet03->ShotAngle)*2.0f;

			// ��ʊO�o����false
			if ((enemybullet03->pos.x < 0.0f - ENEMY_BULLET_03_SIZE_X) || (enemybullet03->pos.x > UI_POS_X) ||
				(enemybullet03->pos.y < 0.0f - ENEMY_BULLET_03_SIZE_Y) || (enemybullet03->pos.y > SCREEN_HEIGHT))
			{
				enemybullet03->use = false;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyBullet03(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet03 = GetEnemyBullet03(0);

	for (int i = 0; i < ENEMY_BULLET_03_MAX; i++, enemybullet03++)
	{
		if (enemybullet03->use == true)
		{
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_D3DTextureEnemyBullet03);

			// ���_���W�̐ݒ�(���_���)
			SetVtx4PointData(g_EnemyBullet03VertexWk, enemybullet03->pos, ENEMY_BULLET_03_SIZE_X, ENEMY_BULLET_03_SIZE_Y);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_EnemyBullet03VertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// �o���b�g��ݒu
//=============================================================================
void SetEnemyBullet03(D3DXVECTOR3 EnemyPos)
{
	ENEMYBULLET *enemybullet03 = GetEnemyBullet03(0);
	PLAYER *player = GetPlayer();

	for (int i = 0; i < ENEMY_BULLET_03_MAX; i++, enemybullet03++)
	{
		if ((i = 0) && (enemybullet03->use == true))continue;

		if (enemybullet03->use == false)
		{
			enemybullet03->pos = EnemyPos;

			if (i == 0)
			{
				enemybullet03->ShotAngle = atan2f(player->pos.y - enemybullet03->pos.y,
					player->pos.x - enemybullet03->pos.x);
			}

			else
			{
				enemybullet03->ShotAngle = (enemybullet03 - i)->ShotAngle + i * (2.0f*D3DX_PI / 20.0f);
			}

			enemybullet03->use = true;
			break;
		}
	}

}

//=============================================================================
// �o���b�g�̏����擾
//=============================================================================
ENEMYBULLET *GetEnemyBullet03(int no)
{
	return&EnemyBullet03Wk[no];
}
