#include "main.h"
#include "basic.h"
#include "PauseUI.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePauseUI = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_PauseUIVertexWk[NUM_VERTEX];	// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPauseUI(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PAUSE_UI,						// �t�@�C���̖��O
		&g_D3DTexturePauseUI);					// �ǂݍ��ރ������[
	}

	// ���_�t�H�[�}�b�g(�w�i)
	MakeVtx4PointData(g_PauseUIVertexWk,				// ���_���i�[���[�N
	D3DXVECTOR3(PAUSE_UI_POS_X, PAUSE_UI_POS_Y, 0.0f), 	// ���WX,Y,Z
	PAUSE_UI_SIZE_X, PAUSE_UI_SIZE_Y);					// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPauseUI(void)
{
	if (g_D3DTexturePauseUI != NULL)
	{
		g_D3DTexturePauseUI->Release();
		g_D3DTexturePauseUI = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePauseUI(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPauseUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTexturePauseUI);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PauseUIVertexWk, sizeof(VERTEX_2D));
}
