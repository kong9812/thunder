#include "main.h"
#include "UI.h"
#include "UINumberScore.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUINumberScore = NULL;		// �e�N�X�`���ւ̃|���S��

VERTEX_2D				ScoreVertexWk[UI_NUMBER_SCORE_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N

UINUMBER				ScoreWk;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitUINumberScore(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	UINUMBER *scoreWk = GetScore();

	// �e�N�X�`���[�̏��������s���H
	if (InitType == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_UI_NUMBER,					// �t�@�C���̖��O
			&D3DTextureUINumberScore);				// �ǂݍ��ރ������̃|�C���^
	}

	scoreWk->pos = D3DXVECTOR3(UI_NUMBER_SCORE_POS_X, UI_NUMBER_SCORE_POS_Y, 0.0f);
	scoreWk->value = 0;

	// ���_���̍쐬
	MakeVertexScore();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUINumberScore(void)
{
	if (D3DTextureUINumberScore != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureUINumberScore->Release();
		D3DTextureUINumberScore = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUINumberScore(void)
{
	SetTextureScore();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUINumberScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureUINumberScore);

	// �X�R�A
	for (int i = 0; i < UI_NUMBER_SCORE_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, ScoreVertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScore(void)
{
	UINUMBER *score = GetScore();

	int i;
	float habaX = 20.0f;	// �����̉���

							// ��������������
	for (i = 0; i < UI_NUMBER_SCORE_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		ScoreVertexWk[i][0].vtx.x = -habaX * i + score->pos.x;
		ScoreVertexWk[i][0].vtx.y = score->pos.y;
		ScoreVertexWk[i][0].vtx.z = 0.0f;
		ScoreVertexWk[i][1].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		ScoreVertexWk[i][1].vtx.y = score->pos.y;
		ScoreVertexWk[i][1].vtx.z = 0.0f;
		ScoreVertexWk[i][2].vtx.x = -habaX * i + score->pos.x;
		ScoreVertexWk[i][2].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		ScoreVertexWk[i][2].vtx.z = 0.0f;
		ScoreVertexWk[i][3].vtx.x = -habaX * i + score->pos.x + UI_NUMBER_SIZE_X;
		ScoreVertexWk[i][3].vtx.y = score->pos.y + UI_NUMBER_SIZE_Y;
		ScoreVertexWk[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		ScoreVertexWk[i][0].rhw =
			ScoreVertexWk[i][1].rhw =
			ScoreVertexWk[i][2].rhw =
			ScoreVertexWk[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		ScoreVertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ScoreVertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ScoreVertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ScoreVertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		ScoreVertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		ScoreVertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		ScoreVertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		ScoreVertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureScore(void)
{
	UINUMBER *scoreWk = GetScore();

	int number = scoreWk->value;

	for (int i = 0; i < UI_NUMBER_SCORE_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);

		ScoreVertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		ScoreVertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		ScoreVertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		ScoreVertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}
//=============================================================================
// HP�f�[�^���Z�b�g����
// ����:add :�ǉ�����_���B�}�C�i�X���\�A�������ȂǂɁB
//=============================================================================
void AddScore(int add)
{
	UINUMBER *scoreWk = GetScore();

	scoreWk->value += add;
	if (scoreWk->value > SCORE_MAX)
	{
		scoreWk->value = SCORE_MAX;
	}

	else if (scoreWk->value < 0)
	{
		scoreWk->value = 0;
	}
}

//=============================================================================
// SCORE�̏����擾
//=============================================================================
UINUMBER *GetScore(void)
{
	return&ScoreWk;
}
