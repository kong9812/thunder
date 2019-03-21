#include "main.h"
#include "basic.h"
#include "input.h"
#include "sound.h"
#include "PauseSelect.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �`�揈��
void DrawPauseSelectReutrnToGame(void);	// ReturnToGame�̕`�揈��
void DrawPauseSelectBackToTittle(void);	// BackToTittle�̕`�揈��
void DrawPauseSelectQuitGame(void);		// QuitGame�̕`�揈��

// �X�V����
void ControlPauseSelect(void);			// �I������(�L�[�{�[�h����&�Q�[���p�b�g)
void SetPauseSelectDiffuse(void);		// �F���]����
void StagePauseTransition(int STAGE);	// ��ʑJ��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTSOUNDBUFFER8	g_pPauseSelectSE;							// SE�p�o�b�t�@

LPDIRECT3DTEXTURE9		g_D3DTexturePauseReturnToGame = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTexturePauseBackToTittle = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTexturePauseQuitGame = NULL;			// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_PauseReturnToGameVertexWk[NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_PauseBackToTittleVertexWk[NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_PauseQuitGameVertexWk[NUM_VERTEX];		// ���_���i�[���[�N

int						g_PauseSelect;								// �I����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPauseSelect(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PAUSE_RETURNTOGAME,				// �t�@�C���̖��O
		&g_D3DTexturePauseReturnToGame);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PAUSE_BACKTOTITTLE,				// �t�@�C���̖��O
		&g_D3DTexturePauseBackToTittle);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PAUSE_QUITGAME,					// �t�@�C���̖��O
		&g_D3DTexturePauseQuitGame);			// �ǂݍ��ރ������[



		// SE���[�h
		g_pPauseSelectSE = LoadSound(SE_SELECT);
	}

	g_PauseSelect = PAUSE_RETURN_TO_GAME;

	// ���_�t�H�[�}�b�g(ReturnToGame)
	MakeVtx4PointData(g_PauseReturnToGameVertexWk,							// ���_���i�[���[�N
	D3DXVECTOR3(PAUSE_RETURNTOGAME_POS_X, PAUSE_RETURNTOGAME_POS_Y, 0.0f),	// ���WX,Y,Z
	PAUSE_RETURNTOGAME_SIZE_X, PAUSE_RETURNTOGAME_SIZE_Y);					// �T�C�YX,Y

	// ���_�t�H�[�}�b�g(BackToTittle)
	MakeVtx4PointData(g_PauseBackToTittleVertexWk,							// ���_���i�[���[�N
	D3DXVECTOR3(PAUSE_BACKTOTITTLE_POS_X, PAUSE_BACKTOTITTLE_POS_Y, 0.0f),	// ���WX,Y,Z
	PAUSE_BACKTOTITTLE_SIZE_X, PAUSE_BACKTOTITTLE_SIZE_Y);					// �T�C�YX,Y

	// ���_�t�H�[�}�b�g(QuitGame)
	MakeVtx4PointData(g_PauseQuitGameVertexWk,								// ���_���i�[���[�N
	D3DXVECTOR3(PAUSE_QUITGAME_POS_X, PAUSE_QUITGAME_POS_Y, 0.0f),			// ���WX,Y,Z
	PAUSE_QUITGAME_SIZE_X, PAUSE_QUITGAME_SIZE_Y);							// �T�C�YX,Y

	return S_OK;

}

//=============================================================================
// �I������
//==============================================================================
void UninitPauseSelect(void)
{
	if (g_D3DTexturePauseReturnToGame != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTexturePauseReturnToGame->Release();
		g_D3DTexturePauseReturnToGame = NULL;
	}

	if (g_D3DTexturePauseBackToTittle != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTexturePauseBackToTittle->Release();
		g_D3DTexturePauseBackToTittle = NULL;
	}

	if (g_D3DTexturePauseQuitGame != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTexturePauseQuitGame->Release();
		g_D3DTexturePauseQuitGame = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePauseSelect(int STAGE)
{
	ControlPauseSelect();
	StagePauseTransition(STAGE);
	SetPauseSelectDiffuse();

}

//=============================================================================
// �I������(�L�[�{�[�h����&�Q�[���p�b�g)
//=============================================================================
void ControlPauseSelect(void)
{
	if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W))
	{
		// SE�Đ�
		g_pPauseSelectSE->SetCurrentPosition(0);
		PlaySound(g_pPauseSelectSE, E_DS8_FLAG_NONE);

		g_PauseSelect--;
	}

	else if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S))
	{
		// SE�Đ�
		g_pPauseSelectSE->SetCurrentPosition(0);
		PlaySound(g_pPauseSelectSE, E_DS8_FLAG_NONE);

		g_PauseSelect++;
	}

	if (g_PauseSelect > PAUSE_QUIT_GAME)
	{
		g_PauseSelect = PAUSE_RETURN_TO_GAME;
	}

	if (g_PauseSelect < PAUSE_RETURN_TO_GAME)
	{
		g_PauseSelect = PAUSE_QUIT_GAME;
	}
}

//=============================================================================
// �F���]����
//=============================================================================
void SetPauseSelectDiffuse(void)
{
	switch (g_PauseSelect)
	{
	case PAUSE_RETURN_TO_GAME:
		// ���ˌ��̐ݒ�(�S�F)
		SetAllDiffuseData(g_PauseReturnToGameVertexWk, PAUSE_SELECT_RGBA);
		// ���ˌ��̐ݒ�(�S�F)
		SetAllDiffuseData(g_PauseBackToTittleVertexWk, PAUSE_NTSELECT_RGBA);
		// ���ˌ��̐ݒ�(�S�F)
		SetAllDiffuseData(g_PauseQuitGameVertexWk, PAUSE_NTSELECT_RGBA); 
		break;
	case PAUSE_BACK_TO_TITLE:
		// ���ˌ��̐ݒ�(�S�F)
		SetAllDiffuseData(g_PauseBackToTittleVertexWk, PAUSE_SELECT_RGBA);
		// ���ˌ��̐ݒ�(�S�F)
		SetAllDiffuseData(g_PauseReturnToGameVertexWk, PAUSE_NTSELECT_RGBA);
		// ���ˌ��̐ݒ�(�S�F)
		SetAllDiffuseData(g_PauseQuitGameVertexWk, PAUSE_NTSELECT_RGBA);
		break;
	case PAUSE_QUIT_GAME:
		// ���ˌ��̐ݒ�(�S�F)
		SetAllDiffuseData(g_PauseQuitGameVertexWk, PAUSE_SELECT_RGBA);
		// ���ˌ��̐ݒ�(�S�F)
		SetAllDiffuseData(g_PauseReturnToGameVertexWk, PAUSE_NTSELECT_RGBA);
		// ���ˌ��̐ݒ�(�S�F)
		SetAllDiffuseData(g_PauseBackToTittleVertexWk, PAUSE_NTSELECT_RGBA);
		break;
	}
}

//=============================================================================
// �X�e�[�W�J�ڏ���
//=============================================================================
void StagePauseTransition(int STAGE)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		switch (g_PauseSelect)
		{
		case PAUSE_RETURN_TO_GAME:
			SetStage(STAGE);
			break;
		case PAUSE_BACK_TO_TITLE:
			SetStage(STAGE_TITLE);
			InitGame();
			break;
		case PAUSE_QUIT_GAME:
			SetGameLoop(false);
			break;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPauseSelect(void)
{
	DrawPauseSelectReutrnToGame();
	DrawPauseSelectBackToTittle();
	DrawPauseSelectQuitGame();
}

//=============================================================================
// �`�揈��(ReturnToGame)
//=============================================================================
void DrawPauseSelectReutrnToGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTexturePauseReturnToGame);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PauseReturnToGameVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(BackToTittle)
//=============================================================================
void DrawPauseSelectBackToTittle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTexturePauseBackToTittle);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PauseBackToTittleVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(QuitGame)
//=============================================================================
void DrawPauseSelectQuitGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTexturePauseQuitGame);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PauseQuitGameVertexWk, sizeof(VERTEX_2D));
}