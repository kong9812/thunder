#include "main.h"
#include "sound.h"
#include "EffectManager.h"
#include "PlayerBulletManager.h"
#include "TutorialPlayerBullet.h"
#include "TutorialPlayerBomb.h"
#include "TutorialEnemy.h"
#include "TutorialCollider.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// BC
bool TutorialBoundingCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float Size1, float Size2);


// �����蔻��
void PlayerBullet01TutorialEnemyCollider(void);
void PlayerBombTutorialEnemyCollider(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTSOUNDBUFFER8	g_pTutorialHitSoundSE;				// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTutorialCollider(int InitType)
{
	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// SE���[�h
		g_pTutorialHitSoundSE = LoadSound(SE_HIT_SOUND);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorialCollider(void)
{


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorialCollider(void)
{
	PlayerBullet01TutorialEnemyCollider();
	PlayerBombTutorialEnemyCollider();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorialCollider(void)
{

}

//=============================================================================
// [ �`���g���A���v���C���[�o���b�g �� �`���g���A���G�l�~�[ ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet01TutorialEnemyCollider(void)
{
	ENEMY *tutorialenemy = GetTutorialEnemy();
	PLAYERBULLET *tutorialplayerbullet = GetTutorialPlayerBullet(0);


	for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, tutorialplayerbullet++)
	{
		if (tutorialplayerbullet->use == true)
		{
			if (TutorialBoundingCircle(tutorialenemy->pos, tutorialplayerbullet->pos,
				ENEMY_01_SIZE_Y / HALF, PLAYER_BULLET_03_SIZE_Y / HALF))
			{
				// SE�Đ�
				if (IsPlaying(g_pTutorialHitSoundSE) == false)
				{
					g_pTutorialHitSoundSE->SetCurrentPosition(0);
				}
				PlaySound(g_pTutorialHitSoundSE, E_DS8_FLAG_NONE);
				SetEffect01(tutorialenemy->pos);
				tutorialenemy->FlashFlag = true;
				tutorialplayerbullet->use = false;
			}
		}
	}

}

//=============================================================================
// [ �`���g���A���v���C���[���� �� �`���g���A���G�l�~�[ ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBombTutorialEnemyCollider(void)
{
	ENEMY *tutorialenemy = GetTutorialEnemy();
	PLAYERBOMB *tutorialplayerbomb = GetTutorialPlayerBomb();


	if (tutorialplayerbomb->use == true)
	{
		if (TutorialBoundingCircle(tutorialenemy->pos, tutorialplayerbomb->pos,
			ENEMY_01_SIZE_Y / HALF, PLAYER_BOMB_SIZE_Y / HALF))
		{
			// SE�Đ�
			if (IsPlaying(g_pTutorialHitSoundSE) == false)
			{
				g_pTutorialHitSoundSE->SetCurrentPosition(0);
			}
			PlaySound(g_pTutorialHitSoundSE, E_DS8_FLAG_NONE);
			SetEffect01(tutorialenemy->pos);
			tutorialenemy->FlashFlag = true;
		}
	}
}


//=============================================================================
// �����蔻�� (BC����)
//============================================================================
bool TutorialBoundingCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float Size1, float Size2)
{
	if ((Size1 + Size2)*(Size1 + Size2) >
		(pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y))
	{
		return true;
	}
	return false;
}