#include "main.h"
#include "UI.h"
#include "player.h"
#include "UINumberBomb.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBomb(void);
void SetTextureBomb(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUINumberBomb = NULL;		// �e�N�X�`���ւ̃|���S��

VERTEX_2D				BombVertexWk[UI_NUMBER_BOMB_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N

UINUMBER				BombWk;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitUINumberBomb(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	UINUMBER *expWk = GetBomb();

	// �e�N�X�`���[�̏��������s���H
	if (InitType == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_UI_NUMBER,					// �t�@�C���̖��O
			&D3DTextureUINumberBomb);				// �ǂݍ��ރ������̃|�C���^
	}

	expWk->pos = D3DXVECTOR3(UI_NUMBER_BOMB_POS_X, UI_NUMBER_BOMB_POS_Y, 0.0f);
	expWk->value = 0;

	// ���_���̍쐬
	MakeVertexBomb();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUINumberBomb(void)
{
	if (D3DTextureUINumberBomb != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureUINumberBomb->Release();
		D3DTextureUINumberBomb = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUINumberBomb(void)
{
	PLAYER *player = GetPlayer();
	UINUMBER *expWk = GetBomb();

	expWk->value = player->Bomb;

	SetTextureBomb();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUINumberBomb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureUINumberBomb);

	// �X�R�A
	for (int i = 0; i < UI_NUMBER_BOMB_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, BombVertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBomb(void)
{
	UINUMBER *score = GetBomb();

	int i;
	float habaX = 20.0f;	// �����̉���

							// ��������������
	for (i = 0; i < UI_NUMBER_BOMB_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		BombVertexWk[i][0].vtx.x = -habaX * i + score->pos.x;
		BombVertexWk[i][0].vtx.y = score->pos.y;
		BombVertexWk[i][0].vtx.z = 0.0f;
		BombVertexWk[i][1].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		BombVertexWk[i][1].vtx.y = score->pos.y;
		BombVertexWk[i][1].vtx.z = 0.0f;
		BombVertexWk[i][2].vtx.x = -habaX * i + score->pos.x;
		BombVertexWk[i][2].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		BombVertexWk[i][2].vtx.z = 0.0f;
		BombVertexWk[i][3].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		BombVertexWk[i][3].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		BombVertexWk[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		BombVertexWk[i][0].rhw =
			BombVertexWk[i][1].rhw =
			BombVertexWk[i][2].rhw =
			BombVertexWk[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		BombVertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		BombVertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		BombVertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		BombVertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		BombVertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		BombVertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		BombVertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		BombVertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureBomb(void)
{
	UINUMBER *expWk = GetBomb();

	int number = expWk->value;

	for (int i = 0; i < UI_NUMBER_BOMB_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);

		BombVertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		BombVertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		BombVertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		BombVertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}

//=============================================================================
// BOMB�̏����擾
//=============================================================================
UINUMBER *GetBomb(void)
{
	return&BombWk;
}
