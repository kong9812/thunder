#ifndef _TUTORIAL_UI_H_
#define _TUTORIAL_UI_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// UI�w�i
#define TEXTURE_TUTORIAL_UI		_T("data/TEXTURE/tutorialUI.png")			// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTutorialUI(int InitType);
void UninitTutorialUI(void);
void UpdateTutorialUI(void);
void DrawTutorialUI(void);

#endif
