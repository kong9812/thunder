#include "main.h"
#include "basic.h"
#include "player.h"
#include "UI.h"
#include "EnemyBulletManager.h"
#include "EnemyBullet01.h"
#include "EnemyBullet02.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureEnemyBullet02 = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_EnemyBullet02VertexWk[NUM_VERTEX];	// ���_���i�[���[�N

ENEMYBULLET				EnemyBullet02Wk[ENEMY_BULLET_02_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyBullet02(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet02 = GetEnemyBullet02(0);

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_ENEMY_BULLET_01,				// �t�@�C���̖��O
		&g_D3DTextureEnemyBullet02);			// �ǂݍ��ރ������[
	}

	for (int i = 0; i < ENEMY_BULLET_02_MAX; i++, enemybullet02++)
	{
		enemybullet02->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// �������WX,Y,Z
		enemybullet02->use = false;
		enemybullet02->ShotAngle = 0;
	}

	// ���_�t�H�[�}�b�g
	MakeVtx4PointData(g_EnemyBullet02VertexWk,		// ���_���i�[���[�N
	enemybullet02->pos, 								// �������WX,Y,Z
	ENEMY_BULLET_02_SIZE_X, ENEMY_BULLET_02_SIZE_Y);	// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyBullet02(void)
{
	if (g_D3DTextureEnemyBullet02 != NULL)
	{// �e�N�X�`���̊J��		 
		g_D3DTextureEnemyBullet02->Release();
		g_D3DTextureEnemyBullet02 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyBullet02(void)
{
	ENEMYBULLET *enemybullet02 = GetEnemyBullet02(0);

	for (int i = 0; i < ENEMY_BULLET_02_MAX; i++, enemybullet02++)
	{
		if (enemybullet02->use == true)
		{
			enemybullet02->pos.x += ENEMY_BULLET_02_SPEED * cosf(enemybullet02->ShotAngle) + (i - 10) / 4;
			enemybullet02->pos.y += ENEMY_BULLET_02_SPEED * sinf(enemybullet02->ShotAngle);

			// ��ʊO�o����false
			if ((enemybullet02->pos.x < 0.0f - ENEMY_BULLET_02_SIZE_X) || (enemybullet02->pos.x > UI_POS_X) ||
				(enemybullet02->pos.y < 0.0f - ENEMY_BULLET_02_SIZE_Y) || (enemybullet02->pos.y > SCREEN_HEIGHT))
			{
				enemybullet02->use = false;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyBullet02(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet02 = GetEnemyBullet02(0);

	for (int i = 0; i < ENEMY_BULLET_02_MAX; i++, enemybullet02++)
	{
		if (enemybullet02->use == true)
		{
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_D3DTextureEnemyBullet02);

			// ���_���W�̐ݒ�(���_���)
			SetVtx4PointData(g_EnemyBullet02VertexWk, enemybullet02->pos, ENEMY_BULLET_02_SIZE_X, ENEMY_BULLET_02_SIZE_Y);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_EnemyBullet02VertexWk, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// �o���b�g��ݒu
//=============================================================================
void SetEnemyBullet02(D3DXVECTOR3 EnemyPos)
{
	ENEMYBULLET *enemybullet02 = GetEnemyBullet02(0);
	PLAYER *player = GetPlayer();

	for (int i = 0; i < ENEMY_BULLET_02_MAX; i++, enemybullet02++)
	{
		if ((i = 0) && (enemybullet02->use == true))continue;

		if (enemybullet02->use == false)
		{
			enemybullet02->pos = EnemyPos;

			enemybullet02->ShotAngle = atan2f(player->pos.y - enemybullet02->pos.y,
				player->pos.x - enemybullet02->pos.x);

			enemybullet02->use = true;
			break;
		}
	}

}

//=============================================================================
// �o���b�g�̏����擾
//=============================================================================
ENEMYBULLET *GetEnemyBullet02(int no)
{
	return&EnemyBullet02Wk[no];
}
