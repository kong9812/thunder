#ifndef ___TITLESELECT_H___
#define ___TITLESELECT_H___

//*****************************************************************************
//�}�N����`
//*****************************************************************************
// �^�C�g���̑I����(�X�^�[�g)		
#define	TEXTURE_START_LOGO			_T("data/TEXTURE/start.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// ���W
#define START_LOGO_POS_X		(532.5f)		// �X�^�[�g���S�̕\���ʒu(X)
#define	START_LOGO_POS_Y		(360.0f)		// �X�^�[�g���S�̕\���ʒu(Y)
#define	START_LOGO_POS_Z		(0.0f)			// �X�^�[�g���S�̕\���ʒu(Z)
// �T�C�Y
#define	START_LOGO_SIZE_X		(215.0f)		// �X�^�[�g���S�̕�(X)
#define	START_LOGO_SIZE_Y		(53.0f)			// �X�^�[�g���S�̍���(Y)

// �^�C�g���̑I����(�`���[�g���A��)
#define	TEXTURE_TUTORIAL_LOGO		_T("data/TEXTURE/tutorial.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
// ���W
#define	TUTORIAL_LOGO_POS_X		(479.5f)		// �`���[�g���A�����S�̕\���ʒu(X)
#define	TUTORIAL_LOGO_POS_Y		(440.0f)		// �`���[�g���A�����S�̕\���ʒu(Y)
#define	TUTORIAL_LOGO_POS_Z		(0.0f)			// �`���[�g���A�����S�̕\���ʒu(Z)
// �T�C�Y											
#define	TUTORIAL_LOGO_SIZE_X	(321.0f)		// �`���[�g���A�����S�̕�(X)
#define	TUTORIAL_LOGO_SIZE_Y	(53.0f)			// �`���[�g���A�����S�̍���(Y)

// �^�C�g���̑I����(�R���t�B�O)
#define	TEXTURE_CONFIG_LOGO		_T("data/TEXTURE/config.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
// ���W
#define	CONFIG_LOGO_POS_X		(529.0f)		// �R���t�B�O���S�̕\���ʒu(X)
#define	CONFIG_LOGO_POS_Y		(520.0f)		// �R���t�B�O���S�̕\���ʒu(Y)
#define	CONFIG_LOGO_POS_Z		(0.0f)			// �R���t�B�O���S�̕\���ʒu(Z)
// �T�C�Y											
#define	CONFIG_LOGO_SIZE_X		(222.0f)		// �R���t�B�O���S�̕�(X)
#define	CONFIG_LOGO_SIZE_Y		(53.0f)			// �R���t�B�O���S�̍���(Y)

// �^�C�g���̑I����(�G���h)
#define	TEXTURE_END_LOGO			_T("data/TEXTURE/end.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
// ���W
#define	END_LOGO_POS_X			(576.5f)		// �G���h���S�̕\���ʒu(X)
#define	END_LOGO_POS_Y			(600.0f)		// �G���h���S�̕\���ʒu(Y)
#define	END_LOGO_POS_Z			(0.0f)			// �G���h���S�̕\���ʒu(Z)
// �T�C�Y
#define	END_LOGO_SIZE_X			(127.0f)		// �G���h���S�̕�(X)
#define	END_LOGO_SIZE_Y			(53.0f)			// �G���h���S�̍���(Y)

// �^�C�g���̑I����(���)
#define	TEXTURE_SELECT_LOGO_LEFT	_T("data/TEXTURE/title_select_left.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// �^�C�g���̑I����(���)
#define	TEXTURE_SELECT_LOGO_RIGHT	_T("data/TEXTURE/title_select_right.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// ���W
#define	SELECT_INTERVAL			(100.0f)		// ���ƑI�����̊Ԋu(X)
// �T�C�Y
#define	SELECT_LOGO_SIZE_X		(55.42f)		// ���̕�(X)
#define	SELECT_LOGO_SIZE_Y		(53.86f)		// ���̍���(Y)
// ���ˌ�
#define	TITLE_SELECT_COLOR_RED	D3DCOLOR_RGBA(255,0,0,255)	// �^�C�g�����(���O)�̔��ˌ�(��)


// �_�ŗp
#define SELECT_FLASHING_ALPHA_ON		D3DCOLOR_RGBA(255, 255, 255, 255)	// �_�̏�Ԃ̃��l
#define SELECT_FLASHING_ALPHA_OFF		D3DCOLOR_RGBA(255, 255, 255, 0)		// �ł̏�Ԃ̃��l
#define SELECT_FLASHING_HOLD_TIME		(10)								// �_/�ł̏�Ԏ���
#define SELECT_FLASHING_RESET			(SELECT_FLASHING_HOLD_TIME*2)		// �_�Ń��Z�b�g

//*****************************************************************************
// �萔��`(enum��`)
//*****************************************************************************
enum TITLE_SELECT		// �^�C�g���̑I��萔
{
	TITLE_START,
	TITLE_TUTORIAL,
	TITLE_CONFIG,
	TITLE_END
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitleSelect(int InitType);
void UninitTitleSelect(void);
void UpdateTitleSelect(void);
void DrawTitleSelect(void);

#endif