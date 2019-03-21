#include "main.h"
#include "basic.h"
#include "player.h"
#include "input.h"
#include "sound.h"
#include "UI.h"
#include "TutorialUI.h"
#include "TutorialPlayerBomb.h"
#include "PlayerBulletManager.h"
#include "TutorialPlayerBullet.h"
#include "TutorialPlayer.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void TutorialPlayerKeyboardControl(void);	// �L�[�{�[�h����
void TutorialPlayerEngineEffect(void);		// �G���W���G�t�F�N�g
void TutorialPlayerInScreen(void);			// �X�N���[���ɓ���A�j���V����

void TutorialPlayerPause(void);				// �|�[�Y
void TutorialPlayerShoot(void);				// �e����
void TutorialPlayerBomb(void);				// ����

void SetTutorialPlayerFlashing(void);		// �_�ŏ���
void SetTutorialPlayerFlashingOn(void);		// �_�ŏ���(�_)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialPlayer = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureTutorialEngineEffect = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECTSOUNDBUFFER8	g_pTutorialPlayerRespawnSE;					// SE�p�o�b�t�@
LPDIRECTSOUNDBUFFER8	g_pTutorialPlayerStartSE;					// SE�p�o�b�t�@

VERTEX_2D				g_TutorialPlayerVertexWk[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_TutorialEngineEffectVertexWk[NUM_VERTEX];	// ���_���i�[���[�N

PLAYER					TutorialPlayerWk;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTutorialPlayer(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *tutorialplayer = GetTutorialPlayer();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PLAYER,							// �t�@�C���̖��O
		&g_D3DTextureTutorialPlayer);			// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_ENGINE_EFFECT,					// �t�@�C���̖��O
		&g_D3DTextureTutorialEngineEffect);		// �ǂݍ��ރ������[

		// SE���[�h
		g_pTutorialPlayerRespawnSE = LoadSound(SE_PLAYER_RESPAWN);
		g_pTutorialPlayerStartSE = LoadSound(SE_PLAYER_START);
	}

	tutorialplayer->pos = PLAYER_SPAWN_POS;
	tutorialplayer->alive = true;
	tutorialplayer->StartSE = true;
	tutorialplayer->MainControl = false;
	tutorialplayer->ReSpawnSE = true;
	tutorialplayer->HP = PLAYER_HP_MAX;
	tutorialplayer->EXP = 0;
	tutorialplayer->PatternAnim = 0;
	tutorialplayer->FlashingCount = 0;
	tutorialplayer->CountShoot = 0;
	tutorialplayer->CountAnim = 0;
	tutorialplayer->EffectPos = D3DXVECTOR3(tutorialplayer->pos.x + PLAYER_SIZE_X / 3, tutorialplayer->pos.y + PLAYER_SIZE_Y / HALF, 0.0f);

	// ���_�t�H�[�}�b�g(�`���g���A���v���C���[)
	MakeVtx4PointData(g_TutorialPlayerVertexWk,			// ���_���i�[���[�N
	tutorialplayer->pos,								// ���WX,Y,Z
	PLAYER_SIZE_X, PLAYER_SIZE_Y);						// �T�C�YX,Y

	// ���_�t�H�[�}�b�g(�G���W���G�t�F�N�g)
	MakeVtx4PointData(g_TutorialEngineEffectVertexWk,	// ���_���i�[���[�N
	tutorialplayer->EffectPos,							// ���WX,Y,Z
	ENGINE_EFFECT_SIZE_X, ENGINE_EFFECT_SIZE_Y);		// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorialPlayer(void)
{
	if (g_D3DTextureTutorialPlayer != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTutorialPlayer->Release();
		g_D3DTextureTutorialPlayer = NULL;
	}

	if (g_D3DTextureTutorialEngineEffect != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTutorialEngineEffect->Release();
		g_D3DTextureTutorialEngineEffect = NULL;
	}

	if (g_pTutorialPlayerRespawnSE != NULL)
	{
		g_pTutorialPlayerRespawnSE->Release();
		g_pTutorialPlayerRespawnSE = NULL;
	}

	if (g_pTutorialPlayerStartSE != NULL)
	{
		g_pTutorialPlayerStartSE->Release();
		g_pTutorialPlayerStartSE = NULL;
	}	
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorialPlayer(void)
{
	PLAYER *tutorialplayer = GetTutorialPlayer();
	
	if (tutorialplayer->MainControl == true)
	{
		TutorialPlayerKeyboardControl();
		TutorialPlayerEngineEffect();
		TutorialPlayerPause();
		TutorialPlayerShoot();
		TutorialPlayerBomb();
	}

	if ((tutorialplayer->pos.y >= PLAYER_START_POS_Y) && (tutorialplayer->MainControl == false))
	{
		// SE�Đ�
		if ((IsPlaying(g_pTutorialPlayerRespawnSE) == false)&&
			tutorialplayer->ReSpawnSE == true)
		{
			g_pTutorialPlayerRespawnSE->SetCurrentPosition(0);
			PlaySound(g_pTutorialPlayerRespawnSE, E_DS8_FLAG_NONE);
			tutorialplayer->ReSpawnSE = false;
		}

		// SE�Đ�
		if ((IsPlaying(g_pTutorialPlayerRespawnSE) == false) &&
			tutorialplayer->StartSE == true)
		{
			g_pTutorialPlayerStartSE->SetCurrentPosition(0);
			PlaySound(g_pTutorialPlayerStartSE, E_DS8_FLAG_NONE);
			tutorialplayer->StartSE = false;
		}

		TutorialPlayerInScreen();
		tutorialplayer->MainControl = false;
	}

	else if (tutorialplayer->pos.y < SCREEN_HEIGHT)
	{
		

		SetTutorialPlayerFlashingOn();
		tutorialplayer->MainControl = true;
		tutorialplayer->ReSpawnSE = true;
		tutorialplayer->StartSE = true;
	}
}

//=============================================================================
// �L�[�{�[�h����
//=============================================================================
void TutorialPlayerKeyboardControl()
{
	PLAYER *tutorialplayer = GetTutorialPlayer();

	if (GetKeyboardPress(DIK_W))	 // ��
	{
		if (GetKeyboardPress(DIK_A))	 // ����
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // ����
			{
				tutorialplayer->pos.y -= cosf(45)*PLAYER_SHIFT_SPEED;
				tutorialplayer->pos.x -= cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				tutorialplayer->pos.y -= cosf(45)*PLAYER_NORMAL_SPEED;
				tutorialplayer->pos.x -= cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else	 if (GetKeyboardPress(DIK_D)) // �E��
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // ����
			{
				tutorialplayer->pos.y -= cosf(45)*PLAYER_SHIFT_SPEED;
				tutorialplayer->pos.x += cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				tutorialplayer->pos.y -= cosf(45)*PLAYER_NORMAL_SPEED;
				tutorialplayer->pos.x += cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // ����
			{
				tutorialplayer->pos.y -= PLAYER_SHIFT_SPEED;
			}
			else
			{
				tutorialplayer->pos.y -= PLAYER_NORMAL_SPEED;
			}
		}
		
	}

	else if (GetKeyboardPress(DIK_S)) // ��
	{
		if (GetKeyboardPress(DIK_A)) // ����
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // ����
			{
				tutorialplayer->pos.y += cosf(45)*PLAYER_SHIFT_SPEED;
				tutorialplayer->pos.x -= cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				tutorialplayer->pos.y += cosf(45)*PLAYER_NORMAL_SPEED;
				tutorialplayer->pos.x -= cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else if (GetKeyboardPress(DIK_D)) // �E��
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // ����
			{
				tutorialplayer->pos.y += cosf(45)*PLAYER_SHIFT_SPEED;
				tutorialplayer->pos.x += cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				tutorialplayer->pos.y += cosf(45)*PLAYER_NORMAL_SPEED;
				tutorialplayer->pos.x += cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // ����
			{
				tutorialplayer->pos.y += PLAYER_SHIFT_SPEED;
			}
			else
			{
				tutorialplayer->pos.y += PLAYER_NORMAL_SPEED;
			}
		}
	}

	else if (GetKeyboardPress(DIK_A)) // ��
	{
		if (GetKeyboardPress(DIK_LSHIFT)) // ����
		{
			tutorialplayer->pos.x -= PLAYER_SHIFT_SPEED;
		}
		else
		{
			tutorialplayer->pos.x -= PLAYER_NORMAL_SPEED;
		}
	}

	else if (GetKeyboardPress(DIK_D)) // �E
	{
		if (GetKeyboardPress(DIK_LSHIFT)) // ����
		{
			tutorialplayer->pos.x += PLAYER_SHIFT_SPEED;
		}
		else
		{
			tutorialplayer->pos.x += PLAYER_NORMAL_SPEED;
		}
	}

	if (tutorialplayer->pos.x < 0.0f)
	{
		tutorialplayer->pos.x = 0.0f;
	}

	if (tutorialplayer->pos.y < 0.0f)
	{
		tutorialplayer->pos.y = 0.0f;
	}

	if (tutorialplayer->pos.x > UI_POS_X - PLAYER_SIZE_X)
	{
		tutorialplayer->pos.x = UI_POS_X - PLAYER_SIZE_X;
	}

	if (tutorialplayer->pos.y > SCREEN_HEIGHT - PLAYER_SIZE_Y)
	{
		tutorialplayer->pos.y = SCREEN_HEIGHT - PLAYER_SIZE_Y;
	}
}

//=============================================================================
// �|�[�Y
//=============================================================================
void TutorialPlayerPause(void)
{
	if (GetKeyboardTrigger(DIK_P))
	{
		SetPauseStage(STAGE_TUTORIAL);
		SetStage(STAGE_PAUSE);
	}
}

//=============================================================================
// �e����
//=============================================================================
void TutorialPlayerShoot(void)
{
	PLAYER *tutorialplayer = GetTutorialPlayer();

	tutorialplayer->CountShoot++;

	if (tutorialplayer->CountShoot >= INT_MAX)
	{
		tutorialplayer->CountShoot -= INT_MAX;
	}


	if (GetKeyboardPress(DIK_K)) // �e����
	{
		if ((tutorialplayer->CountShoot % PLAYER_BULLET_SHOOT_TIME) == 0)
		{
			SetTutorialPlayerBullet(tutorialplayer->pos, PLAYER_BULLET_LEFT);
			SetTutorialPlayerBullet(tutorialplayer->pos, PLAYER_BULLET_RIGHT);

		}

		if ((tutorialplayer->CountShoot % PLAYER_BULLET_SHOOT_TIME) == PLAYER_BULLET_SHOOT_TIME / HALF)
		{
			SetTutorialPlayerBullet(tutorialplayer->pos, PLAYER_BULLET_MID);
		}
	}
}

//=============================================================================
// ����
//=============================================================================
void TutorialPlayerBomb(void)
{
	if (GetKeyboardTrigger(DIK_J)) // ����
	{
		SetTutorialPlayerBomb();
	}
}

//=============================================================================
// �_�ŏ���
//=============================================================================
void SetTutorialPlayerFlashing(void)
{
	PLAYER *tutorialplayer = GetTutorialPlayer();

	tutorialplayer->FlashingCount++;

	if (tutorialplayer->FlashingCount < PLAYER_FLASHING_HOLD_TIME)
	{
		SetAllDiffuseData(g_TutorialPlayerVertexWk,			// �_
		PLAYER_FLASHING_ALPHA_ON);		
		SetAllDiffuseData(g_TutorialEngineEffectVertexWk,	// �_
		PLAYER_FLASHING_ALPHA_ON);
	}

	if (tutorialplayer->FlashingCount > PLAYER_FLASHING_HOLD_TIME)
	{
		SetAllDiffuseData(g_TutorialPlayerVertexWk,			// ��
		PLAYER_FLASHING_ALPHA_OFF);	
		SetAllDiffuseData(g_TutorialEngineEffectVertexWk,	// ��
		PLAYER_FLASHING_ALPHA_OFF);
	}

	if (tutorialplayer->FlashingCount > PLAYER_FLASHING_RESET)
	{
		tutorialplayer->FlashingCount = 0;					// ���Z�b�g
	}
}

//=============================================================================
// �_�ŏ���(�_)
//=============================================================================
void SetTutorialPlayerFlashingOn(void)
{
	SetAllDiffuseData(g_TutorialPlayerVertexWk,			// �_
	PLAYER_FLASHING_ALPHA_ON);
	SetAllDiffuseData(g_TutorialEngineEffectVertexWk,	// �_
	PLAYER_FLASHING_ALPHA_ON);
}


//=============================================================================
// �G���W���G�t�F�N�g
//=============================================================================
void TutorialPlayerEngineEffect(void)
{
	PLAYER *tutorialplayer = GetTutorialPlayer();

	tutorialplayer->CountAnim++;

	if (tutorialplayer->CountAnim%TIME_ENGINE_EFFECT_ANIMATION == 0)
	{
		tutorialplayer->PatternAnim++;

		if (tutorialplayer->PatternAnim > ENGINE_EFFECT_ANIM_PATTERN_NUM)
		{
			tutorialplayer->PatternAnim = 0;
		}
	}

	if (tutorialplayer->CountAnim >= INT_MAX)
	{
		tutorialplayer->CountAnim -= INT_MAX;
	}

	// ������
	tutorialplayer->EffectPos = D3DXVECTOR3(tutorialplayer->pos.x + PLAYER_SIZE_X / 3,
											tutorialplayer->pos.y + PLAYER_SIZE_Y / 2,
											0.0f);

}

//=============================================================================
// �X�N���[���ɓ���A�j���V����
//=============================================================================
void TutorialPlayerInScreen(void)
{
	PLAYER *tutorialplayer = GetTutorialPlayer();

	tutorialplayer->pos.y -= PLAYER_SHIFT_SPEED;

	SetTutorialPlayerFlashing();

}

//=============================================================================
// �`�揈��(�`���g���A���v���C���[)
//=============================================================================
void DrawTutorialPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *tutorialplayer = GetTutorialPlayer();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTutorialPlayer);

	// ���_���W�̐ݒ�(���_���)
	SetVtx4PointData(g_TutorialPlayerVertexWk, tutorialplayer->pos, PLAYER_SIZE_X, PLAYER_SIZE_Y);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialPlayerVertexWk, sizeof(VERTEX_2D));

}

//=============================================================================
// �`�揈��(�`���g���A���G���W���G�t�F�N�g)
//=============================================================================
void DrawTutorialEngineEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *tutorialplayer = GetTutorialPlayer();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTutorialEngineEffect);

	// �e�N�X�`�����W�̐ݒ�(�A�j���[�V����)
	SetTextureAnimationData(g_TutorialEngineEffectVertexWk, tutorialplayer->PatternAnim, ENGINE_EFFECT_PATTERN_DIVIDE_X, ENGINE_EFFECT_PATTERN_DIVIDE_Y);

	// ���_���W�̐ݒ�(���_���)
	SetVtx4PointData(g_TutorialEngineEffectVertexWk, tutorialplayer->EffectPos, ENGINE_EFFECT_SIZE_X, ENGINE_EFFECT_SIZE_Y);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialEngineEffectVertexWk, sizeof(VERTEX_2D));

}

//=============================================================================
// �`���g���A���v���C���[�̏����擾
//=============================================================================
PLAYER *GetTutorialPlayer(void)
{
	return &TutorialPlayerWk;
}
