#include "main.h"
#include "basic.h"
#include "UI.h"
#include "EnemyBulletManager.h"
#include "Enemy03.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void Enemy03InScreen(float MapPos, ENEMY *enemy);		// �X�N���[���ɓ���A�j���V����
void CheckEnemy03HP(ENEMY *enemy);						// �G�l�~�[03��HP����
void SetEnemy03Flashing(ENEMY *enemy);					// �G�l�~�[03�̓_�ŏ���
void SetEnemy03Spin(ENEMY *enemy);						// �G�l�~�[03�̉�]����
void SetEnemy03BasePos(void);							// �G�l�~�[03�̉�]�O�̍��W��ݒ肷��
void SetEnemy03OutScreen(void);							// �X�N���[������o��

void SetEnemy03Shoot(ENEMY *enemy);						// �G�l�~�[03�̒e���ˏ���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureEnemy03 = NULL;			// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_Enemy03VertexWk[NUM_VERTEX];		// ���_���i�[���[�N

ENEMY					Enemy03Wk;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy03(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy03 = GetEnemy03();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_ENEMY_03,						// �t�@�C���̖��O
			&g_D3DTextureEnemy03);					// �ǂݍ��ރ������[
	}


	enemy03->pos = ENEMY_03_SPAWN_POS;
	enemy03->Duffuse = ENEMY_03_FLASHING_ALPHA_ON;
	enemy03->pos.y -= 80;
	enemy03->BasePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy03->rot = D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI);
	enemy03->alive = false;
	enemy03->FlashFlag = false;
	enemy03->ShootCount = 0;
	enemy03->FlashingCount = 0;
	enemy03->state = ENEMY_MOVE;
	enemy03->rotAngle = 0;
	enemy03->HP = ENEMY_03_HP_MAX;
	enemy03->BaseAngle = atan2f(ENEMY_03_SIZE_Y, ENEMY_03_SIZE_X);	// �p�x��������
	enemy03->Radius = D3DXVec2Length(&D3DXVECTOR2(		// ���a
		ENEMY_03_SIZE_X / HALF,
		ENEMY_03_SIZE_Y / HALF));



	// ���_�t�H�[�}�b�g(�G�l�~�[)
	// �G�l�~�[_01(��)
	MakeVtx4PointData(g_Enemy03VertexWk,	// ���_���i�[���[�N
		enemy03->pos,							// ���WX,Y,Z
		ENEMY_03_SIZE_X, ENEMY_03_SIZE_Y);		// �T�C�YX,Y


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy03(void)
{
	if (g_D3DTextureEnemy03 != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureEnemy03->Release();
		g_D3DTextureEnemy03 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy03(float MapPos)
{
	ENEMY *enemy03 = GetEnemy03();


	switch (enemy03->state)
	{
	case ENEMY_MOVE:
		Enemy03InScreen(MapPos, enemy03);
		break;
	case ENEMY_STOP:
		SetEnemy03Shoot(enemy03);
		break;
	case ENEMY_ESCAPE:
		break;
	}

	SetEnemy03Flashing(enemy03);

	CheckEnemy03HP(enemy03);
}

//=============================================================================
// �X�N���[���ɓ���A�j���V����
//=============================================================================
void Enemy03InScreen(float MapPos, ENEMY *enemy)
{
	if (MapPos <= ENEMY_03_STOP_POS_Y)
	{
		enemy->alive = true;
		enemy->pos.y += ENEMY_03_SPEED;
	}

	if (enemy->pos.y >= ENEMY_03_SIZE_Y)
	{
		enemy->state = ENEMY_STOP;
	}

}

//=============================================================================
// �G�l�~�[�̒e���ˏ���
//=============================================================================
void SetEnemy03Shoot(ENEMY *enemy)
{
	if (enemy->alive == true)
	{
		enemy->ShootCount++;

		if ((enemy->ShootCount%ENEMY_03_SHOOT_03_TIME) == 0)
		{
			SetEnemyBullet(enemy->pos, ENEMY_BULLET_03);
		}

		//if ((enemy->ShootCount%ENEMY_03_SHOOT_02_TIME) == 0)
		//{
		//	SetEnemyBullet(enemy->pos, ENEMY_BULLET_02);
		//}

		//if ((enemy->ShootCount%ENEMY_03_SHOOT_01_TIME) == 0)
		//{
		//	SetEnemyBullet(enemy->pos, ENEMY_BULLET_01);
		//}

		if (enemy->ShootCount >= INT_MAX)
		{
			enemy->ShootCount -= enemy->ShootCount;
		}
	}
}



//=============================================================================
// �X�N���[������o��
//=============================================================================
void SetEnemy03OutScreen()
{
	ENEMY *enemy03 = GetEnemy03();

	enemy03->rotAngle += 1.0f;

	enemy03->pos.x = enemy03->BasePos.x + 300.0f * cosf(D3DXToRadian(enemy03->rotAngle));
	enemy03->pos.y = enemy03->BasePos.y + 300.0f * sinf(D3DXToRadian(enemy03->rotAngle));

	// ��ʊO�o����false
	if ((enemy03->pos.x < 0.0f - ENEMY_03_SIZE_X) || (enemy03->pos.x > SCREEN_WIDTH) ||
		(enemy03->pos.y < 0.0f - ENEMY_03_SIZE_Y) || (enemy03->pos.y > SCREEN_HEIGHT))
	{
		enemy03->alive = false;
	}
}


//=============================================================================
// ��]�O�̍��W��ݒ�
//=============================================================================
void SetEnemy03BasePos()
{
	ENEMY *enemy03 = GetEnemy03();

	enemy03->BasePos = enemy03->pos;
	enemy03->BasePos.x += 300.0f;

	enemy03->state = ENEMY_ESCAPE;
}


//=============================================================================
// �G�l�~�[01�̓_�ŏ���
//=============================================================================
void SetEnemy03Flashing(ENEMY *enemy)
{
	if (enemy->FlashFlag == true)
	{
		enemy->FlashingCount++;

		if (enemy->FlashingCount < ENEMY_03_FLASHING_HOLD_TIME)
		{
			enemy->Duffuse = ENEMY_03_FLASHING_ALPHA_ON;
		}

		if (enemy->FlashingCount > ENEMY_03_FLASHING_HOLD_TIME)
		{
			enemy->Duffuse = ENEMY_03_FLASHING_ALPHA_OFF;
		}

		if (enemy->FlashingCount > ENEMY_03_FLASHING_RESET)
		{
			enemy->Duffuse = ENEMY_03_FLASHING_ALPHA_ON;

			enemy->FlashingCount = 0;					// ���Z�b�g
			enemy->FlashFlag = false;

		}
	}

}

//=============================================================================
// �G�l�~�[01�̉�]����
//=============================================================================
void SetEnemy03Spin(ENEMY *enemy)
{
	enemy->rot.z += ENEMY_03_SPIN_Z;

	if (enemy->rot.z > FLT_MAX)
	{
		enemy->rot.z -= FLT_MAX;
	}

}

//=============================================================================
// �G�l�~�[01��HP����
//=============================================================================
void CheckEnemy03HP(ENEMY *enemy)
{
	if (enemy->HP < 0)
	{
		enemy->alive = false;
		SetStage(STAGE_WIN);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy03(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy03 = GetEnemy03();

	if (enemy03->alive == true)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_D3DTextureEnemy03);

		// ���_���W�̐ݒ�
		SetVtxCenterData(g_Enemy03VertexWk, enemy03->pos, ENEMY_03_SIZE_X, ENEMY_03_SIZE_Y);

		// ���ˌ��̐ݒ�(�S�F)
		SetAllDiffuseData(g_Enemy03VertexWk, enemy03->Duffuse);

		// ���_���W�̐ݒ�(��]�p)
		SetVtxRotData(g_Enemy03VertexWk, enemy03->pos, enemy03->rot, enemy03->BaseAngle, enemy03->Radius);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Enemy03VertexWk, sizeof(VERTEX_2D));
	}
}


//=============================================================================
// �G�l�~�[03�̏����擾
//=============================================================================
ENEMY *GetEnemy03(void)
{
	return &Enemy03Wk;
}