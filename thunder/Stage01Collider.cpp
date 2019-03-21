#include "main.h"
#include "sound.h"
#include "EffectManager.h"
#include "PlayerBomb.h"
#include "EnemyBulletManager.h"
#include "PlayerBulletManager.h"
#include "PlayerBullet01.h"
#include "PlayerBullet02.h"
#include "PlayerBullet03.h"
#include "EnemyBullet01.h"
#include "EnemyBullet02.h"
#include "EnemyBullet03.h"
#include "Enemy01.h"
#include "Enemy02.h"
#include "Enemy03.h"
#include "player.h"
#include "UINumberScore.h"
#include "Stage01Collider.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// BC
bool Stage01BoundingCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float Size1, float Size2);


// [�v����[�e->�G�l�~�[]�����蔻��
void PlayerBullet01LEnemy01Collider(void);
void PlayerBullet01REnemy01Collider(void);
void PlayerBullet01LEnemy02Collider(void);
void PlayerBullet01REnemy02Collider(void);
void PlayerBullet01Enemy03Collider(void);

void PlayerBullet02LEnemy01Collider(void);
void PlayerBullet02REnemy01Collider(void);
void PlayerBullet02LEnemy02Collider(void);
void PlayerBullet02REnemy02Collider(void);
void PlayerBullet02Enemy03Collider(void);

void PlayerBullet03LEnemy01Collider(void);
void PlayerBullet03REnemy01Collider(void);
void PlayerBullet03LEnemy02Collider(void);
void PlayerBullet03REnemy02Collider(void);
void PlayerBullet03Enemy03Collider(void);

// [�v����[�K�E�Z->�G�l�~�[]�����蔻��
void PlayerBombEnemyLEnemy01Collider(void);
void PlayerBombEnemyREnemy01Collider(void);
void PlayerBombEnemyLEnemy02Collider(void);
void PlayerBombEnemyREnemy02Collider(void);
void PlayerBombEnemyEnemy03Collider(void);

// [�G�l�~�[->�v���C���[]�����蔻��
void EnemyBullet01PlayerCollider(void);
void EnemyBullet02PlayerCollider(void);
void EnemyBullet03PlayerCollider(void);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTSOUNDBUFFER8	g_pHitSoundSE;				// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStage01Collider(int InitType)
{
	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// SE���[�h
		g_pHitSoundSE = LoadSound(SE_HIT_SOUND);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStage01Collider(void)
{
	if (g_pHitSoundSE != NULL)
	{// �e�N�X�`���̊J��
		g_pHitSoundSE->Release();
		g_pHitSoundSE = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStage01Collider(void)
{
	PlayerBullet01LEnemy01Collider();
	PlayerBullet01REnemy01Collider();
	PlayerBullet01LEnemy02Collider();
	PlayerBullet01REnemy02Collider();
	PlayerBullet01Enemy03Collider();

	PlayerBullet02LEnemy01Collider();
	PlayerBullet02REnemy01Collider();
	PlayerBullet02LEnemy02Collider();
	PlayerBullet02REnemy02Collider();
	PlayerBullet02Enemy03Collider();

	PlayerBullet03LEnemy01Collider();
	PlayerBullet03REnemy01Collider();
	PlayerBullet03LEnemy02Collider();
	PlayerBullet03REnemy02Collider();
	PlayerBullet03Enemy03Collider();

	PlayerBombEnemyLEnemy01Collider();
	PlayerBombEnemyREnemy01Collider();
	PlayerBombEnemyLEnemy02Collider();
	PlayerBombEnemyREnemy02Collider();
	PlayerBombEnemyEnemy03Collider();

	EnemyBullet01PlayerCollider();
	EnemyBullet02PlayerCollider();
	EnemyBullet03PlayerCollider();

	//PlayerBombTutorialEnemyCollider();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStage01Collider(void)
{

}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[01(��) ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet01LEnemy01Collider(void)
{
	ENEMY *enemy01L = GetEnemy01Left(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_01_MAX; j++, enemy01L++)
	{
		if (enemy01L->alive == true)
		{
			PLAYERBULLET *playerbullet01 = GetPlayerBullet01(0);
			for (int i = 0; i < PLAYER_BULLET_01_MAX; i++, playerbullet01++)
			{
				if (playerbullet01->use == true)
				{
					if (Stage01BoundingCircle(enemy01L->pos, playerbullet01->pos,
						ENEMY_01_SIZE_Y / HALF, PLAYER_BULLET_01_SIZE_Y / HALF))
					{
						// SE�Đ�
						if (IsPlaying(g_pHitSoundSE) == false)
						{
							g_pHitSoundSE->SetCurrentPosition(0);
						}
						PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
						SetEffect01(enemy01L->pos);

						enemy01L->HP -= PLAYER_BULLET_01_ATK;
						enemy01L->FlashFlag = true;
						playerbullet01->use = false;

						if (enemy01L->HP <= 0)
						{
							AddScore(ENEMY_01_SCORE);
							player->EXP += ENEMY_01_EXP;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[01(�E) ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet01REnemy01Collider(void)
{
	ENEMY *enemy01R = GetEnemy01Right(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_01_MAX; j++, enemy01R++)
	{
		if (enemy01R->alive == true)
		{
			PLAYERBULLET *playerbullet01 = GetPlayerBullet01(0);
			for (int i = 0; i < PLAYER_BULLET_01_MAX; i++, playerbullet01++)
			{
				if (playerbullet01->use == true)
				{
					if (Stage01BoundingCircle(enemy01R->pos, playerbullet01->pos,
						ENEMY_01_SIZE_Y / HALF, PLAYER_BULLET_01_SIZE_Y / HALF))
					{
						// SE�Đ�
						if (IsPlaying(g_pHitSoundSE) == false)
						{
							g_pHitSoundSE->SetCurrentPosition(0);
						}
						PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
						SetEffect01(enemy01R->pos);

						enemy01R->HP -= PLAYER_BULLET_01_ATK;
						enemy01R->FlashFlag = true;
						playerbullet01->use = false;

						if (enemy01R->HP <= 0)
						{
							AddScore(ENEMY_01_SCORE);
							player->EXP += ENEMY_01_EXP;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[02(��) ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet01LEnemy02Collider(void)
{
	ENEMY *enemy02L = GetEnemy02Left(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_02_MAX; j++, enemy02L++)
	{
		if (enemy02L->alive == true)
		{
			PLAYERBULLET *playerbullet01 = GetPlayerBullet01(0);
			for (int i = 0; i < PLAYER_BULLET_01_MAX; i++, playerbullet01++)
			{
				if (playerbullet01->use == true)
				{
					if (Stage01BoundingCircle(enemy02L->pos, playerbullet01->pos,
						ENEMY_02_SIZE_Y / HALF, PLAYER_BULLET_01_SIZE_Y / HALF))
					{
						// SE�Đ�
						if (IsPlaying(g_pHitSoundSE) == false)
						{
							g_pHitSoundSE->SetCurrentPosition(0);
						}
						PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
						SetEffect01(enemy02L->pos);

						enemy02L->HP -= PLAYER_BULLET_01_ATK;
						enemy02L->FlashFlag = true;
						playerbullet01->use = false;

						if (enemy02L->HP <= 0)
						{
							AddScore(ENEMY_02_SCORE);
							player->EXP += ENEMY_02_EXP;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[02(�E) ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet01REnemy02Collider(void)
{
	ENEMY *enemy02R = GetEnemy02Right(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_02_MAX; j++, enemy02R++)
	{
		if (enemy02R->alive == true)
		{
			PLAYERBULLET *playerbullet01 = GetPlayerBullet01(0);
			for (int i = 0; i < PLAYER_BULLET_01_MAX; i++, playerbullet01++)
			{
				if (playerbullet01->use == true)
				{
					if (Stage01BoundingCircle(enemy02R->pos, playerbullet01->pos,
						ENEMY_02_SIZE_Y / HALF, PLAYER_BULLET_01_SIZE_Y / HALF))
					{
						// SE�Đ�
						if (IsPlaying(g_pHitSoundSE) == false)
						{
							g_pHitSoundSE->SetCurrentPosition(0);
						}
						PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
						SetEffect01(enemy02R->pos);

						enemy02R->HP -= PLAYER_BULLET_01_ATK;
						enemy02R->FlashFlag = true;
						playerbullet01->use = false;
					
						if (enemy02R->HP <= 0)
						{
							AddScore(ENEMY_02_SCORE);
							player->EXP += ENEMY_02_EXP;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[03 ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet01Enemy03Collider(void)
{
	ENEMY *enemy03 = GetEnemy03();
	PLAYER *player = GetPlayer();

	if (enemy03->alive == true)
	{
		PLAYERBULLET *playerbullet01 = GetPlayerBullet01(0);
		for (int i = 0; i < PLAYER_BULLET_01_MAX; i++, playerbullet01++)
		{
			if (playerbullet01->use == true)
			{
				if (Stage01BoundingCircle(enemy03->pos, playerbullet01->pos,
					ENEMY_03_SIZE_Y / HALF, PLAYER_BULLET_01_SIZE_Y / HALF))
				{
					// SE�Đ�
					if (IsPlaying(g_pHitSoundSE) == false)
					{
						g_pHitSoundSE->SetCurrentPosition(0);
					}
					PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
					SetEffect01(enemy03->pos);

					enemy03->HP -= PLAYER_BULLET_01_ATK;
					enemy03->FlashFlag = true;
					playerbullet01->use = false;
				
					if (enemy03->HP <= 0)
					{
						AddScore(ENEMY_03_SCORE);
						player->EXP += ENEMY_03_EXP;
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[01(��) ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet02LEnemy01Collider(void)
{
	ENEMY *enemy01L = GetEnemy01Left(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_01_MAX; j++, enemy01L++)
	{
		if (enemy01L->alive == true)
		{
			PLAYERBULLET *playerbullet02 = GetPlayerBullet02(0);
			for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet02++)
			{
				if (playerbullet02->use == true)
				{
					if (Stage01BoundingCircle(enemy01L->pos, playerbullet02->pos,
						ENEMY_01_SIZE_Y / HALF, PLAYER_BULLET_02_SIZE_Y / HALF))
					{
						// SE�Đ�
						if (IsPlaying(g_pHitSoundSE) == false)
						{
							g_pHitSoundSE->SetCurrentPosition(0);
						}
						PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
						SetEffect01(enemy01L->pos);

						enemy01L->HP -= PLAYER_BULLET_01_ATK;
						enemy01L->FlashFlag = true;
						playerbullet02->use = false;

						if (enemy01L->HP <= 0)
						{
							AddScore(ENEMY_01_SCORE);
							player->EXP += ENEMY_01_EXP;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[01(�E) ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet02REnemy01Collider(void)
{
	ENEMY *enemy01R = GetEnemy01Right(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_01_MAX; j++, enemy01R++)
	{
		if (enemy01R->alive == true)
		{
			PLAYERBULLET *playerbullet02 = GetPlayerBullet02(0);
			for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet02++)
			{
				if (playerbullet02->use == true)
				{
					if (Stage01BoundingCircle(enemy01R->pos, playerbullet02->pos,
						ENEMY_01_SIZE_Y / HALF, PLAYER_BULLET_02_SIZE_Y / HALF))
					{
						// SE�Đ�
						if (IsPlaying(g_pHitSoundSE) == false)
						{
							g_pHitSoundSE->SetCurrentPosition(0);
						}
						PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
						SetEffect01(enemy01R->pos);

						enemy01R->HP -= PLAYER_BULLET_01_ATK;
						enemy01R->FlashFlag = true;
						playerbullet02->use = false;

						if (enemy01R->HP <= 0)
						{
							AddScore(ENEMY_01_SCORE);
							player->EXP += ENEMY_01_EXP;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[02(��) ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet02LEnemy02Collider(void)
{
	ENEMY *enemy02L = GetEnemy02Left(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_02_MAX; j++, enemy02L++)
	{
		if (enemy02L->alive == true)
		{
			PLAYERBULLET *playerbullet02 = GetPlayerBullet02(0);
			for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet02++)
			{
				if (playerbullet02->use == true)
				{
					if (Stage01BoundingCircle(enemy02L->pos, playerbullet02->pos,
						ENEMY_02_SIZE_Y / HALF, PLAYER_BULLET_02_SIZE_Y / HALF))
					{
						// SE�Đ�
						if (IsPlaying(g_pHitSoundSE) == false)
						{
							g_pHitSoundSE->SetCurrentPosition(0);
						}
						PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
						SetEffect01(enemy02L->pos);

						enemy02L->HP -= PLAYER_BULLET_02_ATK;
						enemy02L->FlashFlag = true;
						playerbullet02->use = false;

						if (enemy02L->HP <= 0)
						{
							AddScore(ENEMY_02_SCORE);
							player->EXP += ENEMY_02_EXP;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[02(�E) ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet02REnemy02Collider(void)
{
	ENEMY *enemy02R = GetEnemy02Right(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_02_MAX; j++, enemy02R++)
	{
		if (enemy02R->alive == true)
		{
			PLAYERBULLET *playerbullet02 = GetPlayerBullet02(0);
			for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet02++)
			{
				if (playerbullet02->use == true)
				{
					if (Stage01BoundingCircle(enemy02R->pos, playerbullet02->pos,
						ENEMY_02_SIZE_Y / HALF, PLAYER_BULLET_02_SIZE_Y / HALF))
					{
						// SE�Đ�
						if (IsPlaying(g_pHitSoundSE) == false)
						{
							g_pHitSoundSE->SetCurrentPosition(0);
						}
						PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
						SetEffect01(enemy02R->pos);

						enemy02R->HP -= PLAYER_BULLET_02_ATK;
						enemy02R->FlashFlag = true;
						playerbullet02->use = false;

						if (enemy02R->HP <= 0)
						{
							AddScore(ENEMY_02_SCORE);
							player->EXP += ENEMY_02_EXP;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[03 ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet02Enemy03Collider(void)
{
	ENEMY *enemy03 = GetEnemy03();
	PLAYER *player = GetPlayer();

	if (enemy03->alive == true)
	{
		PLAYERBULLET *playerbullet02 = GetPlayerBullet02(0);
		for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet02++)
		{
			if (playerbullet02->use == true)
			{
				if (Stage01BoundingCircle(enemy03->pos, playerbullet02->pos,
					ENEMY_03_SIZE_Y / HALF, PLAYER_BULLET_02_SIZE_Y / HALF))
				{
					// SE�Đ�
					if (IsPlaying(g_pHitSoundSE) == false)
					{
						g_pHitSoundSE->SetCurrentPosition(0);
					}
					PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
					SetEffect01(enemy03->pos);

					enemy03->HP -= PLAYER_BULLET_01_ATK;
					enemy03->FlashFlag = true;
					playerbullet02->use = false;

					if (enemy03->HP <= 0)
					{
						AddScore(ENEMY_03_SCORE);
						player->EXP += ENEMY_03_EXP;
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[01(��) ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet03LEnemy01Collider(void)
{
	ENEMY *enemy01L = GetEnemy01Left(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_01_MAX; j++, enemy01L++)
	{
		if (enemy01L->alive == true)
		{
			PLAYERBULLET *playerbullet03 = GetPlayerBullet03(0);
			for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, playerbullet03++)
			{
				if (playerbullet03->use == true)
				{
					if (Stage01BoundingCircle(enemy01L->pos, playerbullet03->pos,
						ENEMY_01_SIZE_Y / HALF, PLAYER_BULLET_03_SIZE_Y / HALF))
					{
						// SE�Đ�
						if (IsPlaying(g_pHitSoundSE) == false)
						{
							g_pHitSoundSE->SetCurrentPosition(0);
						}
						PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
						SetEffect01(enemy01L->pos);

						enemy01L->HP -= PLAYER_BULLET_01_ATK;
						enemy01L->FlashFlag = true;
						playerbullet03->use = false;

						if (enemy01L->HP <= 0)
						{
							AddScore(50);
							player->EXP += 1;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[01(�E) ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet03REnemy01Collider(void)
{
	ENEMY *enemy01R = GetEnemy01Right(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_01_MAX; j++, enemy01R++)
	{
		if (enemy01R->alive == true)
		{
			PLAYERBULLET *playerbullet03 = GetPlayerBullet03(0);
			for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, playerbullet03++)
			{
				if (playerbullet03->use == true)
				{
					if (Stage01BoundingCircle(enemy01R->pos, playerbullet03->pos,
						ENEMY_01_SIZE_Y / HALF, PLAYER_BULLET_03_SIZE_Y / HALF))
					{
						// SE�Đ�
						if (IsPlaying(g_pHitSoundSE) == false)
						{
							g_pHitSoundSE->SetCurrentPosition(0);
						}
						PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
						SetEffect01(enemy01R->pos);

						enemy01R->HP -= PLAYER_BULLET_01_ATK;
						enemy01R->FlashFlag = true;
						playerbullet03->use = false;

						if (enemy01R->HP <= 0)
						{
							AddScore(50);
							player->EXP += 1;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[02(��) ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet03LEnemy02Collider(void)
{
	ENEMY *enemy02L = GetEnemy02Left(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_02_MAX; j++, enemy02L++)
	{
		if (enemy02L->alive == true)
		{
			PLAYERBULLET *playerbullet03 = GetPlayerBullet03(0);
			for (int i = 0; i < PLAYER_BULLET_02_MAX; i++, playerbullet03++)
			{
				if (playerbullet03->use == true)
				{
					if (Stage01BoundingCircle(enemy02L->pos, playerbullet03->pos,
						ENEMY_02_SIZE_Y / HALF, PLAYER_BULLET_03_SIZE_Y / HALF))
					{
						// SE�Đ�
						if (IsPlaying(g_pHitSoundSE) == false)
						{
							g_pHitSoundSE->SetCurrentPosition(0);
						}
						PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
						SetEffect01(enemy02L->pos);

						enemy02L->HP -= PLAYER_BULLET_03_ATK;
						enemy02L->FlashFlag = true;
						playerbullet03->use = false;

						if (enemy02L->HP <= 0)
						{
							AddScore(100);
							player->EXP += 1;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[02(�E) ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet03REnemy02Collider(void)
{
	ENEMY *enemy02R = GetEnemy02Right(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_02_MAX; j++, enemy02R++)
	{
		if (enemy02R->alive == true)
		{
			PLAYERBULLET *playerbullet03 = GetPlayerBullet03(0);
			for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, playerbullet03++)
			{
				if (playerbullet03->use == true)
				{
					if (Stage01BoundingCircle(enemy02R->pos, playerbullet03->pos,
						ENEMY_02_SIZE_Y / HALF, PLAYER_BULLET_03_SIZE_Y / HALF))
					{
						// SE�Đ�
						if (IsPlaying(g_pHitSoundSE) == false)
						{
							g_pHitSoundSE->SetCurrentPosition(0);
						}
						PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
						SetEffect01(enemy02R->pos);

						enemy02R->HP -= PLAYER_BULLET_03_ATK;
						enemy02R->FlashFlag = true;
						playerbullet03->use = false;

						if (enemy02R->HP <= 0)
						{
							AddScore(100);
							player->EXP += 1;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[�o���b�g �� �G�l�~�[03 ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBullet03Enemy03Collider(void)
{
	ENEMY *enemy03 = GetEnemy03();
	PLAYER *player = GetPlayer();

	if (enemy03->alive == true)
	{
		PLAYERBULLET *playerbullet03 = GetPlayerBullet03(0);
		for (int i = 0; i < PLAYER_BULLET_03_MAX; i++, playerbullet03++)
		{
			if (playerbullet03->use == true)
			{
				if (Stage01BoundingCircle(enemy03->pos, playerbullet03->pos,
					ENEMY_03_SIZE_Y / HALF, PLAYER_BULLET_03_SIZE_Y / HALF))
				{
					// SE�Đ�
					if (IsPlaying(g_pHitSoundSE) == false)
					{
						g_pHitSoundSE->SetCurrentPosition(0);
					}
					PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
					SetEffect01(enemy03->pos);

					enemy03->HP -= PLAYER_BULLET_01_ATK;
					enemy03->FlashFlag = true;
					playerbullet03->use = false;

					if (enemy03->HP <= 0)
					{
						AddScore(500);
						player->EXP += 1;
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �G�l�~�[�o���b�g01 �� �v���C���[ ] 
// �����蔻�� (BC����)
//============================================================================
void EnemyBullet01PlayerCollider(void)
{
	PLAYER *player = GetPlayer();

	if (player->alive == true)
	{
		ENEMYBULLET *enemybullet01 = GetEnemyBullet01(0);
		for (int i = 0; i < ENEMY_BULLET_01_MAX; i++, enemybullet01++)
		{
			if (enemybullet01->use == true)
			{
				if (Stage01BoundingCircle(player->pos, enemybullet01->pos,
					PLAYER_SIZE_X / 3, ENEMY_BULLET_01_SIZE_X / 3))
				{
					// SE�Đ�
					if (IsPlaying(g_pHitSoundSE) == false)
					{
						g_pHitSoundSE->SetCurrentPosition(0);
					}
					PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
					SetEffect01(player->pos);

					player->HP -= ENEMY_BULLET_01_ATK;
					player->FlashFlag = true;
					enemybullet01->use = false;
				}
			}
		}
	}
}

//=============================================================================
// [ �G�l�~�[�o���b�g02 �� �v���C���[ ] 
// �����蔻�� (BC����)
//============================================================================
void EnemyBullet02PlayerCollider(void)
{
	PLAYER *player = GetPlayer();

	if (player->alive == true)
	{
		ENEMYBULLET *enemybullet02 = GetEnemyBullet02(0);
		for (int i = 0; i < ENEMY_BULLET_02_MAX; i++, enemybullet02++)
		{
			if (enemybullet02->use == true)
			{
				if (Stage01BoundingCircle(player->pos, enemybullet02->pos,
					PLAYER_SIZE_X / 3, ENEMY_BULLET_02_SIZE_X / 3))
				{
					// SE�Đ�
					if (IsPlaying(g_pHitSoundSE) == false)
					{
						g_pHitSoundSE->SetCurrentPosition(0);
					}
					PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
					SetEffect01(player->pos);

					player->HP -= ENEMY_BULLET_02_ATK;
					player->FlashFlag = true;
					enemybullet02->use = false;
				}
			}
		}
	}
}

//=============================================================================
// [ �G�l�~�[�o���b�g03 �� �v���C���[ ] 
// �����蔻�� (BC����)
//============================================================================
void EnemyBullet03PlayerCollider(void)
{
	PLAYER *player = GetPlayer();

	if (player->alive == true)
	{
		ENEMYBULLET *enemybullet03 = GetEnemyBullet03(0);
		for (int i = 0; i < ENEMY_BULLET_01_MAX; i++, enemybullet03++)
		{
			if (enemybullet03->use == true)
			{
				if (Stage01BoundingCircle(player->pos, enemybullet03->pos,
					PLAYER_SIZE_X / 3, ENEMY_BULLET_03_SIZE_X / 3))
				{
					// SE�Đ�
					if (IsPlaying(g_pHitSoundSE) == false)
					{
						g_pHitSoundSE->SetCurrentPosition(0);
					}
					PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
					SetEffect01(player->pos);

					player->HP -= ENEMY_BULLET_03_ATK;
					player->FlashFlag = true;
					enemybullet03->use = false;
				}
			}
		}
	}
}


//=============================================================================
// [ �v���C���[���� �� �G�l�~�[01 ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBombEnemyLEnemy01Collider(void)
{
	ENEMY *enemy01L = GetEnemy01Left(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_01_MAX; j++, enemy01L++)
	{
		if (enemy01L->alive == true)
		{
			PLAYERBOMB *playerbomb = GetPlayerBomb();

			if (playerbomb->use == true)
			{
				if (Stage01BoundingCircle(enemy01L->pos, playerbomb->pos,
					ENEMY_01_SIZE_X, PLAYER_BOMB_SIZE_X))
				{
					// SE�Đ�
					if (IsPlaying(g_pHitSoundSE) == false)
					{
						g_pHitSoundSE->SetCurrentPosition(0);
					}
					PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
					SetEffect01(enemy01L->pos);

					enemy01L->HP -= PLAYER_BOMB_ATK;
					enemy01L->FlashFlag = true;

					if (enemy01L->HP <= 0)
					{
						AddScore(ENEMY_01_SCORE);
						player->EXP += ENEMY_01_EXP;
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[���� �� �G�l�~�[01 ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBombEnemyREnemy01Collider(void)
{
	ENEMY *enemy01R = GetEnemy01Right(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_01_MAX; j++, enemy01R++)
	{
		if (enemy01R->alive == true)
		{
			PLAYERBOMB *playerbomb = GetPlayerBomb();

			if (playerbomb->use == true)
			{
				if (Stage01BoundingCircle(enemy01R->pos, playerbomb->pos,
					ENEMY_01_SIZE_X, PLAYER_BOMB_SIZE_X))
				{
					// SE�Đ�
					if (IsPlaying(g_pHitSoundSE) == false)
					{
						g_pHitSoundSE->SetCurrentPosition(0);
					}
					PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
					SetEffect01(enemy01R->pos);

					enemy01R->HP -= PLAYER_BOMB_ATK;
					enemy01R->FlashFlag = true;

					if (enemy01R->HP <= 0)
					{
						AddScore(ENEMY_01_SCORE);
						player->EXP += ENEMY_01_EXP;
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[���� �� �G�l�~�[02 ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBombEnemyLEnemy02Collider(void)
{
	ENEMY *enemy02L = GetEnemy02Left(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_02_MAX; j++, enemy02L++)
	{
		if (enemy02L->alive == true)
		{
			PLAYERBOMB *playerbomb = GetPlayerBomb();

			if (playerbomb->use == true)
			{
				if (Stage01BoundingCircle(enemy02L->pos, playerbomb->pos,
					ENEMY_02_SIZE_X, PLAYER_BOMB_SIZE_X))
				{
					// SE�Đ�
					if (IsPlaying(g_pHitSoundSE) == false)
					{
						g_pHitSoundSE->SetCurrentPosition(0);
					}
					PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
					SetEffect01(enemy02L->pos);

					enemy02L->HP -= PLAYER_BOMB_ATK;
					enemy02L->FlashFlag = true;

					if (enemy02L->HP <= 0)
					{
						AddScore(ENEMY_02_SCORE);
						player->EXP += ENEMY_02_EXP;
					}
				}
			}
		}
	}

}

//=============================================================================
// [ �v���C���[���� �� �G�l�~�[02 ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBombEnemyREnemy02Collider(void)
{
	ENEMY *enemy02R = GetEnemy02Right(0);
	PLAYER *player = GetPlayer();

	for (int j = 0; j < ENEMY_02_MAX; j++, enemy02R++)
	{
		if (enemy02R->alive == true)
		{
			PLAYERBOMB *playerbomb = GetPlayerBomb();

			if (playerbomb->use == true)
			{
				if (Stage01BoundingCircle(enemy02R->pos, playerbomb->pos,
					ENEMY_02_SIZE_X, PLAYER_BOMB_SIZE_X))
				{
					// SE�Đ�
					if (IsPlaying(g_pHitSoundSE) == false)
					{
						g_pHitSoundSE->SetCurrentPosition(0);
					}
					PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
					SetEffect01(enemy02R->pos);

					enemy02R->HP -= PLAYER_BOMB_ATK;
					enemy02R->FlashFlag = true;

					if (enemy02R->HP <= 0)
					{
						AddScore(ENEMY_02_SCORE);
						player->EXP += ENEMY_02_EXP;
					}
				}
			}
		}
	}
}

//=============================================================================
// [ �v���C���[���� �� �G�l�~�[03 ] 
// �����蔻�� (BC����)
//============================================================================
void PlayerBombEnemyEnemy03Collider(void)
{
	ENEMY *enemy03 = GetEnemy03();
	PLAYER *player = GetPlayer();

	if (enemy03->alive == true)
	{
		PLAYERBOMB *playerbomb = GetPlayerBomb();

		if (playerbomb->use == true)
		{
			if (Stage01BoundingCircle(enemy03->pos, playerbomb->pos,
				ENEMY_03_SIZE_X, PLAYER_BOMB_SIZE_X))
			{
				// SE�Đ�
				if (IsPlaying(g_pHitSoundSE) == false)
				{
					g_pHitSoundSE->SetCurrentPosition(0);
				}
				PlaySound(g_pHitSoundSE, E_DS8_FLAG_NONE);
				SetEffect01(enemy03->pos);

				enemy03->HP -= PLAYER_BOMB_ATK;
				enemy03->FlashFlag = true;

				if (enemy03->HP <= 0)
				{
					AddScore(ENEMY_03_SCORE);
					player->EXP += ENEMY_03_EXP;
				}
			}
		}
	}
}

//=============================================================================
// �����蔻�� (BC����)
//============================================================================
bool Stage01BoundingCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float Size1, float Size2)
{
	if ((Size1 + Size2)*(Size1 + Size2) >
		(pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y))
	{
		return true;
	}
	return false;
}