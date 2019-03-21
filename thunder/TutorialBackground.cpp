#include "main.h"
#include "basic.h"
#include "TutorialManager.h"
#include "BackgroundManager.h"
#include "TutorialBackground.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �X�V����
void TutorialBackgroundScroll(void);		// �w�i�X�N���[������

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialBackground = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_TutorialBackgroundVertexWk[NUM_VERTEX];	// ���_���i�[���[�N

float					g_TutorialBackgroundScrollDistance;			// �}�b�v����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTutorialBackground(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BACKGROUND_01,				// �t�@�C���̖��O
		&g_D3DTextureTutorialBackground);	// �ǂݍ��ރ������[
	}

	// ���_�t�H�[�}�b�g(�`���g���A���w�i)
	MakeVtx4PointData(g_TutorialBackgroundVertexWk,		// ���_���i�[���[�N
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),						// ���WX,Y,Z
	BACKGROUND_01_SIZE_X, BACKGROUND_01_SIZE_Y);		// �T�C�YX,Y

	g_TutorialBackgroundScrollDistance = 0.0f;

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void UninitTutorialBackground(void)
{
	if (g_D3DTextureTutorialBackground != NULL)
	{
		// �e�N�X�`���̊J��
		g_D3DTextureTutorialBackground->Release();
		g_D3DTextureTutorialBackground = NULL;
	}
}


//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorialBackground(void)
{
	TutorialBackgroundScroll();
}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorialBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTutorialBackground);

	// �e�N�X�`�����W�̐ݒ�(�w�i�X�N���[���p)
	SetTextureScrollData(g_TutorialBackgroundVertexWk, g_TutorialBackgroundScrollDistance);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialBackgroundVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �w�i�X�N���[������
//=============================================================================
void TutorialBackgroundScroll(void)
{
	g_TutorialBackgroundScrollDistance -= BACKGROUND_01_SCROLL_SPEED;

	if (g_TutorialBackgroundScrollDistance < FLT_MIN)
	{
		g_TutorialBackgroundScrollDistance -= FLT_MIN;
	}

	SetTutorialMapScrollPos(g_TutorialBackgroundScrollDistance);
	SetDebugTutorialMapPos(g_TutorialBackgroundScrollDistance);
}
