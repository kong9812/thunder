#ifndef _STAGE_01_BACKGROUND_H_
#define _STAGE_01_BACKGROUND_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// STAGE_01�w�i_01									
// �w�i���
#define	STAGE_01_BACKGROUND_01_SCROLL_SPEED	(0.001f)	// �X�N���[���X�s�[�h

// STAGE_01�w�i_02
// �w�i�摜
#define TEXTURT_STAGE_01_BACKGROUND_02		_T("data/TEXTURE/Stage01Background.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y											 
#define STAGE_01_BACKGROUND_02_SIZE_X		(960)		// �w�i�̕�(X)
#define STAGE_01_BACKGROUND_02_SIZE_Y		(760)		// �w�i�̍���(Y)
// �w�i���
#define	STAGE_01_BACKGROUND_02_SCROLL_SPEED	(0.002f)	// �X�N���[���X�s�[�h

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitStage01Background(int InitType);
void UninitStage01Background(void);
void UpdateStage01Background(void);
void DrawStage01Background(void);

#endif