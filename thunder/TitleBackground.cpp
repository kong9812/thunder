#include "main.h"
#include "basic.h"
#include "input.h"
#include "sound.h"
#include "TitleBackground.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �`�揈��
void DrawTitleBG(void);				// �w�i�̕`�揈��
void DrawTitleName(void);			// ���O�̕`�揈��
void DrawTitleCopyRight(void);		// ���쌠�錾�̕`�揈��
void DrawTitleDoor(void);			// �h�A�̕`�揈��

// �X�V����
void TitleScroll(void);				// �w�i�X�N���[������
void UpdateDoorRotation(void);		// �h�A�̉�]����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTitle = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureTitleWall = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureTitleName = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureTitleCopyRight = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureTitleDoor01 = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureTitleDoor02 = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureTitleDoor03 = NULL;			// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_TitleVertexWk[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_TitleWallVertexWk[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_TitleNameVertexWk[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_TitleCopyRightVertexWk[NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_TitleDoor01VertexWk[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_TitleDoor02VertexWk[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_TitleDoor03_00VertexWk[NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_TitleDoor03_01VertexWk[NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_TitleDoor03_02VertexWk[NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_TitleDoor03_03VertexWk[NUM_VERTEX];	// ���_���i�[���[�N

float					g_TitleScrollDistance;					// �^�C�g������				

D3DXVECTOR3				g_Door01Pos;							// ���W

D3DXVECTOR3				g_Door03_00Pos;							// ���W
D3DXVECTOR3				g_Door03_01Pos;							// ���W
D3DXVECTOR3				g_Door03_02Pos;							// ���W
D3DXVECTOR3				g_Door03_03Pos;							// ���W

D3DXVECTOR3				g_DoorMovie;							// �ړ���
float					g_DoorAngle;							// �p�x
float					g_DoorLength;							// ���S���璸�_�܂ł̋���
bool					g_DoorFlag;								// true:�J�� false:����
bool					g_DoorDrawFlag;							// true:�`�� false:�`�悵�Ȃ�

static int				g_Stage;								// �X�e�[�W

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitleBackground(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE,								// �t�@�C���̖��O
		&g_D3DTextureTitle);						// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_WALL,							// �t�@�C���̖��O
		&g_D3DTextureTitleWall);					// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_NAME,							// �t�@�C���̖��O
		&g_D3DTextureTitleName);						// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_COPYRIGHT,						// �t�@�C���̖��O
		&g_D3DTextureTitleCopyRight);				// �ǂݍ��ރ������[
	
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_DOOR_01,								// �t�@�C���̖��O
		&g_D3DTextureTitleDoor01);					// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_DOOR_02,								// �t�@�C���̖��O
		&g_D3DTextureTitleDoor02);					// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_DOOR_03,								// �t�@�C���̖��O
		&g_D3DTextureTitleDoor03);					// �ǂݍ��ރ������[
	}

	g_TitleScrollDistance = 0.0f;											// ��������

	g_Door03_00Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// �����ʒu
	g_Door03_01Pos = D3DXVECTOR3(SCREEN_CENTER_X, 0.0f, 0.0f);				// �����ʒu
	g_Door03_02Pos = D3DXVECTOR3(0.0f, SCREEN_CENTER_Y, 0.0f);				// �����ʒu
	g_Door03_03Pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);	// �����ʒu

	g_Door01Pos		= D3DXVECTOR3(											// �����ʒu
					DOOR_POS_X + DOOR_SIZE_X / HALF,
					DOOR_POS_Y + DOOR_SIZE_Y / HALF, DOOR_POS_Z);
	g_DoorMovie		= D3DXVECTOR3(0.0f, 0.0f, DOOR_MOVIE_Z);				// �����ړ���
	g_DoorAngle		= atan2f(DOOR_SIZE_Y, DOOR_SIZE_X);						// �p�x��������
	g_DoorDrawFlag  = true;													// true:�`��
	g_DoorFlag		= false;												// false:����
	g_DoorLength	= D3DXVec2Length(&D3DXVECTOR2(							// ���S���璸�_�܂ł̋���
					DOOR_SIZE_Y / HALF,
					DOOR_SIZE_X / HALF));

	g_Stage = STAGE_START_GAME;

	// ���_�t�H�[�}�b�g(�w�i)
	MakeVtx4PointData(g_TitleVertexWk,									// ���_���i�[���[�N
	D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, TITLE_POS_Z),					// ���WX,Y,Z
	TITLE_SIZE_X, TITLE_SIZE_Y);											// �T�C�YX,Y

	// ���_�t�H�[�}�b�g(��)
	MakeVtx4PointData(g_TitleWallVertexWk,								// ���_���i�[���[�N
	D3DXVECTOR3(TITLE_WALL_POS_X, TITLE_WALL_POS_Y, TITLE_WALL_POS_Z),	// ���WX,Y,Z
	TITLE_WALL_SIZE_X, TITLE_WALL_SIZE_Y);								// �T�C�YX,Y


	// ���_�t�H�[�}�b�g(���O)
	MakeVtx4PointData(g_TitleNameVertexWk,								// ���_���i�[���[�N
	D3DXVECTOR3(TITLE_NAME_POS_X, TITLE_NAME_POS_Y, TITLE_NAME_POS_Z),	// ���WX,Y,Z
	TITLE_NAME_SIZE_X, TITLE_NAME_SIZE_Y);								// �T�C�YX,Y

	// ���_�t�H�[�}�b�g(���쌠�錾)
	MakeVtx4PointData(g_TitleCopyRightVertexWk,											// ���_���i�[���[�N
	D3DXVECTOR3(TITLE_COPYRIGHT_POS_X, TITLE_COPYRIGHT_POS_Y, TITLE_COPYRIGHT_POS_Z),	// ���WX,Y,Z
	TITLE_COPYRIGHT_SIZE_X, TITLE_COPYRIGHT_SIZE_Y);										// �T�C�YX,Y

	// ���_�t�H�[�}�b�g(�h�A/��)
	// ��g
	MakeVtx4PointData(g_TitleDoor01VertexWk,			// ���_���i�[���[�N
	D3DXVECTOR3(DOOR_POS_X, DOOR_POS_Y, DOOR_POS_Z),	// ���WX,Y,Z
	DOOR_SIZE_X, DOOR_SIZE_Y);							// �T�C�YX,Y
	// ��
	MakeVtx4PointData(g_TitleDoor02VertexWk,			// ���_���i�[���[�N
	D3DXVECTOR3(DOOR_POS_X, DOOR_POS_Y, DOOR_POS_Z),	// ���WX,Y,Z
	DOOR_SIZE_X, DOOR_SIZE_Y);							// �T�C�YX,Y
	
	// ��03-00
	MakeCutVtx4PointData(g_TitleDoor03_00VertexWk,		// ���_���i�[���[�N
	g_Door03_00Pos,										// ���WX,Y,Z
	SCREEN_CENTER_X, SCREEN_CENTER_Y,					// �T�C�YX,Y
	DOOR_CUT_PATTERN_X, DOOR_CUT_PATTERN_Y,				// �����̍��W(X,Y)
	0);													// �����̃T�C�Y(X,Y)
	// ��03-01
	MakeCutVtx4PointData(g_TitleDoor03_01VertexWk,		// ���_���i�[���[�N
	g_Door03_01Pos,										// ���WX,Y,Z
	SCREEN_CENTER_X, SCREEN_CENTER_Y, 					// �T�C�YX,Y
	DOOR_CUT_PATTERN_X, DOOR_CUT_PATTERN_Y,				// �����̍��W(X,Y)
	1);													// �����̃T�C�Y(X,Y)
	// ��03-02
	MakeCutVtx4PointData(g_TitleDoor03_02VertexWk,		// ���_���i�[���[�N
	g_Door03_02Pos,							 			// ���WX,Y,Z
	SCREEN_CENTER_X, SCREEN_CENTER_Y,					// �T�C�YX,Y
	DOOR_CUT_PATTERN_X, DOOR_CUT_PATTERN_Y,				// �����̍��W(X,Y)
	2);													// �����̃T�C�Y(X,Y)
	// ��03-03
	MakeCutVtx4PointData(g_TitleDoor03_03VertexWk,		// ���_���i�[���[�N
	g_Door03_03Pos,										// ���WX,Y,Z
	SCREEN_CENTER_X, SCREEN_CENTER_Y,					// �T�C�YX,Y
	DOOR_CUT_PATTERN_X, DOOR_CUT_PATTERN_Y,				// �����̍��W(X,Y)
	3);													// �����̃T�C�Y(X,Y)


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitleBackground(void)
{
	if(g_D3DTextureTitle != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTitle->Release();
		g_D3DTextureTitle = NULL;
	}

	if (g_D3DTextureTitleWall != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTitleWall->Release();
		g_D3DTextureTitleWall = NULL;
	}


	if (g_D3DTextureTitleName != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTitleName->Release();
		g_D3DTextureTitleName = NULL;
	}

	if (g_D3DTextureTitleCopyRight != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTitleCopyRight->Release();
		g_D3DTextureTitleCopyRight = NULL;
	}

	if (g_D3DTextureTitleDoor01 != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTitleDoor01->Release();
		g_D3DTextureTitleDoor01 = NULL;
	}

	if (g_D3DTextureTitleDoor02 != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTitleDoor02->Release();
		g_D3DTextureTitleDoor02 = NULL;
	}

	if (g_D3DTextureTitleDoor03 != NULL)
	{// �e�N�X�`���̊J��	  
		g_D3DTextureTitleDoor03->Release();
		g_D3DTextureTitleDoor03 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitleBackground(void)
{
	TitleScroll();
	UpdateDoorRotation();
}

//=============================================================================
// �h�A�̉�]�����ƃh�A�̊J������
//=============================================================================
void UpdateDoorRotation(void)
{
	if (g_DoorFlag == true)
	{
		g_DoorMovie.z += DOOR_SCROLL_SPEED;

		if (g_DoorMovie.z >= DOOR_SCROLL_MAX)
		{
			g_DoorDrawFlag = false;

			g_Door03_00Pos.x -= DOOR_MOVE_SPEED;
			g_Door03_00Pos.y -= DOOR_MOVE_SPEED;
			g_Door03_01Pos.x += DOOR_MOVE_SPEED;
			g_Door03_01Pos.y -= DOOR_MOVE_SPEED;
			g_Door03_02Pos.x -= DOOR_MOVE_SPEED;
			g_Door03_02Pos.y += DOOR_MOVE_SPEED;
			g_Door03_03Pos.x += DOOR_MOVE_SPEED;
			g_Door03_03Pos.y += DOOR_MOVE_SPEED;

			if (g_Door03_00Pos.x <= 0.0f - SCREEN_CENTER_X)
			{
				g_DoorFlag = false;
				g_DoorMovie.z = DOOR_MOVIE_Z;
				SetStage(g_Stage);
				g_DoorDrawFlag = true;
			}
		}
	}
}

//=============================================================================
// �w�i�X�N���[������
//=============================================================================
void TitleScroll(void)
{
	g_TitleScrollDistance -= TITLE_SCROLL_SPEED;

	if (g_TitleScrollDistance <= FLT_MIN)
	{
		g_TitleScrollDistance -= FLT_MIN;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitleBackground(bool DrawFlag)
{

	DrawTitleBG();				// �`�揈��(�w�i)
	DrawTitleDoor();			// �`�揈��(�h�A)

	if (DrawFlag == true)
	{
		DrawTitleName();		// �`�揈��(���O)
		DrawTitleCopyRight();	// �`�揈��(���쌠�錾)
	}
}

//=============================================================================
// �`�揈��(�w�i)
//=============================================================================
void DrawTitleBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTitle);

	// �e�N�X�`�����W�̐ݒ�(�w�i�X�N���[���p)
	SetTextureScrollData(g_TitleVertexWk, g_TitleScrollDistance);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleVertexWk, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTitleWall);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleWallVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(���O)
//=============================================================================
void DrawTitleName(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTitleName);

	// ���ˌ��̐ݒ�(�꒸�_����)
	SetSingleDiffuseData(g_TitleNameVertexWk, 0, TITLE_NAME_COLOR_BLACK);	// ����
	SetSingleDiffuseData(g_TitleNameVertexWk, 1, TITLE_NAME_COLOR_RED);		// �E��
	SetSingleDiffuseData(g_TitleNameVertexWk, 2, TITLE_NAME_COLOR_RED);		// ����
	SetSingleDiffuseData(g_TitleNameVertexWk, 3, TITLE_NAME_COLOR_BLACK);	// �E��

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleNameVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(���쌠�錾)
//=============================================================================
void DrawTitleCopyRight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTitleCopyRight);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleCopyRightVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�h�A/��)
//=============================================================================
void DrawTitleDoor(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTitleDoor03);
	
	// ���_���W�̐ݒ�(���_���)
	SetVtx4PointData(g_TitleDoor03_00VertexWk, g_Door03_00Pos, SCREEN_CENTER_X, SCREEN_CENTER_Y);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleDoor03_00VertexWk, sizeof(VERTEX_2D));

	// ���_���W�̐ݒ�(���_���)
	SetVtx4PointData(g_TitleDoor03_01VertexWk, g_Door03_01Pos, SCREEN_CENTER_X, SCREEN_CENTER_Y);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleDoor03_01VertexWk, sizeof(VERTEX_2D));

	// ���_���W�̐ݒ�(���_���)
	SetVtx4PointData(g_TitleDoor03_02VertexWk, g_Door03_02Pos, SCREEN_CENTER_X, SCREEN_CENTER_Y);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleDoor03_02VertexWk, sizeof(VERTEX_2D));

	// ���_���W�̐ݒ�(���_���)
	SetVtx4PointData(g_TitleDoor03_03VertexWk, g_Door03_03Pos, SCREEN_CENTER_X, SCREEN_CENTER_Y);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleDoor03_03VertexWk, sizeof(VERTEX_2D));

	if (g_DoorDrawFlag == true)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_D3DTextureTitleDoor01);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleDoor01VertexWk, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_D3DTextureTitleDoor02);

		// ���_���W�̐ݒ�(���_���)
		SetVtxRotData(g_TitleDoor02VertexWk, g_Door01Pos, g_DoorMovie, g_DoorAngle, g_DoorLength);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleDoor02VertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// �h�A���J���鏈��
//=============================================================================
void SetDoorFlag(bool Flag)
{
	g_DoorFlag = Flag;
}

//=============================================================================
// �X�e�[�W�J��
//=============================================================================
void SetTitleSelectStage(int STAGE)
{
	g_Stage = STAGE;
}