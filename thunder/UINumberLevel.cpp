#include "main.h"
#include "UI.h"
#include "player.h"
#include "UINumberLevel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexLevel(void);
void SetTextureLevel(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUINumberLevel = NULL;		// �e�N�X�`���ւ̃|���S��

VERTEX_2D				LevelVertexWk[UI_NUMBER_LEVEL_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N

UINUMBER				LevelWk;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitUINumberLevel(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	UINUMBER *levelWk = GetLevel();

	// �e�N�X�`���[�̏��������s���H
	if (InitType == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_UI_NUMBER,					// �t�@�C���̖��O
			&D3DTextureUINumberLevel);				// �ǂݍ��ރ������̃|�C���^
	}

	levelWk->pos = D3DXVECTOR3(UI_NUMBER_LEVEL_POS_X, UI_NUMBER_LEVEL_POS_Y, 0.0f);
	levelWk->value = 0;

	// ���_���̍쐬
	MakeVertexLevel();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUINumberLevel(void)
{
	if (D3DTextureUINumberLevel != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureUINumberLevel->Release();
		D3DTextureUINumberLevel = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUINumberLevel(void)
{
	PLAYER *player = GetPlayer();
	UINUMBER *levelWk = GetLevel();

	levelWk->value = player->Level;

	SetTextureLevel();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUINumberLevel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureUINumberLevel);

	// �X�R�A
	for (int i = 0; i < UI_NUMBER_LEVEL_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, LevelVertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexLevel(void)
{
	UINUMBER *score = GetLevel();

	int i;
	float habaX = 20.0f;	// �����̉���

							// ��������������
	for (i = 0; i < UI_NUMBER_LEVEL_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		LevelVertexWk[i][0].vtx.x = -habaX * i + score->pos.x;
		LevelVertexWk[i][0].vtx.y = score->pos.y;
		LevelVertexWk[i][0].vtx.z = 0.0f;
		LevelVertexWk[i][1].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		LevelVertexWk[i][1].vtx.y = score->pos.y;
		LevelVertexWk[i][1].vtx.z = 0.0f;
		LevelVertexWk[i][2].vtx.x = -habaX * i + score->pos.x;
		LevelVertexWk[i][2].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		LevelVertexWk[i][2].vtx.z = 0.0f;
		LevelVertexWk[i][3].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		LevelVertexWk[i][3].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		LevelVertexWk[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		LevelVertexWk[i][0].rhw =
			LevelVertexWk[i][1].rhw =
			LevelVertexWk[i][2].rhw =
			LevelVertexWk[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		LevelVertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		LevelVertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		LevelVertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		LevelVertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		LevelVertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		LevelVertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		LevelVertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		LevelVertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureLevel(void)
{
	UINUMBER *levelWk = GetLevel();

	int number = levelWk->value;

	for (int i = 0; i < UI_NUMBER_LEVEL_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);

		LevelVertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		LevelVertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		LevelVertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		LevelVertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}

//=============================================================================
// LEVEL�̏����擾
//=============================================================================
UINUMBER *GetLevel(void)
{
	return&LevelWk;
}
