#ifndef _TUTORIAL_PLAYER_BOMB_H_
#define _TUTORIAL_PLAYER_BOMB_H_

#include "main.h"
#include "player.h"
#include "PlayerBomb.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �\���̐錾
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTutorialPlayerBomb(int InitType);
void UninitTutorialPlayerBomb(void);
void UpdateTutorialPlayerBomb(void);
void DrawTutorialPlayerBomb(void);

void SetTutorialPlayerBomb(void);
PLAYERBOMB *GetTutorialPlayerBomb(void);

#endif