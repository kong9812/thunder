#include "main.h"
#include "basic.h"
#include "Stage01Manager.h"
#include "TitleBackground.h"
#include "Stage01Background.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �`�揈��
void DrawStage01Background01(void);		// �w�i_01�`�揈��
void DrawStage01Background02(void);		// �w�i_02�`�揈��


// �X�V����
void Stage01BackgroundScroll(void);		// �w�i�X�N���[������

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureStage01Background01 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureStage01Background02 = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_Stage01Background01VertexWk[NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_Stage01Background02VertexWk[NUM_VERTEX];	// ���_���i�[���[�N

float					g_Stage01Background01ScrollDistance;		// �}�b�v01����
float					g_Stage01Background02ScrollDistance;		// �}�b�v02����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStage01Background(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE,						// �t�@�C���̖��O
		&g_D3DTextureStage01Background01);	// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURT_STAGE_01_BACKGROUND_02,		// �t�@�C���̖��O
		&g_D3DTextureStage01Background02);	// �ǂݍ��ރ������[
	}

	g_Stage01Background01ScrollDistance = 0;
	g_Stage01Background02ScrollDistance = 0;

	// ���_�t�H�[�}�b�g(STAGE_01�w�i_01)
	MakeVtx4PointData(g_Stage01Background01VertexWk,	// ���_���i�[���[�N
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),						// ���WX,Y,Z
	SCREEN_WIDTH, SCREEN_HEIGHT);						// �T�C�YX,Y

	// ���_�t�H�[�}�b�g(STAGE_01�w�i_02)
	MakeVtx4PointData(g_Stage01Background02VertexWk,				// ���_���i�[���[�N
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),									// ���WX,Y,Z
	STAGE_01_BACKGROUND_02_SIZE_X, STAGE_01_BACKGROUND_02_SIZE_Y);	// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStage01Background(void)
{
	if (g_D3DTextureStage01Background01 != NULL)
	{
		// �e�N�X�`���̊J��
		g_D3DTextureStage01Background01->Release();
		g_D3DTextureStage01Background01 = NULL;
	}

	if (g_D3DTextureStage01Background02 != NULL)
	{								  
		// �e�N�X�`���̊J��			  
		g_D3DTextureStage01Background02->Release();
		g_D3DTextureStage01Background02 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStage01Background(void)
{
	Stage01BackgroundScroll();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStage01Background(void)
{
	DrawStage01Background01();
	DrawStage01Background02();
}


//=============================================================================
// �w�i_01�`�揈��
//=============================================================================
void DrawStage01Background01(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureStage01Background01);

	// �e�N�X�`�����W�̐ݒ�(�w�i�X�N���[���p)
	SetTextureScrollData(g_Stage01Background01VertexWk, g_Stage01Background01ScrollDistance);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Stage01Background01VertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �w�i_02�`�揈��
//=============================================================================
void DrawStage01Background02(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureStage01Background02);

	// �e�N�X�`�����W�̐ݒ�(�w�i�X�N���[���p)
	SetTextureScrollData(g_Stage01Background02VertexWk, g_Stage01Background02ScrollDistance);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Stage01Background02VertexWk, sizeof(VERTEX_2D));
}


//=============================================================================
// �w�i�X�N���[������
//=============================================================================
void Stage01BackgroundScroll(void)
{
	g_Stage01Background01ScrollDistance -= STAGE_01_BACKGROUND_01_SCROLL_SPEED;
	g_Stage01Background02ScrollDistance -= STAGE_01_BACKGROUND_02_SCROLL_SPEED;

	if (g_Stage01Background01ScrollDistance < FLT_MIN)
	{
		g_Stage01Background01ScrollDistance -= FLT_MIN;
	}

	if (g_Stage01Background02ScrollDistance < FLT_MIN)
	{
		g_Stage01Background02ScrollDistance -= FLT_MIN;
	}

	SetStage01MapScrollPos(g_Stage01Background02ScrollDistance);
	SetDebugStage01MapPos(g_Stage01Background02ScrollDistance);
}
