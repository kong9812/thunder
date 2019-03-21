#include "main.h"
#include "basic.h"
#include "EffectManager.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureEffect01 = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_Effect01VertexWk[NUM_VERTEX];	// ���_���i�[���[�N

EFFECT					Effect01Wk[EFFECT_01_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffectManager(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT *effect01 = GetEffect01(0);

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EFFECT_01,					// �t�@�C���̖��O
		&g_D3DTextureEffect01);				// �ǂݍ��ރ������[
	}

	for (int i = 0; i < EFFECT_01_MAX; i++, effect01++)
	{
		effect01->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);		// �������WX,Y,Z
		effect01->CountAnim = 0;
		effect01->PatternAnim = 0;
		effect01->use = false;
	}

	// ���_�t�H�[�}�b�g(�X�^�[�g)
	MakeVtx4PointData(g_Effect01VertexWk,	// ���_���i�[���[�N
	effect01->pos, 							// �������WX,Y,Z
	EFFECT_01_SIZE_X, EFFECT_01_SIZE_Y);	// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffectManager(void)
{
	if (g_D3DTextureEffect01 != NULL)
	{// �e�N�X�`���̊J��		 
		g_D3DTextureEffect01->Release();
		g_D3DTextureEffect01 = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffectManager(void)
{
	EFFECT *effect01 = GetEffect01(0);

	for (int i = 0; i < EFFECT_01_MAX; i++, effect01++)
	{
		if (effect01->use == true)
		{
			effect01->CountAnim++;

			if (effect01->CountAnim%TIME_EFFECT_01_ANIMATION == 0)
			{
				effect01->PatternAnim++;
			}

			if (effect01->PatternAnim >= EFFECT_01_ANIM_PATTERN_NUM)
			{
				effect01->PatternAnim = 0;
				effect01->CountAnim = 0;
				effect01->use = false;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffectManager(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT *effect01 = GetEffect01(0);

	for (int i = 0; i < EFFECT_01_MAX; i++, effect01++)
	{
		if (effect01->use == true)
		{
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_D3DTextureEffect01);

			// �e�N�X�`�����W�̐ݒ�(�A�j���[�V����)
			SetTextureAnimationData(g_Effect01VertexWk, effect01->PatternAnim, EFFECT_01_PATTERN_DIVIDE_X, EFFECT_01_PATTERN_DIVIDE_Y);

			// ���_���W�̐ݒ�(���_���)
			SetVtx4PointData(g_Effect01VertexWk, effect01->pos, EFFECT_01_SIZE_X, EFFECT_01_SIZE_Y);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Effect01VertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// �G�t�F�N�g��ݒu
//=============================================================================
void SetEffect01(D3DXVECTOR3 pos)
{
	EFFECT *effect01 = GetEffect01(0);

	for (int i = 0; i < EFFECT_01_MAX; i++, effect01++)
	{
		if (effect01->use == false)
		{
			effect01->pos = pos;
			effect01->pos.x -= EFFECT_01_SIZE_X / HALF;
			effect01->use = true;
			break;
		}
	}
}

//=============================================================================
// �G�t�F�N�g�̏����擾
//=============================================================================
EFFECT *GetEffect01(int no)
{
	return&Effect01Wk[no];
}
