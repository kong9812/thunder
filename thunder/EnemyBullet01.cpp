#include "main.h"
#include "basic.h"
#include "player.h"
#include "UI.h"
#include "EnemyBulletManager.h"
#include "EnemyBullet01.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureEnemyBullet01 = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_EnemyBullet01VertexWk[NUM_VERTEX];	// ���_���i�[���[�N

ENEMYBULLET				EnemyBullet01Wk[ENEMY_BULLET_01_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyBullet01(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet01 = GetEnemyBullet01(0);

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_ENEMY_BULLET_01,				// �t�@�C���̖��O
		&g_D3DTextureEnemyBullet01);			// �ǂݍ��ރ������[
	}

	for (int i = 0; i < ENEMY_BULLET_01_MAX; i++, enemybullet01++)
	{
		enemybullet01->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// �������WX,Y,Z
		enemybullet01->use = false;
		enemybullet01->ShotAngle = 0;
	}

	// ���_�t�H�[�}�b�g(�X�^�[�g)
	MakeVtx4PointData(g_EnemyBullet01VertexWk,			// ���_���i�[���[�N
	enemybullet01->pos, 								// �������WX,Y,Z
	ENEMY_BULLET_01_SIZE_X, ENEMY_BULLET_01_SIZE_Y);	// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyBullet01(void)
{
	if (g_D3DTextureEnemyBullet01 != NULL)
	{// �e�N�X�`���̊J��		 
		g_D3DTextureEnemyBullet01->Release();
		g_D3DTextureEnemyBullet01 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyBullet01(void)
{
	ENEMYBULLET *enemybullet01 = GetEnemyBullet01(0);

	for (int i = 0; i < ENEMY_BULLET_01_MAX; i++, enemybullet01++)
	{
		if (enemybullet01->use == true)
		{
			enemybullet01->pos.x += ENEMY_BULLET_01_SPEED * cosf(enemybullet01->ShotAngle);
			enemybullet01->pos.y += ENEMY_BULLET_01_SPEED * sinf(enemybullet01->ShotAngle);

			// ��ʊO�o����false
			if ((enemybullet01->pos.x < 0.0f - ENEMY_BULLET_01_SIZE_X) || (enemybullet01->pos.x > UI_POS_X) ||
				(enemybullet01->pos.y < 0.0f - ENEMY_BULLET_01_SIZE_Y) || (enemybullet01->pos.y > SCREEN_HEIGHT))
			{
				enemybullet01->use = false;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyBullet01(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet01 = GetEnemyBullet01(0);

	for (int i = 0; i < ENEMY_BULLET_01_MAX; i++, enemybullet01++)
	{
		if (enemybullet01->use == true)
		{
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_D3DTextureEnemyBullet01);

			// ���_���W�̐ݒ�(���_���)
			SetVtx4PointData(g_EnemyBullet01VertexWk, enemybullet01->pos, ENEMY_BULLET_01_SIZE_X, ENEMY_BULLET_01_SIZE_Y);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_EnemyBullet01VertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// �o���b�g��ݒu
//=============================================================================
void SetEnemyBullet01(D3DXVECTOR3 EnemyPos)
{
	ENEMYBULLET *enemybullet01 = GetEnemyBullet01(0);
	PLAYER *player = GetPlayer();

	for (int i = 0; i < ENEMY_BULLET_01_MAX; i++, enemybullet01++)
	{
		if (enemybullet01->use == false)
		{
			enemybullet01->pos = EnemyPos;

			enemybullet01->ShotAngle = atan2f(player->pos.y - enemybullet01->pos.y,
											player->pos.x - enemybullet01->pos.x);
			
			enemybullet01->use = true;
			break;
		}
	}

}

//=============================================================================
// �o���b�g�̏����擾
//=============================================================================
ENEMYBULLET *GetEnemyBullet01(int no)
{
	return&EnemyBullet01Wk[no];
}
