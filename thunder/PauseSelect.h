#ifndef _PAUSE_SELECT_H_
#define _PAUSE_SELECT_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ReturnToGame�摜
#define	TEXTURE_PAUSE_RETURNTOGAME	_T("data/TEXTURE/ReturnToGame.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y
#define PAUSE_RETURNTOGAME_SIZE_X	(243)		// �|�[�YUI�̕�(X)
#define PAUSE_RETURNTOGAME_SIZE_Y	(18.75f)	// �|�[�YUI�̍���(Y)
// ���W
#define PAUSE_RETURNTOGAME_POS_X	(SCREEN_WIDTH/HALF-PAUSE_RETURNTOGAME_SIZE_X/HALF)	
#define PAUSE_RETURNTOGAME_POS_Y	(350)	

// BackToTittle�摜
#define	TEXTURE_PAUSE_BACKTOTITTLE	_T("data/TEXTURE/BackToTittle.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y
#define PAUSE_BACKTOTITTLE_SIZE_X	(243)		// �|�[�YUI�̕�(X)
#define PAUSE_BACKTOTITTLE_SIZE_Y	(18.75f)	// �|�[�YUI�̍���(Y)
// ���W		
#define PAUSE_BACKTOTITTLE_POS_X	(SCREEN_WIDTH/HALF-PAUSE_BACKTOTITTLE_SIZE_X/HALF)	
#define PAUSE_BACKTOTITTLE_POS_Y	(390)	

// QuitGame�摜
#define	TEXTURE_PAUSE_QUITGAME		_T("data/TEXTURE/QuitGame.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y
#define PAUSE_QUITGAME_SIZE_X		(108)		// �|�[�YUI�̕�(X)
#define PAUSE_QUITGAME_SIZE_Y		(18.75f)	// �|�[�YUI�̍���(Y)
// ���W		
#define PAUSE_QUITGAME_POS_X		(SCREEN_WIDTH/HALF-PAUSE_QUITGAME_SIZE_X/HALF)	
#define PAUSE_QUITGAME_POS_Y		(430)	


#define PAUSE_SELECT_RGBA			D3DCOLOR_RGBA(0,0,0,255)		// �I�����ꂽ��Ԃ̐F

#define PAUSE_NTSELECT_RGBA			D3DCOLOR_RGBA(255,255,255,255)	// �I������ĂȂ���Ԃ̐F



//*****************************************************************************
// �萔��`(enum��`)
//*****************************************************************************
enum PAUSE_SELECT		// �^�C�g���̑I��萔
{
	PAUSE_RETURN_TO_GAME,
	PAUSE_BACK_TO_TITLE,
	PAUSE_QUIT_GAME
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPauseSelect(int InitType);
void UninitPauseSelect(void);
void UpdatePauseSelect(int STAGE);
void DrawPauseSelect(void);

#endif