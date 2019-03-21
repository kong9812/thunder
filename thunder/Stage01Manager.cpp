#include "main.h"
#include "basic.h"
#include "UI.h"
#include "player.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "Stage01Collider.h"
#include "EnemyBulletManager.h"
#include "PlayerBomb.h"
#include "PlayerBulletManager.h"
#include "Stage01Background.h"
#include "Stage01Manager.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
float g_fStage01MapScrollPos;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStage01Manager(int InitType)
{
	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{		
		// ������
		InitEffectManager(FIRST_INIT);
		InitStage01Collider(FIRST_INIT);
		InitStage01Background(FIRST_INIT);
		InitEnemyBulletManager(FIRST_INIT);
		InitPlayerBulletManager(FIRST_INIT);
		InitPlayerBomb(FIRST_INIT);
		InitEnemyManager(FIRST_INIT);
		InitPlayer(FIRST_INIT);
		InitUI(FIRST_INIT);
	}

	else
	{
		// �ď�����
		InitEffectManager(RE_INIT);
		InitStage01Collider(RE_INIT);
		InitStage01Background(RE_INIT);
		InitEnemyBulletManager(RE_INIT);
		InitPlayerBulletManager(RE_INIT);
		InitPlayerBomb(RE_INIT);
		InitEnemyManager(RE_INIT);
		InitPlayer(RE_INIT);
		InitUI(RE_INIT);
	}

	g_fStage01MapScrollPos = 0.0f;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStage01Manager(void)
{
	UninitEffectManager();
	UninitStage01Collider();
	UninitStage01Background();
	UninitEnemyBulletManager();
	UninitPlayerBulletManager();
	UninitPlayerBomb();
	UninitEnemyManager();
	UninitPlayer();
	UninitUI();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStage01Manager(void)
{
	UpdateStage01Background();
	UpdateEnemyBulletManager();
	UpdatePlayerBulletManager();
	UpdatePlayerBomb();
	UpdateEnemyManager(g_fStage01MapScrollPos);
	UpdatePlayer();
	UpdateStage01Collider();
	UpdateEffectManager();
	UpdateUI(g_fStage01MapScrollPos);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStage01Manager(void)
{

	DrawStage01Collider();
	DrawStage01Background();
	DrawPlayerBomb();
	DrawEnemyBulletManager();
	DrawPlayerBulletManager();
	DrawEnemyManager();
	DrawEngineEffect();
	DrawPlayer();
	DrawEffectManager();
	DrawUI();
}

//=============================================================================
// �}�b�v�̈ʒu��ݒ�
//=============================================================================
void SetStage01MapScrollPos(float MapPos)
{
	g_fStage01MapScrollPos = MapPos;
}
