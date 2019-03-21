#include "main.h"
#include "basic.h"
#include "PauseBackground.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePauseBackground = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_PauseBackgroundVertexWk[NUM_VERTEX];	// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPauseBackground(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g(�w�i)
	MakeVtx4PointData(g_PauseBackgroundVertexWk,			// ���_���i�[���[�N
	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 							// ���WX,Y,Z
	SCREEN_WIDTH, SCREEN_HEIGHT);							// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPauseBackground(void)
{
	if (g_D3DTexturePauseBackground != NULL)
	{
		g_D3DTexturePauseBackground->Release();
		g_D3DTexturePauseBackground = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePauseBackground(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPauseBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTexturePauseBackground);

	// ���ˌ��̐ݒ�(�꒸�_����)
	SetAllDiffuseData(g_PauseBackgroundVertexWk, TITLE_NAME_COLOR_GRAY);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PauseBackgroundVertexWk, sizeof(VERTEX_2D));
}
