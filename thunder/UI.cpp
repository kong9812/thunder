#include "main.h"
#include "basic.h"
#include "UINumberStage.h"
#include "UINumberLife.h"
#include "UINumberBomb.h"
#include "UINumberScore.h"
#include "UINumberExp.h"
#include "UINumberLevel.h"
#include "UI.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureUI = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_UIVertexWk[NUM_VERTEX];	// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitUI(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		InitUINumberStage(FIRST_INIT);
		InitUINumberLife(FIRST_INIT);
		InitUINumberBomb(FIRST_INIT);
		InitUINumberScore(FIRST_INIT);
		InitUINumberExp(FIRST_INIT);
		InitUINumberLevel(FIRST_INIT);

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_UI,							// �t�@�C���̖��O
		&g_D3DTextureUI);					// �ǂݍ��ރ������[
	}

	else
	{
		InitUINumberStage(RE_INIT);
		InitUINumberLife(RE_INIT);
		InitUINumberBomb(RE_INIT);
		InitUINumberScore(RE_INIT);
		InitUINumberExp(RE_INIT);
		InitUINumberLevel(RE_INIT);
	}

	// ���_�t�H�[�}�b�g(�X�^�[�g)
	MakeVtx4PointData(g_UIVertexWk,			// ���_���i�[���[�N
	D3DXVECTOR3(UI_POS_X, 0.0f, 0.0f),		// ���WX,Y,Z
	RIGHT_UI_SIZE_X, RIGHT_UI_SIZE_Y);		// �T�C�YX,Y
	 
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUI(void)
{
	if (g_D3DTextureUI != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureUI->Release();
		g_D3DTextureUI = NULL;
	}

	UninitUINumberStage();
	UninitUINumberLife();
	UninitUINumberBomb();
	UninitUINumberScore();
	UninitUINumberExp();
	UninitUINumberLevel();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUI(float MapPos)
{
	UpdateUINumberStage(MapPos);
	UpdateUINumberLife();
	UpdateUINumberBomb();
	UpdateUINumberScore();
	UpdateUINumberExp();
	UpdateUINumberLevel();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureUI);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_UIVertexWk, sizeof(VERTEX_2D));

	DrawUINumberStage();
	DrawUINumberLife();
	DrawUINumberBomb();
	DrawUINumberScore();
	DrawUINumberExp();
	DrawUINumberLevel();
}
