#include "main.h"
#include "basic.h"
#include "input.h"
#include "Lose.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureLose = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_LoseVertexWk[NUM_VERTEX];	// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitLose(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_LOSE,						// �t�@�C���̖��O
		&g_D3DTextureLose);					// �ǂݍ��ރ������[
	}

	// ���_�t�H�[�}�b�g(�w�i)
	MakeVtx4PointData(g_LoseVertexWk,		// ���_���i�[���[�N
	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 			// ���WX,Y,Z
	SCREEN_WIDTH, SCREEN_HEIGHT);			// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitLose(void)
{
	if (g_D3DTextureLose != NULL)
	{
		g_D3DTextureLose->Release();
		g_D3DTextureLose = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLose(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetStage(STAGE_TITLE);
		InitGame();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLose(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureLose);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_LoseVertexWk, sizeof(VERTEX_2D));
}
