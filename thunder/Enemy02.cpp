#include "main.h"
#include "basic.h"
#include "UI.h"
#include "EnemyBulletManager.h"
#include "Enemy02.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void Enemy02InScreen(float MapPos, ENEMY *enemy);	// �X�N���[���ɓ���A�j���V����
void CheckEnemy02HP(ENEMY *enemy);					// �G�l�~�[02��HP����
void SetEnemy02Flashing(ENEMY *enemy);				// �G�l�~�[02�̓_�ŏ���
void SetEnemy02Spin(ENEMY *enemy);					// �G�l�~�[02�̉�]����

void SetEnemy02LBasePos(int no);					// �G�l�~�[02(��)�̉�]�O�̍��W��ݒ肷��
void SetEnemy02RBasePos(int no);					// �G�l�~�[02(�E)�̉�]�O�̍��W��ݒ肷��

void SetEnemy02Shoot(ENEMY *enemy);					// �G�l�~�[02�̒e���ˏ���

void SetEnemy02LOutScreen(int no);					// �X�N���[������o��
void SetEnemy02ROutScreen(int no);					// �X�N���[������o��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureEnemy02 = NULL;			// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_Enemy02LVertexWk[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_Enemy02RVertexWk[NUM_VERTEX];		// ���_���i�[���[�N

ENEMY					Enemy02LeftWk[ENEMY_02_MAX];
ENEMY					Enemy02RightWk[ENEMY_02_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy02(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy02L = GetEnemy02Left(0);
	ENEMY *enemy02R = GetEnemy02Right(0);

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_ENEMY_02,						// �t�@�C���̖��O
			&g_D3DTextureEnemy02);					// �ǂݍ��ރ������[
	}

	for (int i = 0; i < ENEMY_02_MAX; i++, enemy02L++)
	{
		enemy02L->pos = ENEMY_02L_SPAWN_POS;
		enemy02L->Duffuse = ENEMY_02_FLASHING_ALPHA_ON;
		enemy02L->pos.y -= 80 * i;
		enemy02L->BasePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy02L->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy02L->HoldTimeCount = 0;
		enemy02L->alive = false;
		enemy02L->FlashFlag = false;
		enemy02L->ShootCount = 0;
		enemy02L->FlashingCount = 0;
		enemy02L->state = ENEMY_MOVE;
		enemy02L->rotAngle = 0;
		enemy02L->HP = ENEMY_02_HP_MAX;
		enemy02L->BaseAngle = atan2f(ENEMY_02_SIZE_Y, ENEMY_02_SIZE_X);	// �p�x��������
		enemy02L->Radius = D3DXVec2Length(&D3DXVECTOR2(		// ���a
			ENEMY_02_SIZE_X / HALF,
			ENEMY_02_SIZE_Y / HALF));
	}

	for (int i = 0; i < ENEMY_02_MAX; i++, enemy02R++)
	{
		enemy02R->pos = ENEMY_02R_SPAWN_POS;
		enemy02R->Duffuse = ENEMY_02_FLASHING_ALPHA_ON;
		enemy02R->pos.y -= 80 * i;
		enemy02R->BasePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy02R->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy02R->HoldTimeCount = 0;
		enemy02R->alive = false;
		enemy02R->FlashFlag = false;
		enemy02R->ShootCount = 0;
		enemy02R->FlashingCount = 0;
		enemy02R->state = ENEMY_MOVE;
		enemy02R->rotAngle = 0;
		enemy02R->HP = ENEMY_02_HP_MAX;
		enemy02R->BaseAngle = atan2f(ENEMY_02_SIZE_Y, ENEMY_02_SIZE_X);	// �p�x��������
		enemy02R->Radius = D3DXVec2Length(&D3DXVECTOR2(		// ���a
			ENEMY_02_SIZE_X / HALF,
			ENEMY_02_SIZE_Y / HALF));
	}

	// ���_�t�H�[�}�b�g(�G�l�~�[)
	// �G�l�~�[_01(��)
	MakeVtx4PointData(g_Enemy02LVertexWk,	// ���_���i�[���[�N
		enemy02L->pos,							// ���WX,Y,Z
		ENEMY_02_SIZE_X, ENEMY_02_SIZE_Y);		// �T�C�YX,Y

												// ���_�t�H�[�}�b�g(�G�l�~�[)
												// �G�l�~�[_01(�E)
	MakeVtx4PointData(g_Enemy02RVertexWk,	// ���_���i�[���[�N
		enemy02R->pos,							// ���WX,Y,Z
		ENEMY_02_SIZE_X, ENEMY_02_SIZE_Y);		// �T�C�YX,Y


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy02(void)
{
	if (g_D3DTextureEnemy02 != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureEnemy02->Release();
		g_D3DTextureEnemy02 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy02(float MapPos)
{
	ENEMY *enemy02L = GetEnemy02Left(0);
	ENEMY *enemy02R = GetEnemy02Right(0);

	for (int i = 0; i < ENEMY_02_MAX; i++, enemy02L++)
	{
		switch (enemy02L->state)
		{
		case ENEMY_MOVE:
			Enemy02InScreen(MapPos, enemy02L);
			break;
		case ENEMY_STOP:
			SetEnemy02Shoot(enemy02L);
			SetEnemy02LBasePos(i);
			break;
		case ENEMY_ESCAPE:
			SetEnemy02Spin(enemy02L);
			SetEnemy02LOutScreen(i);
			break;
		}
		SetEnemy02Flashing(enemy02L);
		CheckEnemy02HP(enemy02L);
	}

	for (int i = 0; i < ENEMY_02_MAX; i++, enemy02R++)
	{
		switch (enemy02R->state)
		{
		case ENEMY_MOVE:
			Enemy02InScreen(MapPos, enemy02R);
			break;
		case ENEMY_STOP:
			SetEnemy02Shoot(enemy02R);
			SetEnemy02RBasePos(i);
			break;
		case ENEMY_ESCAPE:
			SetEnemy02Spin(enemy02R);
			SetEnemy02ROutScreen(i);
			break;
		}
		SetEnemy02Flashing(enemy02R);
		CheckEnemy02HP(enemy02R);
	}
}

//=============================================================================
// �X�N���[���ɓ���A�j���V����
//=============================================================================
void Enemy02InScreen(float MapPos, ENEMY *enemy)
{
	if (MapPos <= ENEMY_02_STOP_POS_Y)
	{
		enemy->alive = true;
		enemy->pos.y += ENEMY_02_SPEED;
	}

	if (enemy->pos.y >= ENEMY_02_SIZE_Y * 3)
	{
		enemy->state = ENEMY_STOP;
	}

}

//=============================================================================
// �X�N���[������o��
//=============================================================================
void SetEnemy02LOutScreen(int no)
{
	ENEMY *enemy02L = GetEnemy02Left(no);

	if (enemy02L->alive == true)
	{
		enemy02L->pos.x -= ENEMY_02_SPEED;

		// ��ʊO�o����false
		if ((enemy02L->pos.x < 0.0f - ENEMY_02_SIZE_X) || (enemy02L->pos.x > SCREEN_WIDTH) ||
			(enemy02L->pos.y < 0.0f - ENEMY_02_SIZE_Y) || (enemy02L->pos.y > SCREEN_HEIGHT))
		{
			enemy02L->alive = false;
		}
	}
}

void SetEnemy02ROutScreen(int no)
{
	ENEMY *enemy02R = GetEnemy02Right(no);

	if (enemy02R->alive == true)
	{
		enemy02R->pos.x -= ENEMY_02_SPEED;

		// ��ʊO�o����false
		if ((enemy02R->pos.x < 0.0f - ENEMY_02_SIZE_X) || (enemy02R->pos.x > UI_POS_X) ||
			(enemy02R->pos.y < 0.0f - ENEMY_02_SIZE_Y) || (enemy02R->pos.y > SCREEN_HEIGHT))
		{
			enemy02R->alive = false;
		}
	}
}

//=============================================================================
// �G�l�~�[�̒e���ˏ���
//=============================================================================
void SetEnemy02Shoot(ENEMY *enemy)
{
	if (enemy->alive == true)
	{
		enemy->ShootCount++;

		if ((enemy->ShootCount%ENEMY_02_SHOOT_TIME) == 0)
		{
			SetEnemyBullet(enemy->pos, ENEMY_BULLET_03);
		}

		if (enemy->ShootCount >= INT_MAX)
		{
			enemy->ShootCount -= enemy->ShootCount;
		}
	}
}

//=============================================================================
// ��]�O�̍��W��ݒ�
//=============================================================================
void SetEnemy02LBasePos(int no)
{
	ENEMY *enemy02L = GetEnemy02Left(no);

	if (enemy02L->alive == true)
	{
		enemy02L->HoldTimeCount++;

		if (enemy02L->HoldTimeCount%ENEMY_02_STOP_TIME == 0)
		{
			enemy02L->state = ENEMY_ESCAPE;
		}
	}
}

void SetEnemy02RBasePos(int no)
{
	ENEMY *enemy02R = GetEnemy02Right(no);

	if (enemy02R->alive == true)
	{
		enemy02R->HoldTimeCount++;

		if (enemy02R->HoldTimeCount%ENEMY_02_STOP_TIME == 0)
		{
			enemy02R->state = ENEMY_ESCAPE;
		}
	}
}


//=============================================================================
// �G�l�~�[02�̓_�ŏ���
//=============================================================================
void SetEnemy02Flashing(ENEMY *enemy)
{
	if (enemy->FlashFlag == true)
	{
		enemy->FlashingCount++;

		if (enemy->FlashingCount < ENEMY_02_FLASHING_HOLD_TIME)
		{
			enemy->Duffuse = ENEMY_02_FLASHING_ALPHA_ON;
		}

		if (enemy->FlashingCount > ENEMY_02_FLASHING_HOLD_TIME)
		{
			enemy->Duffuse = ENEMY_02_FLASHING_ALPHA_OFF;
		}

		if (enemy->FlashingCount > ENEMY_02_FLASHING_RESET)
		{
			enemy->Duffuse = ENEMY_02_FLASHING_ALPHA_ON;

			enemy->FlashingCount = 0;					// ���Z�b�g
			enemy->FlashFlag = false;

		}
	}

}

//=============================================================================
// �G�l�~�[02�̉�]����
//=============================================================================
void SetEnemy02Spin(ENEMY *enemy)
{
	if (enemy->alive == true)
	{
		enemy->rot.z = ENEMY_02_SPIN_Z;
	}
}

//=============================================================================
// �G�l�~�[02��HP����
//=============================================================================
void CheckEnemy02HP(ENEMY *enemy)
{
	if (enemy->HP <= 0)
	{
		enemy->alive = false;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy02(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy02L = GetEnemy02Left(0);
	ENEMY *enemy02R = GetEnemy02Right(0);

	for (int i = 0; i < ENEMY_02_MAX; i++, enemy02L++)
	{
		if (enemy02L->alive == true)
		{
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_D3DTextureEnemy02);

			// ���_���W�̐ݒ�
			SetVtxCenterData(g_Enemy02LVertexWk, enemy02L->pos, ENEMY_02_SIZE_X, ENEMY_02_SIZE_Y);

			// ���ˌ��̐ݒ�(�S�F)
			SetAllDiffuseData(g_Enemy02LVertexWk, enemy02L->Duffuse);

			// ���_���W�̐ݒ�(��]�p)
			SetVtxRotData(g_Enemy02LVertexWk, enemy02L->pos, enemy02L->rot, enemy02L->BaseAngle, enemy02L->Radius);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Enemy02LVertexWk, sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < ENEMY_02_MAX; i++, enemy02R++)
	{
		if (enemy02R->alive == true)
		{
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_D3DTextureEnemy02);

			// ���_���W�̐ݒ�
			SetVtxCenterData(g_Enemy02RVertexWk, enemy02R->pos, ENEMY_02_SIZE_X, ENEMY_02_SIZE_Y);

			// ���ˌ��̐ݒ�(�S�F)
			SetAllDiffuseData(g_Enemy02RVertexWk, enemy02R->Duffuse);

			// ���_���W�̐ݒ�(��]�p)
			SetVtxRotData(g_Enemy02RVertexWk, enemy02R->pos, enemy02R->rot, enemy02R->BaseAngle, enemy02R->Radius);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Enemy02RVertexWk, sizeof(VERTEX_2D));
		}
	}

}

//=============================================================================
// �G�l�~�[02�̏����擾
//=============================================================================
ENEMY *GetEnemy02Left(int no)
{
	return (&Enemy02LeftWk[no]);
}

//=============================================================================
// �G�l�~�[02�̏����擾
//=============================================================================
ENEMY *GetEnemy02Right(int no)
{
	return (&Enemy02RightWk[no]);
}