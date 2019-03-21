#ifndef _STAGE_01_MANAGER_H_
#define _STAGE_01_MANAGER_H_




//*****************************************************************************
// ç\ë¢ëÃêÈåæ
//*****************************************************************************
HRESULT InitStage01Manager(int InitType);
void UninitStage01Manager(void);
void UpdateStage01Manager(void);
void DrawStage01Manager(void);

void SetStage01MapScrollPos(float MapPos);

#endif