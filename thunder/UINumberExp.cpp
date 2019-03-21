#include "main.h"
#include "UI.h"
#include "player.h"
#include "UINumberExp.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexExp(void);
void SetTextureExp(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUINumberExp = NULL;		// �e�N�X�`���ւ̃|���S��

VERTEX_2D				ExpVertexWk[UI_NUMBER_EXP_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N

UINUMBER				ExpWk;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitUINumberExp(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	UINUMBER *expWk = GetExp();

	// �e�N�X�`���[�̏��������s���H
	if (InitType == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
		TEXTURE_UI_NUMBER,					// �t�@�C���̖��O
		&D3DTextureUINumberExp);				// �ǂݍ��ރ������̃|�C���^
	}

	expWk->pos = D3DXVECTOR3(UI_NUMBER_EXP_POS_X, UI_NUMBER_EXP_POS_Y, 0.0f);
	expWk->value = 0;

	// ���_���̍쐬
	MakeVertexExp();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUINumberExp(void)
{
	if (D3DTextureUINumberExp != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureUINumberExp->Release();
		D3DTextureUINumberExp = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUINumberExp(void)
{
	PLAYER *player = GetPlayer();
	UINUMBER *expWk = GetExp();

	expWk->value = player->EXP;

	SetTextureExp();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUINumberExp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureUINumberExp);

	// �X�R�A
	for (int i = 0; i < UI_NUMBER_EXP_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, ExpVertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexExp(void)
{
	UINUMBER *score = GetExp();

	int i;
	float habaX = 20.0f;	// �����̉���

	// ��������������
	for (i = 0; i < UI_NUMBER_EXP_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		ExpVertexWk[i][0].vtx.x = -habaX * i + score->pos.x;
		ExpVertexWk[i][0].vtx.y = score->pos.y;
		ExpVertexWk[i][0].vtx.z = 0.0f;
		ExpVertexWk[i][1].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		ExpVertexWk[i][1].vtx.y = score->pos.y;
		ExpVertexWk[i][1].vtx.z = 0.0f;
		ExpVertexWk[i][2].vtx.x = -habaX * i + score->pos.x;
		ExpVertexWk[i][2].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		ExpVertexWk[i][2].vtx.z = 0.0f;
		ExpVertexWk[i][3].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		ExpVertexWk[i][3].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		ExpVertexWk[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		ExpVertexWk[i][0].rhw =
		ExpVertexWk[i][1].rhw =
		ExpVertexWk[i][2].rhw =
		ExpVertexWk[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		ExpVertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ExpVertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ExpVertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ExpVertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		ExpVertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		ExpVertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		ExpVertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		ExpVertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureExp(void)
{
	UINUMBER *expWk = GetExp();

	int number = expWk->value;

	for (int i = 0; i < UI_NUMBER_EXP_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);

		ExpVertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		ExpVertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		ExpVertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		ExpVertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}

//=============================================================================
// EXP�̏����擾
//=============================================================================
UINUMBER *GetExp(void)
{
	return&ExpWk;
}
