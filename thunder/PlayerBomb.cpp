#include "main.h"
#include "basic.h"
#include "sound.h"
#include "PlayerBomb.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePlayerBomb = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECTSOUNDBUFFER8	g_pPlayerBombSE;					// SE�p�o�b�t�@

VERTEX_2D				g_PlayerBombVertexWk[NUM_VERTEX];	// ���_���i�[���[�N

PLAYERBOMB				PlayerBombWk;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerBomb(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBOMB *tutorialplayerbomb = GetPlayerBomb();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_PLAYER_BOMB,					// �t�@�C���̖��O
			&g_D3DTexturePlayerBomb);		// �ǂݍ��ރ������[

													// SE���[�h
		g_pPlayerBombSE = LoadSound(SE_PLAYER_BOMB);
	}

	tutorialplayerbomb->CountAnim = 0;
	tutorialplayerbomb->PatternAnim = 0;
	tutorialplayerbomb->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	tutorialplayerbomb->use = false;

	// ���_�t�H�[�}�b�g(�G���W���G�t�F�N�g)
	MakeVtx4PointData(g_PlayerBombVertexWk,	// ���_���i�[���[�N
		tutorialplayerbomb->pos,						// ���WX,Y,Z
		ENGINE_EFFECT_SIZE_X, ENGINE_EFFECT_SIZE_Y);	// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerBomb(void)
{
	if (g_D3DTexturePlayerBomb != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTexturePlayerBomb->Release();
		g_D3DTexturePlayerBomb = NULL;
	}

	if (g_pPlayerBombSE != NULL)
	{// �e�N�X�`���̊J��
		g_pPlayerBombSE->Release();
		g_pPlayerBombSE = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerBomb(void)
{
	PLAYERBOMB *tutorialplayerbomb = GetPlayerBomb();

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
void DrawPlayerBomb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBOMB *tutorialplayerbomb = GetPlayerBomb();

	if (tutorialplayerbomb->use == true)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_D3DTexturePlayerBomb);

		// �e�N�X�`�����W�̐ݒ�(�A�j���[�V����)
		SetTextureAnimationData(g_PlayerBombVertexWk, tutorialplayerbomb->PatternAnim, PLAYER_BOMB_PATTERN_DIVIDE_X, PLAYER_BOMB_PATTERN_DIVIDE_Y);

		// ���_���W�̐ݒ�(���_���)
		SetVtx4PointData(g_PlayerBombVertexWk, tutorialplayerbomb->pos, PLAYER_BOMB_SIZE_X, PLAYER_BOMB_SIZE_Y);

		// ���ˌ��̐ݒ�(�S�F)
		SetAllDiffuseData(g_PlayerBombVertexWk, PLAYER_BOMB_COLOR);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PlayerBombVertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ������ݒu
//=============================================================================
void SetPlayerBomb(void)
{
	PLAYERBOMB *tutorialplayerbomb = GetPlayerBomb();

	if (tutorialplayerbomb->use == false)
	{
		// SE�Đ�
		g_pPlayerBombSE->SetCurrentPosition(0);
		PlaySound(g_pPlayerBombSE, E_DS8_FLAG_NONE);

		tutorialplayerbomb->use = true;
	}
}

//=============================================================================
// �����̏����擾
//=============================================================================
PLAYERBOMB *GetPlayerBomb(void)
{
	return &PlayerBombWk;
}
