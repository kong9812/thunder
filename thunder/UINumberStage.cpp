#include "main.h"
#include "UI.h"
#include "player.h"
#include "Enemy01.h"
#include "Enemy02.h"
#include "Enemy03.h"
#include "UINumberStage.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexStage(void);
void SetTextureStage(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUINumberStage = NULL;		// �e�N�X�`���ւ̃|���S��

VERTEX_2D				StageVertexWk[UI_NUMBER_STAGE_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N

UINUMBER				StageWk;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitUINumberStage(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	UINUMBER *expWk = GetStage();

	// �e�N�X�`���[�̏��������s���H
	if (InitType == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_UI_NUMBER,					// �t�@�C���̖��O
			&D3DTextureUINumberStage);				// �ǂݍ��ރ������̃|�C���^
	}

	expWk->pos = D3DXVECTOR3(UI_NUMBER_STAGE_POS_X, UI_NUMBER_STAGE_POS_Y, 0.0f);
	expWk->value = STAGE_0;

	// ���_���̍쐬
	MakeVertexStage();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUINumberStage(void)
{
	if (D3DTextureUINumberStage != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureUINumberStage->Release();
		D3DTextureUINumberStage = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUINumberStage(float MapPos)
{
	UINUMBER *stageWk = GetStage();

	if (MapPos <= ENEMY_01_STOP_POS_Y)
	{
		stageWk->value = STAGE_1;
	}

	if (MapPos <= ENEMY_02_STOP_POS_Y)
	{
		stageWk->value = STAGE_2;
	}

	if (MapPos <= ENEMY_03_STOP_POS_Y)
	{
		stageWk->value = STAGE_3;
	}


	SetTextureStage();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUINumberStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureUINumberStage);

	// �X�R�A
	for (int i = 0; i < UI_NUMBER_STAGE_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, StageVertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexStage(void)
{
	UINUMBER *score = GetStage();

	int i;
	float habaX = 20.0f;	// �����̉���

							// ��������������
	for (i = 0; i < UI_NUMBER_STAGE_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		StageVertexWk[i][0].vtx.x = -habaX * i + score->pos.x;
		StageVertexWk[i][0].vtx.y = score->pos.y;
		StageVertexWk[i][0].vtx.z = 0.0f;
		StageVertexWk[i][1].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		StageVertexWk[i][1].vtx.y = score->pos.y;
		StageVertexWk[i][1].vtx.z = 0.0f;
		StageVertexWk[i][2].vtx.x = -habaX * i + score->pos.x;
		StageVertexWk[i][2].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		StageVertexWk[i][2].vtx.z = 0.0f;
		StageVertexWk[i][3].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		StageVertexWk[i][3].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		StageVertexWk[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		StageVertexWk[i][0].rhw =
			StageVertexWk[i][1].rhw =
			StageVertexWk[i][2].rhw =
			StageVertexWk[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		StageVertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		StageVertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		StageVertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		StageVertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		StageVertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		StageVertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		StageVertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		StageVertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureStage(void)
{
	UINUMBER *expWk = GetStage();

	int number = expWk->value;

	for (int i = 0; i < UI_NUMBER_STAGE_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);

		StageVertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		StageVertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		StageVertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		StageVertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}

//=============================================================================
// STAGE�̏����擾
//=============================================================================
UINUMBER *GetStage(void)
{
	return&StageWk;
}
