#ifndef _TUTORIAL_PLAYER_H_
#define _TUTORIAL_PLAYER_H_

#include "player.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTutorialPlayer(int InitType);
void UninitTutorialPlayer(void);
void UpdateTutorialPlayer(void);
void DrawTutorialPlayer(void);
void DrawTutorialEngineEffect(void);
PLAYER *GetTutorialPlayer(void);

#endif