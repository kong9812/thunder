#include "main.h"
#include "basic.h"
#include "UI.h"
#include "TutorialUI.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialUI = NULL;			// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_TutorialUIVertexWk[NUM_VERTEX];		// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTutorialUI(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TUTORIAL_UI,						// �t�@�C���̖��O
		&g_D3DTextureTutorialUI);					// �ǂݍ��ރ������[

	}

	// ���_�t�H�[�}�b�g(�X�^�[�g)
	MakeVtx4PointData(g_TutorialUIVertexWk,			// ���_���i�[���[�N
	D3DXVECTOR3(UI_POS_X, 0.0f, 0.0f),				// ���WX,Y,Z
	RIGHT_UI_SIZE_X, RIGHT_UI_SIZE_Y);				// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorialUI(void)
{
	if (g_D3DTextureTutorialUI != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTutorialUI->Release();
		g_D3DTextureTutorialUI = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorialUI(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorialUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTutorialUI);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialUIVertexWk, sizeof(VERTEX_2D));

}
