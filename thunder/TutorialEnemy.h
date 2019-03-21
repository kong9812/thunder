#ifndef _TUTORIAL_ENEMY_H_
#define _TUTORIAL_ENEMY_H_

#include "Enemy01.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// チュトリアルエネミーの情報
#define TUTORIAL_ENEMY_SPAWN_POS		D3DXVECTOR3(300.0f, -10.0f, 0.0f) // 初期位置
#define TUTORIAL_ENEMY_STOP_POS_Y		(-0.2f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTutorialEnemy(int InitType);
void UninitTutorialEnemy(void);
void UpdateTutorialEnemy(float MapPos);
void DrawTutorialEnemy(void);
ENEMY *GetTutorialEnemy(void);

#endif