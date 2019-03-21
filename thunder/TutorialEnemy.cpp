#include "main.h"
#include "basic.h"
#include "Enemy01.h"
#include "TutorialBackground.h"
#include "TutorialEnemy.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void TutorialEnemyInScreen(float MapPos);		// �X�N���[���ɓ���A�j���V����
void CheckTutorialEnemyHP(void);				// �`���g���A���G�l�~�[��HP����

void SetTutorialEnemyFlashing(void);			// �`���g���A���G�l�~�[�̓_�ŏ���
void SetTutorialEnemySpin(void);				// �`���g���A���G�l�~�[�̉�]����
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialEnemy = NULL;			// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_TutorialEnemyVertexWk[NUM_VERTEX];		// ���_���i�[���[�N

ENEMY					TutorialEnemyWk;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTutorialEnemy(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *tutorialenemy = GetTutorialEnemy();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_ENEMY_01,						// �t�@�C���̖��O
		&g_D3DTextureTutorialEnemy);			// �ǂݍ��ރ������[
	}

	tutorialenemy->pos = TUTORIAL_ENEMY_SPAWN_POS;
	tutorialenemy->rot = D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI);
	tutorialenemy->alive = false;
	tutorialenemy->movie = true;
	tutorialenemy->FlashFlag = false;
	tutorialenemy->ShootCount = 0;
	tutorialenemy->FlashingCount = 0;
	tutorialenemy->HP = ENEMY_01_HP_MAX;
	tutorialenemy->BaseAngle = atan2f(ENEMY_01_SIZE_Y, ENEMY_01_SIZE_X);	// �p�x��������
	tutorialenemy->Radius = D3DXVec2Length(&D3DXVECTOR2(					// ���a
							ENEMY_01_SIZE_Y / HALF,
							ENEMY_01_SIZE_X / HALF));

	// ���_�t�H�[�}�b�g(�`���g���A���G�l�~�[)
	// �G�l�~�[_01
	MakeVtx4PointData(g_TutorialEnemyVertexWk,		// ���_���i�[���[�N
	tutorialenemy->pos,								// ���WX,Y,Z
	ENEMY_01_SIZE_X, ENEMY_01_SIZE_Y);				// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorialEnemy(void)
{
	if (g_D3DTextureTutorialEnemy != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTutorialEnemy->Release();
		g_D3DTextureTutorialEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorialEnemy(float MapPos)
{
	TutorialEnemyInScreen(MapPos);

	SetTutorialEnemySpin();

	SetTutorialEnemyFlashing();

	//CheckTutorialEnemyHP();
}

//=============================================================================
// �X�N���[���ɓ���A�j���V����
//=============================================================================
void TutorialEnemyInScreen(float MapPos)
{
	ENEMY *tutorialenemy = GetTutorialEnemy();

	if ((MapPos <= TUTORIAL_ENEMY_STOP_POS_Y) && (tutorialenemy->movie == true))
	{
		tutorialenemy->alive = true;
		tutorialenemy->pos.y += ENEMY_01_SPEED;
	}

	if (tutorialenemy->pos.y >= ENEMY_01_SIZE_Y)
	{
		tutorialenemy->movie = false;
	}

}

//=============================================================================
// �`���g���A���G�l�~�[�̓_�ŏ���
//=============================================================================
void SetTutorialEnemyFlashing(void)
{
	ENEMY *tutorialenemy = GetTutorialEnemy();

	if (tutorialenemy->FlashFlag == true)
	{
		tutorialenemy->FlashingCount++;

		if (tutorialenemy->FlashingCount < ENEMY_01_FLASHING_HOLD_TIME)
		{
			SetAllDiffuseData(g_TutorialEnemyVertexWk,			// �_
			ENEMY_01_FLASHING_ALPHA_ON);
		}

		if (tutorialenemy->FlashingCount > ENEMY_01_FLASHING_HOLD_TIME)
		{
			SetAllDiffuseData(g_TutorialEnemyVertexWk,			// ��
			ENEMY_01_FLASHING_ALPHA_OFF);
		}

		if (tutorialenemy->FlashingCount > ENEMY_01_FLASHING_RESET)
		{
			SetAllDiffuseData(g_TutorialEnemyVertexWk,			// �_
			ENEMY_01_FLASHING_ALPHA_ON);

			tutorialenemy->FlashingCount = 0;					// ���Z�b�g
			tutorialenemy->FlashFlag = false;

		}
	}
}

//=============================================================================
// �`���g���A���G�l�~�[�̉�]����
//=============================================================================
void SetTutorialEnemySpin(void)
{
	ENEMY *tutorialenemy = GetTutorialEnemy();

	tutorialenemy->rot.z += ENEMY_01_SPIN_Z;

	if (tutorialenemy->rot.z > FLT_MAX)
	{
		tutorialenemy->rot.z -= FLT_MAX;
	}
}

//=============================================================================
// �`���g���A���G�l�~�[��HP����
//=============================================================================
void CheckTutorialEnemyHP(void)
{
	ENEMY *tutorialenemy = GetTutorialEnemy();

	if (tutorialenemy->HP < 0)
	{
		tutorialenemy->alive = false;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorialEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *tutorialenemy = GetTutorialEnemy();

	if (tutorialenemy->alive == true)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_D3DTextureTutorialEnemy);

		// ���_���W�̐ݒ�(��]�p)
		SetVtxRotData(g_TutorialEnemyVertexWk, tutorialenemy->pos, tutorialenemy->rot, tutorialenemy->BaseAngle, tutorialenemy->Radius);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialEnemyVertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// �`���g���A���G�l�~�[�̏����擾
//=============================================================================
ENEMY *GetTutorialEnemy(void)
{
	return &TutorialEnemyWk;
}