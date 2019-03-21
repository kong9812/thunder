#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// UI�摜
#define	TEXTURE_UI	_T("data/TEXTURE/UI.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y
#define RIGHT_UI_SIZE_X		(320)
#define RIGHT_UI_SIZE_Y		(720)
// ���W
#define UI_POS_X			(SCREEN_WIDTH - RIGHT_UI_SIZE_X)
// ����
#define TEXTURE_UI_NUMBER			_T("data/TEXTURE/UINumber.png")	// �T���v���p�摜
// �T�C�Y	
#define UI_NUMBER_SIZE_X				(20)		// �e�N�X�`���T�C�Y
#define UI_NUMBER_SIZE_Y				(40)		// ����
// �A�j���[�V�����p�^�[��
#define UI_NUMBER_PATTERN_DIVIDE_X		(5)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define UI_NUMBER_PATTERN_DIVIDE_Y		(2)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define UI_NUMBER_ANIM_PATTERN_NUM		(UI_NUMBER_PATTERN_DIVIDE_X*UI_NUMBER_PATTERN_DIVIDE_Y)
#define TIME_UI_NUMBER_ANIMATION		(100)		// �A�j���[�V�����̐؂�ւ��J�E���g

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// UINumber�\����
{
	D3DXVECTOR3				pos;				// ���W

	int						value;				// �l

}UINUMBER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUI(int InitType);
void UninitUI(void);
void UpdateUI(float MapPos);
void DrawUI(void);

#endif