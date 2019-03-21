#ifndef _TUTORIAL_PLAYER_BULLET_H_
#define _TUTORIAL_PLAYER_BULLET_H_

#include "PlayerBulletManager.h"
#include "PlayerBullet03.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTutorialPlayerBullet(int InitType);
void UninitTutorialPlayerBullet(void);
void UpdateTutorialPlayerBullet(void);
void DrawTutorialPlayerBullet(void);

void SetTutorialPlayerBullet(D3DXVECTOR3 PlayerPos, int BulletPos);

PLAYERBULLET *GetTutorialPlayerBullet(int no);

#endif