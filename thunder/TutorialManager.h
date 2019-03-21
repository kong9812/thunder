#ifndef _TUTORIAL_MANAGER_H_
#define _TUTORIAL_MANAGER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �R���g���[������
#define	TEXTURE_CONTROL				_T("data/TEXTURE/tutorial_ctrl.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y		
#define CONTROL_SIZE_X					(300)	// �v���C���[�̕�(X)
#define CONTROL_SIZE_Y					(300)	// �v���C���[�̍���(Y)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTutorialManager(int InitType);
void UninitTutorialManager(void);
void UpdateTutorialManager(void);
void DrawTutorialManager(void);

void SetTutorialMapScrollPos(float PosY);

#endif