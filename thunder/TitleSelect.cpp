#include "main.h"
#include "basic.h"
#include "sound.h"
#include "input.h"
#include "TitleManager.h"
#include "TitleBackground.h"
#include "TitleSelect.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �`�揈��
void DrawTitleSelectStart(void);		// �X�^�[�g�̕`�揈��
void DrawTitleSelectTutorial(void);		// �`���[�g���A���̕`�揈��
void DrawTitleSelectConfig(void);		// �R���t�B�O�̕`�揈��
void DrawTitleSelectEnd(void);			// �G���h�̕`�揈��
void DrawTitleSelectArrow(void);		// ���̕`�揈��

// �X�V����
void ControlTitleSelect(void);			// �I������(�L�[�{�[�h����&�Q�[���p�b�g)
void SetTitleSelectArrow(void);			// �I������(���)
void SetTitleSelectFlashing(void);		// �I������(�_��)
void SetTitleSelectFlashingOn(void);	// �_�ŏ���(�_)
void SetTitleSelectFlashingOff(void);	// �_�ŏ���(��)
void StageTransition(void);				// �X�e�[�W�J�ڏ���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTSOUNDBUFFER8	g_pTitleSelectSE;					// SE�p�o�b�t�@
LPDIRECTSOUNDBUFFER8	g_pTitleBGM;						// BGM�p�o�b�t�@

LPDIRECT3DTEXTURE9		g_D3DTextureTitleStart = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureTitleTutorial = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureTitleConfig = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureTitleEnd = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureTitleSelectLeft = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureTitleSelectRight = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_TitleStartVertexWk[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_TitleTutorialVertexWk[NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_TitleConfigVertexWk[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_TitleEndVertexWk[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_TitleSelectLeftVertexWk[NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_TitleSelectRightVertexWk[NUM_VERTEX];	// ���_���i�[���[�N

int						g_TitleSelect;							// �I����

int						g_nTitleFlashingCount;					// �_�ŗp�^�C�}�[
//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitleSelect(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_START_LOGO,						// �t�@�C���̖��O
		&g_D3DTextureTitleStart);				// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TUTORIAL_LOGO,					// �t�@�C���̖��O
		&g_D3DTextureTitleTutorial);				// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_CONFIG_LOGO,						// �t�@�C���̖��O
		&g_D3DTextureTitleConfig);				// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_END_LOGO,						// �t�@�C���̖��O
		&g_D3DTextureTitleEnd);					// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SELECT_LOGO_LEFT,				// �t�@�C���̖��O
		&g_D3DTextureTitleSelectLeft);			// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SELECT_LOGO_RIGHT,				// �t�@�C���̖��O
		&g_D3DTextureTitleSelectRight);			// �ǂݍ��ރ������[

		// BGM���[�h
		g_pTitleBGM = LoadSound(TITLE_BGM);

		// SE���[�h
		g_pTitleSelectSE = LoadSound(SE_SELECT);
		
	}

	// ���_�t�H�[�}�b�g(�X�^�[�g)
	MakeVtx4PointData(g_TitleStartVertexWk,										// ���_���i�[���[�N
	D3DXVECTOR3(START_LOGO_POS_X, START_LOGO_POS_Y, START_LOGO_POS_Z),			// ���WX,Y,Z
	START_LOGO_SIZE_X, START_LOGO_SIZE_Y);										// �T�C�YX,Y

	// ���_�t�H�[�}�b�g(�`���[�g���A��)
	MakeVtx4PointData(g_TitleTutorialVertexWk,									// ���_���i�[���[�N
	D3DXVECTOR3(TUTORIAL_LOGO_POS_X, TUTORIAL_LOGO_POS_Y, TUTORIAL_LOGO_POS_Z),	// ���WX,Y,Z
	TUTORIAL_LOGO_SIZE_X, TUTORIAL_LOGO_SIZE_Y);								// �T�C�YX,Y

	// ���_�t�H�[�}�b�g(�R���t�B�O)
	MakeVtx4PointData(g_TitleConfigVertexWk,									// ���_���i�[���[�N
	D3DXVECTOR3(CONFIG_LOGO_POS_X, CONFIG_LOGO_POS_Y, CONFIG_LOGO_POS_Z),		// ���WX,Y,Z
	CONFIG_LOGO_SIZE_X, CONFIG_LOGO_SIZE_Y);									// �T�C�YX,Y

	// ���_�t�H�[�}�b�g(�G���h)
	MakeVtx4PointData(g_TitleEndVertexWk,										// ���_���i�[���[�N
	D3DXVECTOR3(END_LOGO_POS_X, END_LOGO_POS_Y, END_LOGO_POS_Z),				// ���WX,Y,Z
	END_LOGO_SIZE_X, END_LOGO_SIZE_Y);											// �T�C�YX,Y

	// ���_�t�H�[�}�b�g(���)
	// ���
	MakeVtx4PointData(g_TitleSelectLeftVertexWk,											// ���_���i�[���[�N
	D3DXVECTOR3(START_LOGO_POS_X - SELECT_INTERVAL, START_LOGO_POS_Y, START_LOGO_POS_Z), 	// ���WX,Y,Z
	SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);												// �T�C�YX,Y
	// ���
	MakeVtx4PointData(g_TitleSelectRightVertexWk,											// ���_���i�[���[�N
	D3DXVECTOR3(START_LOGO_POS_X + SELECT_INTERVAL, START_LOGO_POS_Y, START_LOGO_POS_Z),	// ���WX,Y,Z
	SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);												// �T�C�YX,Y

	g_TitleSelect = TITLE_START;

	g_nTitleFlashingCount = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitleSelect(void)
{
	if (g_D3DTextureTitleStart != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTitleStart->Release();
		g_D3DTextureTitleStart = NULL;
	}

	if (g_D3DTextureTitleTutorial != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTitleTutorial->Release();
		g_D3DTextureTitleTutorial = NULL;
	}

	if (g_D3DTextureTitleConfig != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTitleConfig->Release();
		g_D3DTextureTitleConfig = NULL;
	}

	if (g_D3DTextureTitleEnd != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTitleEnd->Release();
		g_D3DTextureTitleEnd = NULL;
	}

	if (g_D3DTextureTitleSelectLeft != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTitleSelectLeft->Release();
		g_D3DTextureTitleSelectLeft = NULL;
	}

	if (g_D3DTextureTitleSelectRight != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTitleSelectRight->Release();
		g_D3DTextureTitleSelectRight = NULL;
	}

	if (g_pTitleSelectSE != NULL)
	{
		g_pTitleSelectSE->Release();
		g_pTitleSelectSE = NULL;
	}

	if (g_pTitleBGM != NULL)
	{
		g_pTitleBGM->Release();
		g_pTitleBGM = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitleSelect(void)
{
	// BGM�Đ�
	PlaySound(g_pTitleBGM, E_DS8_FLAG_LOOP);

	g_nTitleFlashingCount++;

	ControlTitleSelect();		// ����
	SetTitleSelectArrow();		// ���̈ړ�
	SetTitleSelectFlashing();	// �_��
	StageTransition();			// �X�e�[�W�J��
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitleSelect(void)
{
		DrawTitleSelectStart();			// �`�揈��(�X�^�[�g)
		DrawTitleSelectTutorial();		// �`�揈��(�`���[�g���A��)
		DrawTitleSelectConfig();		// �`�揈��(�R���t�B�O)
		DrawTitleSelectEnd();			// �`�揈��(�G���h)
		DrawTitleSelectArrow();			// �`�揈��(���)
}

//=============================================================================
// �`�揈��(�X�^�[�g)
//=============================================================================
void DrawTitleSelectStart(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTitleStart);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleStartVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�`���[�g���A��)
//=============================================================================
void DrawTitleSelectTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTitleTutorial);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleTutorialVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�R���t�B�O)
//=============================================================================
void DrawTitleSelectConfig(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTitleConfig);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleConfigVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�G���h)
//=============================================================================
void DrawTitleSelectEnd(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTitleEnd);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleEndVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(���)
//=============================================================================
void DrawTitleSelectArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTitleSelectLeft);

	// ���ˌ��̐ݒ�(�S�F)
	SetAllDiffuseData(g_TitleSelectLeftVertexWk, TITLE_SELECT_COLOR_RED);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleSelectLeftVertexWk, sizeof(VERTEX_2D));

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTitleSelectRight);

	// ���ˌ��̐ݒ�(�S�F)
	SetAllDiffuseData(g_TitleSelectRightVertexWk, TITLE_SELECT_COLOR_RED);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleSelectRightVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �I������(�L�[�{�[�h����&�Q�[���p�b�g)
//=============================================================================
void ControlTitleSelect(void)
{
	if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W))
	{
		// SE�Đ�
		g_pTitleSelectSE->SetCurrentPosition(0);
		PlaySound(g_pTitleSelectSE, E_DS8_FLAG_NONE);

		g_TitleSelect--;

		// �_�ŏ���(�_)
		SetTitleSelectFlashingOn();
	}

	else if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S))
	{
		// SE�Đ�
		g_pTitleSelectSE->SetCurrentPosition(0);
		PlaySound(g_pTitleSelectSE, E_DS8_FLAG_NONE);

		g_TitleSelect++;

		// �_�ŏ���(�_)
		SetTitleSelectFlashingOn();
	}

	if (g_TitleSelect > TITLE_END)
	{
		g_TitleSelect = TITLE_START;
	}

	if (g_TitleSelect < TITLE_START)
	{
		g_TitleSelect = TITLE_END;
	}
}

//=============================================================================
// �I������(���)
//=============================================================================
void SetTitleSelectArrow(void)
{
	switch (g_TitleSelect)
	{
	case TITLE_START:
		// ���
		SetVtx4PointData(
		g_TitleSelectLeftVertexWk,
		D3DXVECTOR3(START_LOGO_POS_X - SELECT_INTERVAL- SELECT_LOGO_SIZE_X, START_LOGO_POS_Y, START_LOGO_POS_Z),
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		// ���
		SetVtx4PointData(
		g_TitleSelectRightVertexWk,
		D3DXVECTOR3(START_LOGO_SIZE_X + START_LOGO_POS_X + SELECT_INTERVAL, START_LOGO_POS_Y, START_LOGO_POS_Z), 
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		break;
	case TITLE_TUTORIAL:
		// ���
		SetVtx4PointData(
		g_TitleSelectLeftVertexWk,
		D3DXVECTOR3(TUTORIAL_LOGO_POS_X - SELECT_INTERVAL - SELECT_LOGO_SIZE_X, TUTORIAL_LOGO_POS_Y, TUTORIAL_LOGO_POS_Z),
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		// ���
		SetVtx4PointData(
		g_TitleSelectRightVertexWk,
		D3DXVECTOR3(TUTORIAL_LOGO_SIZE_X +TUTORIAL_LOGO_POS_X + SELECT_INTERVAL, TUTORIAL_LOGO_POS_Y, TUTORIAL_LOGO_POS_Z),
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		break;
	case TITLE_CONFIG:
		// ���
		SetVtx4PointData(
		g_TitleSelectLeftVertexWk,
		D3DXVECTOR3(CONFIG_LOGO_POS_X - SELECT_INTERVAL - SELECT_LOGO_SIZE_X, CONFIG_LOGO_POS_Y, CONFIG_LOGO_POS_Z),
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		// ���
		SetVtx4PointData(
		g_TitleSelectRightVertexWk,
		D3DXVECTOR3(CONFIG_LOGO_SIZE_X + CONFIG_LOGO_POS_X + SELECT_INTERVAL, CONFIG_LOGO_POS_Y, CONFIG_LOGO_POS_Z),
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		break;
	case TITLE_END:
		// ���
		SetVtx4PointData(
		g_TitleSelectLeftVertexWk,
		D3DXVECTOR3(END_LOGO_POS_X - SELECT_INTERVAL - SELECT_LOGO_SIZE_X, END_LOGO_POS_Y, END_LOGO_POS_Z),
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		// ���
		SetVtx4PointData(
		g_TitleSelectRightVertexWk,
		D3DXVECTOR3(END_LOGO_SIZE_X + END_LOGO_POS_X + SELECT_INTERVAL, END_LOGO_POS_Y, END_LOGO_POS_Z), 
		SELECT_LOGO_SIZE_X, SELECT_LOGO_SIZE_Y);
		break;
	}
}

//=============================================================================
// �I������(�_��)
//=============================================================================
void SetTitleSelectFlashing(void)
{
	if (g_nTitleFlashingCount < SELECT_FLASHING_HOLD_TIME)
	{
		SetTitleSelectFlashingOn();		// �_
	}

	if (g_nTitleFlashingCount > SELECT_FLASHING_HOLD_TIME)
	{
		SetTitleSelectFlashingOff();	// ��
	}

	if (g_nTitleFlashingCount > SELECT_FLASHING_RESET)
	{
		g_nTitleFlashingCount = 0;		// ���Z�b�g
	}
}

//=============================================================================
// �_�ŏ���(�_)
//=============================================================================
void SetTitleSelectFlashingOn(void)
{
	// �X�^�[�g
	SetAllDiffuseData(g_TitleStartVertexWk,
	SELECT_FLASHING_ALPHA_ON);
	// �`���[�g���A��
	SetAllDiffuseData(g_TitleTutorialVertexWk,
	SELECT_FLASHING_ALPHA_ON);
	// �R���t�B�O
	SetAllDiffuseData(g_TitleConfigVertexWk,
	SELECT_FLASHING_ALPHA_ON);
	// �G���h
	SetAllDiffuseData(g_TitleEndVertexWk,
	SELECT_FLASHING_ALPHA_ON);
}

//=============================================================================
// �_�ŏ���(��)
//=============================================================================
void SetTitleSelectFlashingOff(void)
{
	switch (g_TitleSelect)
	{
	case TITLE_START:
		SetAllDiffuseData(g_TitleStartVertexWk,
		SELECT_FLASHING_ALPHA_OFF);
		break;

	case TITLE_TUTORIAL:
		SetAllDiffuseData(g_TitleTutorialVertexWk,
		SELECT_FLASHING_ALPHA_OFF);
		break;

	case TITLE_CONFIG:
		SetAllDiffuseData(g_TitleConfigVertexWk,
		SELECT_FLASHING_ALPHA_OFF);
		break;

	case TITLE_END:
		SetAllDiffuseData(g_TitleEndVertexWk,
		SELECT_FLASHING_ALPHA_OFF);
		break;
	}
}

//=============================================================================
// �X�e�[�W�J�ڏ���
//=============================================================================
void StageTransition(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		switch (g_TitleSelect)
		{
		case TITLE_START:
			SetTitleSelectStage(STAGE_START_GAME);
			SetTitleManagerDrowFalg(false);
			SetDoorFlag(true);
			break;
		case TITLE_TUTORIAL:
			SetTitleSelectStage(STAGE_TUTORIAL);
			SetTitleManagerDrowFalg(false);
			SetDoorFlag(true);
			break;
		case TITLE_CONFIG:

			break;
		case TITLE_END:
			SetGameLoop(false);
			break;
		}
	}
}
