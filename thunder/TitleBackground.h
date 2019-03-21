#ifndef _TITLE_BACKGROUND_H_
#define _TITLE_BACKGROUND_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �^�C�g�����(�w�i)
#define	TEXTURE_TITLE				_T("data/TEXTURE/GameBackground.jpg")	// �ǂݍ��ރe�N�X�`���t�@�C����
// ���W
#define TITLE_POS_X					(0.0f)				// �^�C�g�����(�w�i)�̕\���ʒu(X)
#define TITLE_POS_Y					(0.0f)				// �^�C�g�����(�w�i)�̕\���ʒu(Y)
#define TITLE_POS_Z					(0.0f)				// �^�C�g�����(�w�i)�̕\���ʒu(Z)
// �T�C�Y
#define TITLE_SIZE_X				(SCREEN_WIDTH)		// �^�C�g�����(�w�i)�̕�(X)
#define TITLE_SIZE_Y				(SCREEN_HEIGHT)		// �^�C�g�����(�w�i)�̍���(Y)
// �X�N���[��
#define TITLE_SCROLL_SPEED			(0.001f)			// �^�C�g�����(�w�i)�̃X�N���[�����x

// �^�C�g�����(��)
#define	TEXTURE_TITLE_WALL			_T("data/TEXTURE/TekWall.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// ���W
#define TITLE_WALL_POS_X			(0.0f)				// �^�C�g�����(��)�̕\���ʒu(X)
#define TITLE_WALL_POS_Y			(0.0f)				// �^�C�g�����(��)�̕\���ʒu(Y)
#define TITLE_WALL_POS_Z			(0.0f)				// �^�C�g�����(��)�̕\���ʒu(Z)
// �T�C�Y															 
#define TITLE_WALL_SIZE_X			(SCREEN_WIDTH)		// �^�C�g�����(��)�̕�(X)
#define TITLE_WALL_SIZE_Y			(SCREEN_HEIGHT)		// �^�C�g�����(��)�̍���(Y)

// �^�C�g�����(���O)
#define	TEXTURE_TITLE_NAME			_T("data/TEXTURE/name.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
// ���W
#define	TITLE_NAME_POS_X			(398.5f)			// �^�C�g�����(���O)�̕\���ʒu(X)
#define	TITLE_NAME_POS_Y			(70.0f)				// �^�C�g�����(���O)�̕\���ʒu(Y)
#define TITLE_NAME_POS_Z			(0.0f)				// �^�C�g�����(���O)�̕\���ʒu(Z)
// �T�C�Y
#define	TITLE_NAME_SIZE_X			(483.0f)			// �^�C�g�����(���O)�̕�(X)
#define	TITLE_NAME_SIZE_Y			(85.0f)				// �^�C�g�����(���O)�̍���(Y)
// ���ˌ�
#define	TITLE_NAME_COLOR_RED		D3DCOLOR_RGBA(255,0,0,255)		// �^�C�g�����(���O)�̔��ˌ�(��)
#define	TITLE_NAME_COLOR_BLACK		D3DCOLOR_RGBA(0,0,0,255)		// �^�C�g�����(���O)�̔��ˌ�(��)

// ���쌠�錾
#define	TEXTURE_TITLE_COPYRIGHT		_T("data/TEXTURE/copyright.png")// �ǂݍ��ރe�N�X�`���t�@�C����
// ���W
#define	TITLE_COPYRIGHT_POS_X			(1083.0f)		// �^�C�g�����(���O)�̕\���ʒu(X)
#define	TITLE_COPYRIGHT_POS_Y			(708.0f)		// �^�C�g�����(���O)�̕\���ʒu(Y)
#define TITLE_COPYRIGHT_POS_Z			(0.0f)			// �^�C�g�����(���O)�̕\���ʒu(Z)
// �T�C�Y											
#define	TITLE_COPYRIGHT_SIZE_X			(197.0f)		// ���쌠�錾�̕�(X)
#define	TITLE_COPYRIGHT_SIZE_Y			(12.0f)			// ���쌠�錾�̍���(Y)

// �^�C�g�����(�h�A/��)
// ��g
#define	TEXTURE_DOOR_01			_T("data/TEXTURE/TekDoor-1.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// ��
#define	TEXTURE_DOOR_02			_T("data/TEXTURE/TekDoor-2.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// ��
#define	TEXTURE_DOOR_03			_T("data/TEXTURE/TekDoor_3.jpg")	// �ǂݍ��ރe�N�X�`���t�@�C����
// ���W
#define DOOR_POS_X					(280.0f)			// �^�C�g�����(�h�A)�̕\���ʒu(X)
#define DOOR_POS_Y					(0.0f)				// �^�C�g�����(�h�A)�̕\���ʒu(Y)
#define DOOR_POS_Z					(0.0f)				// �^�C�g�����(�h�A)�̕\���ʒu(Z)
// �T�C�Y															 
#define DOOR_SIZE_X					(720)				// �^�C�g�����(�h�A)�̕�(X)
#define DOOR_SIZE_Y					(720)				// �^�C�g�����(�h�A)�̍���(Y)
// ���[�e�[�V����	
#define DOOR_SCROLL_SPEED			(0.01f)				// �^�C�g�����(�h�A)�̃��[�e�[�V�������x
#define DOOR_SCROLL_MAX				(0.7f)				// �^�C�g�����(�h�A)�̃��[�e�[�V�������E
#define	DOOR_MOVIE_Z				(-0.8f)				// �^�C�g�����(�h�A)�̏����p�x
// �ړ�
#define DOOR_MOVE_SPEED				(10)				// �^�C�g�����(�h�A)�̈ړ����x
// �e�N�X�`�������p
#define DOOR_CUT_PATTERN_X			(2)					// �e�N�X�`����������(X)
#define DOOR_CUT_PATTERN_Y			(2)					// �e�N�X�`����������(Y)
#define DOOR_CUT_01_SIZE_X			(0.5f)				// �e�N�X�`���̕����̃T�C�Y(X)
#define DOOR_CUT_01_SIZE_Y			(0.5f)				// �e�N�X�`���̕����̃T�C�Y(Y)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitleBackground(int InitType);
void UninitTitleBackground(void);
void UpdateTitleBackground(void);
void DrawTitleBackground(bool DrawFlag);

void SetDoorFlag(bool Flag);
void SetTitleSelectStage(int STAGE);

#endif
