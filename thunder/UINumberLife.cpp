#include "main.h"
#include "UI.h"
#include "player.h"
#include "UINumberLife.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexLife(void);
void SetTextureLife(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUINumberLife = NULL;		// �e�N�X�`���ւ̃|���S��

VERTEX_2D				LifeVertexWk[UI_NUMBER_LIFE_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N

UINUMBER				LifeWk;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitUINumberLife(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	UINUMBER *expWk = GetLife();

	// �e�N�X�`���[�̏��������s���H
	if (InitType == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_UI_NUMBER,					// �t�@�C���̖��O
			&D3DTextureUINumberLife);				// �ǂݍ��ރ������̃|�C���^
	}

	expWk->pos = D3DXVECTOR3(UI_NUMBER_LIFE_POS_X, UI_NUMBER_LIFE_POS_Y, 0.0f);
	expWk->value = 0;

	// ���_���̍쐬
	MakeVertexLife();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUINumberLife(void)
{
	if (D3DTextureUINumberLife != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureUINumberLife->Release();
		D3DTextureUINumberLife = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUINumberLife(void)
{
	PLAYER *player = GetPlayer();
	UINUMBER *expWk = GetLife();

	expWk->value = player->Life;

	SetTextureLife();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUINumberLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureUINumberLife);

	// �X�R�A
	for (int i = 0; i < UI_NUMBER_LIFE_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, LifeVertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexLife(void)
{
	UINUMBER *score = GetLife();

	int i;
	float habaX = 20.0f;	// �����̉���

							// ��������������
	for (i = 0; i < UI_NUMBER_LIFE_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		LifeVertexWk[i][0].vtx.x = -habaX * i + score->pos.x;
		LifeVertexWk[i][0].vtx.y = score->pos.y;
		LifeVertexWk[i][0].vtx.z = 0.0f;
		LifeVertexWk[i][1].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		LifeVertexWk[i][1].vtx.y = score->pos.y;
		LifeVertexWk[i][1].vtx.z = 0.0f;
		LifeVertexWk[i][2].vtx.x = -habaX * i + score->pos.x;
		LifeVertexWk[i][2].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		LifeVertexWk[i][2].vtx.z = 0.0f;
		LifeVertexWk[i][3].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		LifeVertexWk[i][3].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		LifeVertexWk[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		LifeVertexWk[i][0].rhw =
			LifeVertexWk[i][1].rhw =
			LifeVertexWk[i][2].rhw =
			LifeVertexWk[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		LifeVertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		LifeVertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		LifeVertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		LifeVertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		LifeVertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		LifeVertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		LifeVertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		LifeVertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureLife(void)
{
	UINUMBER *expWk = GetLife();

	int number = expWk->value;

	for (int i = 0; i < UI_NUMBER_LIFE_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);

		LifeVertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		LifeVertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		LifeVertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		LifeVertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}

//=============================================================================
// LIFE�̏����擾
//=============================================================================
UINUMBER *GetLife(void)
{
	return&LifeWk;
}
