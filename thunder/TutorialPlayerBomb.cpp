#include "main.h"
#include "basic.h"
#include "sound.h"
#include "PlayerBomb.h"
#include "TutorialPlayerBomb.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialPlayerBomb = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECTSOUNDBUFFER8	g_pTutorialPlayerBombSE;					// SE�p�o�b�t�@

VERTEX_2D				g_TutorialPlayerBombVertexWk[NUM_VERTEX];	// ���_���i�[���[�N

PLAYERBOMB				TutorialPlayerBombWk;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTutorialPlayerBomb(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBOMB *tutorialplayerbomb = GetTutorialPlayerBomb();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PLAYER_BOMB,					// �t�@�C���̖��O
		&g_D3DTextureTutorialPlayerBomb);		// �ǂݍ��ރ������[

		// SE���[�h
		g_pTutorialPlayerBombSE = LoadSound(SE_PLAYER_BOMB);
	}

	tutorialplayerbomb->CountAnim = 0;
	tutorialplayerbomb->PatternAnim = 0;
	tutorialplayerbomb->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	tutorialplayerbomb->use = false;

	// ���_�t�H�[�}�b�g(�G���W���G�t�F�N�g)
	MakeVtx4PointData(g_TutorialPlayerBombVertexWk,	// ���_���i�[���[�N
	tutorialplayerbomb->pos,						// ���WX,Y,Z
	ENGINE_EFFECT_SIZE_X, ENGINE_EFFECT_SIZE_Y);	// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorialPlayerBomb(void)
{
	if (g_D3DTextureTutorialPlayerBomb != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTutorialPlayerBomb->Release();
		g_D3DTextureTutorialPlayerBomb = NULL;
	}

	if (g_pTutorialPlayerBombSE != NULL)
	{// �e�N�X�`���̊J��
		g_pTutorialPlayerBombSE->Release();
		g_pTutorialPlayerBombSE = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorialPlayerBomb(void)
{
	PLAYERBOMB *tutorialplayerbomb = GetTutorialPlayerBomb();

	if (tutorialplayerbomb->use == true)
	{
		tutorialplayerbomb->CountAnim++;

		if (tutorialplayerbomb->CountAnim >= INT_MAX)
		{
			tutorialplayerbomb->CountAnim -= INT_MAX;
		}

		if (tutorialplayerbomb->CountAnim%TIME_PLAYER_BOMB_ANIMATION == 0)
		{
			tutorialplayerbomb->PatternAnim++;

			if (tutorialplayerbomb->PatternAnim > ENGINE_EFFECT_ANIM_PATTERN_NUM)
			{
				tutorialplayerbomb->use = false;
				tutorialplayerbomb->PatternAnim = 0;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorialPlayerBomb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBOMB *tutorialplayerbomb = GetTutorialPlayerBomb();

	if (tutorialplayerbomb->use == true)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_D3DTextureTutorialPlayerBomb);

		// �e�N�X�`�����W�̐ݒ�(�A�j���[�V����)
		SetTextureAnimationData(g_TutorialPlayerBombVertexWk, tutorialplayerbomb->PatternAnim, PLAYER_BOMB_PATTERN_DIVIDE_X, PLAYER_BOMB_PATTERN_DIVIDE_Y);

		// ���_���W�̐ݒ�(���_���)
		SetVtx4PointData(g_TutorialPlayerBombVertexWk, tutorialplayerbomb->pos, PLAYER_BOMB_SIZE_X, PLAYER_BOMB_SIZE_Y);

		// ���ˌ��̐ݒ�(�S�F)
		SetAllDiffuseData(g_TutorialPlayerBombVertexWk, PLAYER_BOMB_COLOR);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialPlayerBombVertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ������ݒu
//=============================================================================
void SetTutorialPlayerBomb(void)
{
	PLAYERBOMB *tutorialplayerbomb = GetTutorialPlayerBomb();

	if (tutorialplayerbomb->use == false)
	{
		// SE�Đ�
		g_pTutorialPlayerBombSE->SetCurrentPosition(0);
		PlaySound(g_pTutorialPlayerBombSE, E_DS8_FLAG_NONE);

		tutorialplayerbomb->use = true;
	}
}

//=============================================================================
// �����̏����擾
//=============================================================================
PLAYERBOMB *GetTutorialPlayerBomb(void)
{
	return &TutorialPlayerBombWk;
}
